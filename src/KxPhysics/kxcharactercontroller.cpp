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

#include "kxcharactercontroller.h"
#include <QtCore/qvariant.h>
#include "kxphysicsworld.h"
#include "kxbulletutil.h"
#include "kxconvexshape.h"


KxCharacterController::KxCharacterController(KxConvexShape *shape, int upAxis, QObject *parent) :
        KxCollisionObject(parent)
{
    setup(shape, upAxis);
}

KxCharacterController::~KxCharacterController()
{
    emit beforeDestroy(this);
    delete m_ghostObject;
    delete m_character;
}

void KxCharacterController::setup(KxConvexShape *shape, int upAxis)
{
    m_ghostObject = new btPairCachingGhostObject();
    m_ghostObject->setCollisionShape(shape->internalConvexShape());
    m_ghostObject->setUserPointer(this);
    m_ghostObject->setCollisionFlags(btCollisionObject::CF_CHARACTER_OBJECT);
    m_character = new btKinematicCharacterController(m_ghostObject, shape->internalConvexShape(), 1, upAxis);
}

KxCollisionShape *KxCharacterController::collisionShape() const
{
    return (KxCollisionShape*)m_ghostObject->getCollisionShape()->getUserPointer();
}

void KxCharacterController::updateAction(btCollisionWorld *collisionWorld, btScalar deltaTimeStep)
{
    if (m_useWalkDirection) {
        m_character->setWalkDirection(KxBulletUtil::convertScaled(m_walkDirection));
        m_walkDirection = QVector3D();
    } else {
        m_character->setVelocityForTimeInterval(KxBulletUtil::convertScaled(m_walkDirection), BT_LARGE_FLOAT);
    }
    m_character->preStep(collisionWorld);
    m_character->playerStep(collisionWorld, deltaTimeStep);
    QVector3D pos = position();
    emit transformChanged(pos, rotation());
    emit positionChanged(pos);
}

void KxCharacterController::debugDraw(btIDebugDraw *debugDrawer)
{
    Q_UNUSED(debugDrawer);
}

short KxCharacterController::mask() const
{
    return m_ghostObject->getBroadphaseHandle()->m_collisionFilterMask;
}

short KxCharacterController::group() const
{
    return m_ghostObject->getBroadphaseHandle()->m_collisionFilterGroup;
}

void KxCharacterController::setPosition(const QVector3D &position)
{
    m_character->warp(KxBulletUtil::convertScaled(position));
}

QVector3D KxCharacterController::position() const
{
    return KxBulletUtil::convertScaled(m_ghostObject->getWorldTransform().getOrigin());
}

QQuaternion KxCharacterController::rotation() const
{
    return KxBulletUtil::convert(m_ghostObject->getWorldTransform().getRotation());
}

void KxCharacterController::setRotation(const QQuaternion &value)
{
    m_ghostObject->getWorldTransform().setRotation(KxBulletUtil::convert(value));
    emit rotationChanged(value);
}

void KxCharacterController::jump()
{
    m_character->jump();
}

bool KxCharacterController::isCharacterController() const
{
    return true;
}

qreal KxCharacterController::fallSpeed() const
{
    //return m_character->;   //HACK BULLET getter
    return 0;
}

void KxCharacterController::setJumpSpeed(qreal value)
{
    m_character->setJumpSpeed(KxBulletUtil::scale() * value);
}

qreal KxCharacterController::jumpSpeed() const
{
    return 0; //HACK BULLET getter
}

void KxCharacterController::setMaxJumpHeight(qreal value)
{
    m_character->setMaxJumpHeight(KxBulletUtil::scale() * value);
}

qreal KxCharacterController::maxJumpHeight() const
{
    return 0; //HACK BULLET getter
}

void KxCharacterController::setMaxSlope(qreal value)
{
    m_character->setMaxSlope(value);
}

qreal KxCharacterController::maxSlope() const
{
    return m_character->getMaxSlope();
}

void KxCharacterController::setFallSpeed(qreal value)
{
    m_character->setFallSpeed(KxBulletUtil::scale() * value);
}

void KxCharacterController::setVelocity(const QVector3D &velocity)
{
    m_useWalkDirection = false;
    m_walkDirection = velocity;
    //m_character->setVelocityForTimeInterval(KxBulletUtil::convert(velocity), BT_LARGE_FLOAT);
}

void KxCharacterController::setWalkDirection(const QVector3D &delta)
{
    m_useWalkDirection = true;
    m_walkDirection += delta;
    ///m_character->setWalkDirection(KxBulletUtil::convertScaled(delta));
}
