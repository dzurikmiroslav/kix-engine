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

#include "kxgeneric6dofconstraintcon.h"
#include "kxgeneric6dofconstraint.h"

KxGeneric6DofConstraintCon::KxGeneric6DofConstraintCon(QObject *parent) :
        QObject(parent)
{    
    m_motors = QBitArray(6, false);
    m_angularUpperLimit = QVector3D(-1, -1, -1);
    m_angularLowerLimit = QVector3D(1, 1, 1);
    m_angularNormalCFM = QVector3D(0, 0, 0);
    m_angularStopERP = QVector3D(0.2f, 0.2f, 0.2f);
    m_angularStopCFM = QVector3D(0, 0, 0);
    m_angularBounce = QVector3D(0, 0, 0);
    m_angularDamping = QVector3D(1, 1, 1);
    m_angularLimitSoftness = QVector3D(0.5f, 0.5f, 0.5f);
    m_linearLowerLimit = QVector3D(0, 0, 0);
    m_linearUpperLimit = QVector3D(0, 0, 0);
    m_linearNormalCFM = QVector3D(0, 0, 0);
    m_linearStopERP = QVector3D(0.2f, 0.2f, 0.2f);
    m_linearStopCFM = QVector3D(0, 0, 0);
    m_linearLimitSoftness = 0.7f;
    m_linearDamping = 1;
    m_linearRestitution = 0.5f;
    m_angularMaxLimitForce = QVector3D(300, 300, 300);
}

KxGeneric6DofConstraint *KxGeneric6DofConstraintCon::create(KxRigidBody *aBody, KxRigidBody *bBody, QObject *parent) const
{    
    KxGeneric6DofConstraint *constraint = new KxGeneric6DofConstraint(aBody, bBody,
                                                                      m_posInA, m_rotInA,
                                                                      m_posInB, m_rotInB, parent);
    setup6DofConstraintProperties(constraint);
    return constraint;
}

KxGeneric6DofConstraint* KxGeneric6DofConstraintCon::create(QObject *aBody, QObject *bBody, QObject *parent) const
{
    if((!qobject_cast<KxRigidBody*>(aBody)) || (!qobject_cast<KxRigidBody*>(bBody))) {
        qWarning() << "KxGeneric6DofConstraintCon::create invalid body";
        return NULL;
    }
    return create(qobject_cast<KxRigidBody*>(aBody), qobject_cast<KxRigidBody*>(bBody), parent);
}

void KxGeneric6DofConstraintCon::setup6DofConstraintProperties(KxGeneric6DofConstraint *constraint) const
{
    constraint->setAngularLowerLimit(m_angularLowerLimit);
    constraint->setAngularUpperLimit(m_angularUpperLimit);
    constraint->setLinearLowerLimit(m_linearLowerLimit);
    constraint->setLinearUpperLimit(m_linearUpperLimit);
    constraint->setAngularDamping(m_angularDamping);
    constraint->setAngularLimitSoftness(m_angularLimitSoftness);
    constraint->setAngularNormalCFM(m_angularNormalCFM);
    constraint->setAngularStopCFM(m_angularStopCFM);
    constraint->setAngularStopERP(m_angularStopERP);
    constraint->setAngularBounce(m_angularBounce);
    constraint->setLinearNormalCFM(m_linearNormalCFM);
    constraint->setLinearStopERP(m_linearStopERP);
    constraint->setLinearStopCFM(m_linearStopCFM);
    constraint->setLinearRestitution(m_linearRestitution);
    constraint->setLinearDamping(m_linearDamping);
    constraint->setLinearLimitSoftness(m_linearLimitSoftness);
    constraint->setLinearXMotor(m_motors.at(0));
    constraint->setLinearYMotor(m_motors.at(1));
    constraint->setLinearZMotor(m_motors.at(2));
    constraint->setAngularXMotor(m_motors.at(3));
    constraint->setAngularYMotor(m_motors.at(4));
    constraint->setAngularZMotor(m_motors.at(5));
    constraint->setAngularMaxLimitForce(m_angularMaxLimitForce);
}
