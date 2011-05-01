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

#include "kxgeneric6dofspringconstraint.h"
#include "kxbulletutil.h"
#include "kxrigidbody.h"

KxGeneric6DofSpringConstraint::KxGeneric6DofSpringConstraint(KxRigidBody *rbA,
                                                             KxRigidBody *rbB,
                                                             const QVector3D &posInA, const QQuaternion &rotInA,
                                                             const QVector3D &posInB, const QQuaternion &rotInB,
                                                             QObject *parent) :
KxGeneric6DofConstraint(parent)
{
    btTransform frameInA = btTransform(KxBulletUtil::convert(rotInA), KxBulletUtil::convertScaled(posInA));
    btTransform frameInB = btTransform(KxBulletUtil::convert(rotInB), KxBulletUtil::convertScaled(posInB));
    m_constraint = new btGeneric6DofSpringConstraint(*rbA->m_body, *rbB->m_body, frameInA, frameInB, false);
    m_constraint->setUserConstraintPtr(this);
}

