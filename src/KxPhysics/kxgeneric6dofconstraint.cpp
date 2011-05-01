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

#include "kxgeneric6dofconstraint.h"
#include "kxrigidbody.h"
#include "kxbulletutil.h"

KxGeneric6DofConstraint::KxGeneric6DofConstraint(KxRigidBody *rbA, KxRigidBody *rbB,
                                                 const QVector3D &posInA, const QQuaternion &rotInA,
                                                 const QVector3D &posInB, const QQuaternion &rotInB,
                                                 QObject *parent) :
KxTypedConstraint(parent)
{
    btTransform frameInA = btTransform(KxBulletUtil::convert(rotInA), KxBulletUtil::convertScaled(posInA));
    btTransform frameInB = btTransform(KxBulletUtil::convert(rotInB), KxBulletUtil::convertScaled(posInB));
    m_constraint = new btGeneric6DofConstraint(*rbA->m_body, *rbB->m_body, frameInA, frameInB, false);
    m_constraint->setUserConstraintPtr(this);
}

KxGeneric6DofConstraint::KxGeneric6DofConstraint(QObject *parent) :
        KxTypedConstraint(parent)
{
}

KxGeneric6DofConstraint::~KxGeneric6DofConstraint()
{
    emit beforeDestroy(this);
    delete m_constraint;
}

KxRigidBody *KxGeneric6DofConstraint::aBody() const
{
    return (KxRigidBody*) m_constraint->getRigidBodyA().getUserPointer();
}

KxRigidBody *KxGeneric6DofConstraint::bBody() const
{
    return (KxRigidBody*) m_constraint->getRigidBodyB().getUserPointer();
}
