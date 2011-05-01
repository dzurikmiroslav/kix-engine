/*
* This file is part of Kix Engine
*
* Copyright (C) 2011 - Miroslav Dzurik
*
* Kix Engine is free software; you can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public
* License as published by the Free Software Foundation; either
* version 3 of the License, or (at your option) any later version.
*
* Kix Engine is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
* Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public
* License along with this library; if not, write to the Free Software
* Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "kxphysicsworld.h"
#include "kxrigidbody.h"
#include "kxbulletutil.h"
#include "kxcollisionshape.h"
#include "kxcharactercontroller.h"
#include <BulletCollision/CollisionDispatch/btGhostObject.h>
#include "kxconcaveshape.h"
#include "kxconvexshape.h"
#include <QtCore/QThread>
#include <QtCore/QCoreApplication>
#include "kxrayresultcallback.h"
#include "KxEngine/kxengine.h"

KxPhysicsWorld::KxPhysicsWorld(QObject *parent) :
    QObject(parent)
{
    qDebug() << "KxPhysicsWorld::KxPhysicsWorld bullet version" << btGetVersion();
    gDisableDeactivation = true;
    m_sleep = false;
    m_collisionConfiguration = new btDefaultCollisionConfiguration();
    m_dispatcher = new btCollisionDispatcher(m_collisionConfiguration);
    m_broadphase= new btDbvtBroadphase();
    m_broadphase->getOverlappingPairCache()->setInternalGhostPairCallback(new btGhostPairCallback());
    m_solver = new btSequentialImpulseConstraintSolver();
    m_dynamicsWorld = new btContinuousDynamicsWorld(m_dispatcher, m_broadphase, m_solver, m_collisionConfiguration);
    //m_dynamicsWorld = new btDiscreteDynamicsWorld(m_dispatcher, m_broadphase, m_solver, m_collisionConfiguration);
    m_drawer = new KxBulletDebugDrawer(KxBulletUtil::oneOverScale());
    m_vehicleRaycaster = new btDefaultVehicleRaycaster(m_dynamicsWorld);
    m_dynamicsWorld->setDebugDrawer(m_drawer);
    m_dynamicsWorld->getSolverInfo().m_splitImpulse = true;
    m_dynamicsWorld->getSolverInfo().m_numIterations = 20;
    m_dynamicsWorld->getDispatchInfo().m_useContinuous = true;
}

btVehicleRaycaster *KxPhysicsWorld::vechicleRaycaster() const
{
    return m_vehicleRaycaster;
}

void KxPhysicsWorld::rayTest(KxRayResultCallback *rayCallback)
{
    m_mutex.lock();
    btCollisionWorld::ClosestRayResultCallback &rayCb = rayCallback->prepare();
    rayCb.m_collisionObject = NULL;
    rayCb.m_closestHitFraction = btScalar(1.0);
    m_dynamicsWorld->rayTest(rayCb.m_rayFromWorld, rayCb.m_rayToWorld, rayCb);
    m_mutex.unlock();
}

void KxPhysicsWorld::setSleep(bool sleep)
{
    m_mutex.lock();
    m_sleep = sleep;
    m_mutex.unlock();
}

KxPhysicsWorld::~KxPhysicsWorld()
{
    delete m_dynamicsWorld;
    delete m_solver;
    delete m_broadphase;
    delete m_dispatcher;
    delete m_collisionConfiguration;
    if (m_drawer)
        delete m_drawer;
}

void KxPhysicsWorld::debugDraw()
{
    m_mutex.lock();
    m_drawer->bind();
    m_dynamicsWorld->debugDrawWorld();
    m_drawer->release();
    m_mutex.unlock();
}

QVector3D KxPhysicsWorld::gravity() const
{
    return KxBulletUtil::convertScaled(m_dynamicsWorld->getGravity());
}

void KxPhysicsWorld::setGravity(const QVector3D &gravity)
{
    m_dynamicsWorld->setGravity(KxBulletUtil::convertScaled(gravity));
}

QMutex physicsUpdate;

void KxPhysicsWorld::update(int ms)
{
    m_mutex.lock();
    if (!m_sleep) {
        physicsUpdate.lock();
        //m_dynamicsWorld->stepSimulation(ms / 1000.f);
        m_dynamicsWorld->stepSimulation(ms / 1000.f, 0);
        physicsUpdate.unlock();
        /*
          Not usefull ?!?
        int constraintCount = m_dynamicsWorld->getNumConstraints();
        for (int i = 0; i < constraintCount; i++) {
            KxTypedConstraint *constraint = m_dynamicsWorld->getConstraint(i)->getUserConstraintPtr();
            if (constraint)
                constraint->emitPosotions();
        }*/
    }
    m_mutex.unlock();
}

