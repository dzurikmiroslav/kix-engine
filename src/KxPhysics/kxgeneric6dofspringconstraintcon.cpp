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

#include "kxgeneric6dofspringconstraintcon.h"
#include "kxgeneric6dofspringconstraint.h"
#include "kxrigidbody.h"

KxGeneric6DofSpringConstraintCon::KxGeneric6DofSpringConstraintCon(QObject *parent) :
        KxGeneric6DofConstraintCon(parent)
{
    m_springs = QBitArray(6, false);
    m_angularEquilibriumPoint = m_linearEquilibriumPoint = QVector3D(0, 0, 0);
    m_angularSpringDamping = m_linearSpringDamping = QVector3D(1, 1, 1);
    m_angularSpringStiffness = m_linearSpringStiffness = QVector3D(0, 0, 0);
}

KxGeneric6DofSpringConstraint* KxGeneric6DofSpringConstraintCon::create(KxRigidBody *aBody, KxRigidBody *bBody, QObject *parent) const
{
    KxGeneric6DofSpringConstraint *constraint = new KxGeneric6DofSpringConstraint(aBody, bBody,
                                                                                  m_posInA, m_rotInA,
                                                                                  m_posInB, m_rotInB, parent);
    setup6DofConstraintProperties(constraint);
    constraint->setAngularSpringDamping(m_angularSpringDamping);
    constraint->setAngularStiffness(m_angularSpringStiffness);
    constraint->setAngularEquilibriumPoint(m_angularEquilibriumPoint);
    constraint->setLinearSpringDamping(m_linearSpringDamping);
    constraint->setLinearStiffness(m_linearSpringStiffness);
    constraint->setLinearEquilibriumPoint(m_linearEquilibriumPoint);
    for(int i = 0; i < 6; i++) {
        constraint->setEnableSpring(i, m_springs.at(i));
    }
    return constraint;
}

KxGeneric6DofSpringConstraint* KxGeneric6DofSpringConstraintCon::create(QObject *aBody, QObject *bBody, QObject *parent) const
{
    if((!qobject_cast<KxRigidBody*>(aBody)) || (!qobject_cast<KxRigidBody*>(bBody))) {
        qWarning() << "KxGeneric6DofSpringConstraintCon::create invalid body";
        return NULL;
    }
    return create(qobject_cast<KxRigidBody*>(aBody), qobject_cast<KxRigidBody*>(bBody), parent);
}
