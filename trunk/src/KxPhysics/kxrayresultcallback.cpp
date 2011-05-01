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

#include "kxrayresultcallback.h"
#include "kxcollisionobject.h"
#include "kxphysicsworld.h"
#include "kxbulletutil.h"

KxRayResultCallback::KxRayResultCallback(QObject *parent) :
    QObject(parent),
    m_rayResultCallback(btVector3(), btVector3())
{
    m_rayResultCallback.m_collisionFilterMask = 1;
    m_rayResultCallback.m_collisionFilterGroup = 1;
}

short KxRayResultCallback::mask() const
{
    return m_rayResultCallback.m_collisionFilterMask;
}

short KxRayResultCallback::group() const
{
    return m_rayResultCallback.m_collisionFilterGroup;
}

void KxRayResultCallback::setGroup(short group)
{
    m_rayResultCallback.m_collisionFilterGroup = group;
}

void KxRayResultCallback::setMask(short mask)
{
    m_rayResultCallback.m_collisionFilterMask = mask;
}

bool KxRayResultCallback::hasHit() const
{
    return m_rayResultCallback.hasHit();
}

QVector3D KxRayResultCallback::from() const
{
    return KxBulletUtil::convertScaled(m_rayResultCallback.m_rayFromWorld);
}

QVector3D KxRayResultCallback::direction() const
{
    return m_direction;
    //return KxBulletUtil::convertScaled(m_rayResultCallback.m_rayToWorld);
}

QVector3D KxRayResultCallback::hitPosition() const
{
    return KxBulletUtil::convertScaled(m_rayResultCallback.m_hitPointWorld);
}

void KxRayResultCallback::setFrom(const QVector3D &pos)
{
    m_rayResultCallback.m_rayFromWorld = KxBulletUtil::convertScaled(pos);
}

void KxRayResultCallback::setDirection(const QVector3D &value)
{
    m_direction = value;
    //m_rayResultCallback.m_rayToWorld = KxBulletUtil::convertScaled(pos);
}

void KxRayResultCallback::setMaxFraction(qreal value)
{
    m_maxFraction = value;
}

btCollisionWorld::ClosestRayResultCallback &KxRayResultCallback::prepare()
{
    m_rayResultCallback.m_rayToWorld = m_rayResultCallback.m_rayFromWorld
            + KxBulletUtil::convertScaled(m_direction * m_maxFraction);
    return m_rayResultCallback;
}

qreal KxRayResultCallback::maxFraction() const
{
    return m_maxFraction;
}

KxCollisionObject* KxRayResultCallback::collisionObject() const
{
    return (KxCollisionObject*)m_rayResultCallback.m_collisionObject->getUserPointer();
}

qreal KxRayResultCallback::hitFraction() const
{
    return m_rayResultCallback.m_closestHitFraction;
}