void KxPhysicsWorld::addCollisionObject(KxCollisionObject *object, short group, short mask)
{
    m_mutex.lock();
    if (qobject_cast<KxRigidBody*>(object)) {
        KxRigidBody *rb = qobject_cast<KxRigidBody*>(object);
        m_dynamicsWorld->addRigidBody(rb->m_body, group, mask);
    } else if (qobject_cast<KxCharacterController*>(object)) {
        KxCharacterController *character = qobject_cast<KxCharacterController*>(object);
        m_dynamicsWorld->addCollisionObject(character->m_ghostObject, group, mask);
        m_dynamicsWorld->addAction(character);
        //m_dynamicsWorld->addCharacter(character->m_character);
    } else /*if (qobject_cast<KxRaycastVehicle*>(object))*/ {
        KxRaycastVehicle *vehicle = qobject_cast<KxRaycastVehicle*>(object);
        m_dynamicsWorld->addRigidBody(vehicle->m_body, group, mask);
        m_dynamicsWorld->addAction(vehicle);
    }
    connect(object, SIGNAL(beforeDestroy(KxCollisionObject*)),
            this, SLOT(removeCollisionObject(KxCollisionObject*)));
    m_mutex.unlock();
}

void KxPhysicsWorld::addConstraint(KxTypedConstraint *constraint, bool disCollBetween)
{
    m_mutex.lock();
    m_dynamicsWorld->addConstraint(constraint->internalBtConstraint(), disCollBetween);
    connect(constraint, SIGNAL(beforeDestroy(KxTypedConstraint*)),
            this, SLOT(removeConstraint(KxTypedConstraint*)));
    m_mutex.unlock();
}

void KxPhysicsWorld::removeConstraint(KxTypedConstraint *constraint)
{
    m_mutex.lock();
    m_dynamicsWorld->removeConstraint(constraint->internalBtConstraint());
    disconnect(constraint, SIGNAL(beforeDestroy(KxTypedConstraint*)),
               this, SLOT(removeConstraint(KxTypedConstraint*)));
    m_mutex.unlock();
}

void KxPhysicsWorld::removeCollisionObject(KxCollisionObject *object)
{
    m_mutex.lock();
    if (object->inherits(KxRigidBody::staticMetaObject.className())) {
        KxRigidBody *rb = qobject_cast<KxRigidBody*>(object);
        m_dynamicsWorld->removeRigidBody(rb->m_body);
    } else if (object->inherits(KxCharacterController::staticMetaObject.className())) {
        KxCharacterController *character = qobject_cast<KxCharacterController*>(object);
        m_dynamicsWorld->removeAction(character);
        m_dynamicsWorld->removeCollisionObject(character->m_ghostObject);
    }
    disconnect(object, SIGNAL(beforeDestroy(KxCollisionObject*)),
               this, SLOT(removeCollisionObject(KxCollisionObject*)));
    m_mutex.unlock();
}

void KxPhysicsWorld::addCollisionObject(const QVariant &objectVar, const QVariant &groupVar, const QVariant &maskVar)
{
    KxCollisionObject *colObj = qobject_cast<KxCollisionObject*>(objectVar.value<QObject*>());
    if (colObj) {
        short group = 1;
        short mask = 1;
        if (groupVar.canConvert(QVariant::UInt) && maskVar.canConvert(QVariant::UInt)) {
            group = groupVar.toUInt();
            mask = maskVar.toUInt();
        }
        addCollisionObject(colObj, group, mask);
    } else {
        qWarning() << "KxPhysicsWorld::addCollisionObject invalid object";
    }
}

void KxPhysicsWorld::rayTest(const QVariant &rayCallbackVar)
{
    KxRayResultCallback *rayCallback = qobject_cast<KxRayResultCallback*> (rayCallbackVar.value<QObject*>());
    if (rayCallback)
        rayTest(rayCallback);
    else
        qWarning() << "KxPhysicsWorld::rayTest invalid rayCallback";
}

void KxPhysicsWorld::addConstraint(const QVariant &constraintVar, const QVariant &disCollBetweenVar)
{
    KxTypedConstraint *constraint = qobject_cast<KxTypedConstraint*>(constraintVar.value<QObject*>());
    if (constraint) {
        bool disCollBetween = true;
        if (disCollBetweenVar.canConvert(QVariant::Bool))
            disCollBetween = disCollBetweenVar.toBool();
        addConstraint(constraint, disCollBetween);
    } else {
        qWarning() << "KxPhysicsWorld::addConstraint invalid constraint";
    }
}
