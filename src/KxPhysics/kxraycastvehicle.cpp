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

#include "kxraycastvehicle.h"
#include "kxphysicsworld.h"

KxWheelInfo::KxWheelInfo(int wheelIndex, KxRaycastVehicle *vehicle) :
        QObject(vehicle)
{
    m_vechile = vehicle->m_vechile;
    m_wheelId = wheelIndex;
    m_vechile->getWheelInfo(m_wheelId).m_clientInfo = (void*)this;
}

void KxWheelInfo::emitTransform()
{
    m_vechile->updateWheelTransform(m_wheelId, true);
    const btWheelInfo &w = m_vechile->getWheelInfo(m_wheelId);
    emit transformChanged(KxBulletUtil::convertScaled(w.m_worldTransform.getOrigin()),
                          KxBulletUtil::convert(w.m_worldTransform.getRotation()));
}

KxRaycastVehicle::KxRaycastVehicle(KxCollisionShape *shape, qreal mass, QObject *parent) :
        KxRigidBody(shape, mass, parent)
{
    m_vechile = new btRaycastVehicle(m_turing, m_body, KxBulletUtil::physicsWorld()->vechicleRaycaster());
    m_vechile->setCoordinateSystem(0, 1, 2);
}

void KxRaycastVehicle::debugDraw(btIDebugDraw *debugDrawer)
{
    for (int v=0;v< m_vechile->getNumWheels();v++)
    {
        btVector3 wheelColor(0,1,1);
        if (m_vechile->getWheelInfo(v).m_raycastInfo.m_isInContact)
        {
            wheelColor.setValue(0,0,1);
        } else
        {
            wheelColor.setValue(1,0,1);
        }

        btVector3 wheelPosWS = m_vechile->getWheelInfo(v).m_worldTransform.getOrigin();

        btVector3 axle = btVector3(
                m_vechile->getWheelInfo(v).m_worldTransform.getBasis()[0][m_vechile->getRightAxis()],
                m_vechile->getWheelInfo(v).m_worldTransform.getBasis()[1][m_vechile->getRightAxis()],
                m_vechile->getWheelInfo(v).m_worldTransform.getBasis()[2][m_vechile->getRightAxis()]);

        //debug wheels (cylinders)
        debugDrawer->drawLine(wheelPosWS,wheelPosWS+axle,wheelColor);
        debugDrawer->drawLine(wheelPosWS,m_vechile->getWheelInfo(v).m_raycastInfo.m_contactPointWS,wheelColor);
    }
}

void KxRaycastVehicle::updateAction(btCollisionWorld *collisionWorld, btScalar deltaTimeStep)
{
    m_vechile->updateVehicle(deltaTimeStep);
    foreach(KxWheelInfo *w, m_wheels)
        w->emitTransform();
}

QDeclarativeListProperty<KxWheelInfo> KxRaycastVehicle::qmlWheels()
{
    return QDeclarativeListProperty<KxWheelInfo>(this, m_wheels);
}

KxWheelInfo *KxRaycastVehicle::addWheel(const QVector3D &connectionPointCS0,
                                        const QVector3D &wheelDirectionCS0,
                                        const QVector3D &wheelAxleCS,
                                        qreal suspensionRestLength, qreal wheelRadius, bool isFrontWheel)
{
    btWheelInfo *w = &(m_vechile->addWheel(KxBulletUtil::convertScaled(connectionPointCS0),
                                          KxBulletUtil::convert(wheelDirectionCS0),
                                          KxBulletUtil::convert(wheelAxleCS),
                                          suspensionRestLength * KxBulletUtil::scale(),
                                          wheelRadius * KxBulletUtil::scale(),
                                          m_turing, isFrontWheel));

/*
    float	wheelFriction = 2;//BT_LARGE_FLOAT;
    float	suspensionStiffness = 20.f;
    float	suspensionDamping = 2.3f;
    float	suspensionCompression = 0.03f;
    float	rollInfluence = 0.3;//1.0f;
    w->m_suspensionStiffness = suspensionStiffness;
    w->m_wheelsDampingRelaxation = suspensionDamping;
    w->m_wheelsDampingCompression = suspensionCompression;
    w->m_frictionSlip = wheelFriction;
    w->m_rollInfluence = rollInfluence;
*/
    KxWheelInfo *wheel = new KxWheelInfo(m_vechile->getNumWheels() - 1, this);
    m_wheels << wheel;
    return wheel;
}

void KxRaycastVehicle::setSteeringValue(qreal steering, int wheel)
{
    m_vechile->setSteeringValue(steering, wheel);
}
