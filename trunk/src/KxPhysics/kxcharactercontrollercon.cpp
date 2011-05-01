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

#include "kxcharactercontrollercon.h"
#include "kxcharactercontroller.h"

KxCharacterControllerCon::KxCharacterControllerCon(QObject *parent) :
    QObject(parent)
{
    m_upAxis = 1;
    m_collisionShape = NULL;
    m_mask = 1;
    m_group = 1;
    m_fallSpeed = -1; // 55 / KxBulletUtil::scale();
    m_jumpSpeed = -1; //10 / KxBulletUtil::scale();
    m_maxSlope = -1; //45 / KxBulletUtil::scale();
    m_maxJumpHeight = -1; // 1 / KxBulletUtil::scale();
}

QVariant KxCharacterControllerCon::create(const QVariant &parent) const
{
    if (parent.value<QObject*>()) {
        return QVariant::fromValue(create(parent.value<QObject*>()));
    } else {
        qWarning() << "KxCharacterControllerCon::create parent is not QObject";
        return QVariant::fromValue(create());
    }
}

KxCharacterController *KxCharacterControllerCon::create(QObject *parent) const
{
    KxCharacterController *con = new KxCharacterController(m_collisionShape, m_upAxis, parent);
    con->setPosition(m_position);
    con->setRotation(m_rotation);
    if (m_fallSpeed != -1)
        con->setFallSpeed(m_fallSpeed);
    if (m_jumpSpeed != -1)
        con->setJumpSpeed(m_jumpSpeed);
    if (m_maxJumpHeight != -1)
        con->setMaxJumpHeight(m_maxJumpHeight);
    if (m_maxSlope != -1)
        con->setMaxSlope(m_maxSlope);
    return con;
}

qreal KxCharacterControllerCon::fallSpeed() const
{
    return m_fallSpeed;
}

void KxCharacterControllerCon::setFallSpeed(qreal value)
{
    m_fallSpeed = value;
}

qreal KxCharacterControllerCon::jumpSpeed() const
{
    return m_jumpSpeed;
}

void KxCharacterControllerCon::setJumpSpeed(qreal value)
{
    m_jumpSpeed = value;
}

qreal KxCharacterControllerCon::maxJumpHeight() const
{
    return m_maxJumpHeight;
}

void KxCharacterControllerCon::setMaxJumpHeight(qreal value)
{
    m_maxJumpHeight = value;
}

qreal KxCharacterControllerCon::maxSlope() const
{
    return m_maxSlope;
}

void KxCharacterControllerCon::setMaxSlope(qreal value)
{
    m_maxSlope = value;
}


void KxCharacterControllerCon::setPosition(const QVector3D &value)
{
    m_position = value;
}

void KxCharacterControllerCon::setRotation(const QQuaternion &value)
{
    m_rotation = value;
}

void KxCharacterControllerCon::setMask(short value)
{
    m_mask = value;
}

void KxCharacterControllerCon::setGroup(short value)
{
    m_group = value;
}

void KxCharacterControllerCon::setCollisionShape(KxConvexShape *value)
{
    m_collisionShape = value;
}

void KxCharacterControllerCon::setUpAxis(int value)
{
    m_upAxis = value;
}

KxConvexShape *KxCharacterControllerCon::collisionShape() const
{
    return m_collisionShape;
}

int KxCharacterControllerCon::upAxis() const
{
    return m_upAxis;
}

short KxCharacterControllerCon::mask() const
{
    return m_mask;
}

short KxCharacterControllerCon::group() const
{
    return m_group;
}

const QVector3D& KxCharacterControllerCon::position() const
{
    return m_position;
}

const QQuaternion& KxCharacterControllerCon::rotation() const
{
    return m_rotation;
}
