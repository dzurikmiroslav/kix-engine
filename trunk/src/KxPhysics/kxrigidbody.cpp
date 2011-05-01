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

#include "kxrigidbody.h"
#include "kxbulletutil.h"
#include "kxcollisionshape.h"
#include <QtCore/qmath.h>

KxRigidBody::KxRigidBody(KxCollisionShape *shape, qreal mass, QObject *parent) :
        KxCollisionObject(parent)
{
    m_worldTransform.setIdentity();
    setup(shape, mass);
}

KxRigidBody::~KxRigidBody()
{
    emit beforeDestroy(this);
    if(m_body)
        delete m_body;
}

void KxRigidBody::setup(KxCollisionShape *shape, qreal mass)
{
    btVector3 localInertia(0, 0, 0);
    if (!qIsNull(mass))
        shape->internalBtShape()->calculateLocalInertia(mass, localInertia);
    m_body = new btRigidBody(mass, this, shape->internalBtShape(), localInertia);
    m_body->setUserPointer(this);
    m_body->setActivationState(DISABLE_DEACTIVATION);   //TODO
}

QVector3D KxRigidBody::position() const
{
    return KxBulletUtil::convertScaled(m_worldTransform.getOrigin());
}

void KxRigidBody::setPosition(const QVector3D &pos)
{
    m_worldTransform.setOrigin(KxBulletUtil::convertScaled(pos));
    m_body->setWorldTransform(m_worldTransform);
    // emit changeWorldTransform(worldTransform());
}

QQuaternion KxRigidBody::rotation() const
{
    return KxBulletUtil::convert(m_worldTransform.getRotation());
}

void KxRigidBody::setRotation(const QQuaternion &value)
{
    m_worldTransform.setRotation(KxBulletUtil::convert(value));
    m_body->setWorldTransform(m_worldTransform);
    //m_body->setWorldTransform(btTransform(KxBulletUtil::convert(value)));
}

KxCollisionShape* KxRigidBody::collisionShape() const
{
    return (KxCollisionShape*)m_body->getCollisionShape()->getUserPointer();
}

short KxRigidBody::mask() const
{
    return m_body->getBroadphaseHandle()->m_collisionFilterMask;
}

short KxRigidBody::group() const
{
    return m_body->getBroadphaseHandle()->m_collisionFilterGroup;
}

QVector3D KxRigidBody::linearVelocity() const
{
    return KxBulletUtil::convertScaled(m_body->getLinearVelocity());
}

QVector3D KxRigidBody::angularVelocity() const
{
    return KxBulletUtil::convert(m_body->getAngularVelocity());
}

qreal KxRigidBody::linearDamping() const
{
    return m_body->getLinearDamping();
}

qreal KxRigidBody::angularDamping() const
{
    return m_body->getAngularDamping();
}

QVector3D KxRigidBody::gravity() const
{
    return KxBulletUtil::convertScaled(m_body->getGravity());
}

QVector3D KxRigidBody::linearFactor() const
{
    return KxBulletUtil::convert(m_body->getLinearFactor());
}

QVector3D KxRigidBody::angularFactor() const
{
    return KxBulletUtil::convert(m_body->getAngularFactor());
}

void KxRigidBody::setLinearVelocity(const QVector3D &velocity)
{
    m_body->activate();
    m_body->setLinearVelocity(KxBulletUtil::convertScaled(velocity));
}

void KxRigidBody::setAngularVelocity(const QVector3D &velocity)
{
    m_body->activate();
    m_body->setAngularVelocity(KxBulletUtil::convert(velocity));
}

void KxRigidBody::setLinearFactor(const QVector3D &velocity)
{
    m_body->setLinearFactor(KxBulletUtil::convert(velocity));
}

void KxRigidBody::setAngularFactor(const QVector3D &value)
{
    m_body->setAngularFactor(KxBulletUtil::convert(value));
}

void KxRigidBody::setLinearDamping(qreal value)
{
    m_body->setDamping(value, m_body->getAngularDamping());
}

void KxRigidBody::setAngularDamping(qreal value)
{
    m_body->setDamping(m_body->getLinearDamping(), value);
}

void KxRigidBody::setGravity(const QVector3D &gravity)
{
    m_body->setGravity(KxBulletUtil::convertScaled(gravity));
}

void KxRigidBody::setWorldTransform(const btTransform &centerOfMassWorldTrans)
{
    if(m_worldTransform == centerOfMassWorldTrans)
        return;
    m_worldTransform = centerOfMassWorldTrans;
    QVector3D pos = KxBulletUtil::convertScaled(m_worldTransform.getOrigin());
    QQuaternion rot = KxBulletUtil::convert(m_worldTransform.getRotation());
    emit transformChanged(pos, rot);
   //emit positionChanged(pos);
   // emit rotationChanged(rot);
}

void KxRigidBody::getWorldTransform(btTransform &centerOfMassWorldTrans) const
{
    centerOfMassWorldTrans = m_worldTransform;
}

QVector3D KxRigidBody::totalForce() const
{
    return KxBulletUtil::convertScaled(m_body->getTotalForce());
}

QVector3D KxRigidBody::totalTorque() const
{
    return KxBulletUtil::convert(m_body->getTotalTorque()) * qPow(KxBulletUtil::oneOverScale(), qreal(2));
}

void KxRigidBody::applyCentralForce(const QVector3D& force)
{
    m_body->activate();
    m_body->applyCentralForce(KxBulletUtil::convertScaled(force));
}

void KxRigidBody::applyForce(const QVector3D &force, const QVector3D &relPos)
{
    m_body->activate();
    m_body->applyForce(KxBulletUtil::convertScaled(force), KxBulletUtil::convertScaled(relPos));
}

void KxRigidBody::applyTorque(const QVector3D &torque)
{
    m_body->activate();
    m_body->applyTorque(KxBulletUtil::convert(torque) * qPow(KxBulletUtil::scale(), qreal(2)));
}

void KxRigidBody::applyCentralImpulse(const QVector3D &impulse)
{
    m_body->activate();
    m_body->applyCentralImpulse(KxBulletUtil::convertScaled(impulse));
}

void KxRigidBody::applyTorqueImpulse(const QVector3D &torque)
{
    m_body->activate();
    m_body->applyTorqueImpulse(KxBulletUtil::convert(torque) * qPow(KxBulletUtil::scale(), qreal(2)));
}

void KxRigidBody::applyImpulse(const QVector3D &impulse, const QVector3D &relPos)
{
    m_body->activate();
    m_body->applyImpulse(KxBulletUtil::convertScaled(impulse), KxBulletUtil::convertScaled(relPos));
}

void KxRigidBody::clearForces()
{
    m_body->clearForces();
}

bool KxRigidBody::isRigidBody() const
{
    return true;
}

bool KxRigidBody::isDynamic() const
{
    return !qIsNull(m_body->getInvMass());
}
