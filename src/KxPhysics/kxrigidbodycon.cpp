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

#include "kxrigidbodycon.h"
#include "kxrigidbody.h"
#include "KxEntity/kxentity.h"
#include <QtCore/qdebug.h>

KxRigidBodyCon::KxRigidBodyCon(QObject *parent) :
    QObject(parent)
{
    m_collisionShape = NULL;
    m_group = 1;
    m_mask = 1;
    m_mass = 0;
    m_friction = 0.5;
}

QVariant KxRigidBodyCon::create(const QVariant &parent) const
{
    if (parent.value<QObject*>()) {
       return QVariant::fromValue(create(parent.value<QObject*>()));
    } else {
        qWarning() << "KxRigidBodyCon::create parent is not QObject";
        return QVariant::fromValue(create());
    }
}

KxRigidBody *KxRigidBodyCon::create(QObject *parent) const
{
    if (!m_collisionShape) {
        qWarning() << "KxRigidBodyCon::create collisionShape is NULL";
        return NULL;
    }
    KxRigidBody *rb = new KxRigidBody(m_collisionShape, m_mass, parent);
    rb->setFriction(m_friction);
    rb->setPosition(m_position);
    rb->setRotation(m_rotation);
    return rb;
}
