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

#ifndef KXGENERIC6DOFCONSTRAINT_H
#define KXGENERIC6DOFCONSTRAINT_H

#include "kxtypedconstraint.h"
#include "kxbulletutil.h"
#include <btBulletDynamicsCommon.h>

class KxGeneric6DofConstraint : public KxTypedConstraint
{
    Q_OBJECT
    Q_PROPERTY(QVector3D angularLowerLimit READ angularLowerLimit WRITE setAngularLowerLimit FINAL)
    Q_PROPERTY(QVector3D angularUpperLimit READ angularUpperLimit WRITE setAngularUpperLimit FINAL)
    Q_PROPERTY(QVector3D linearLowerLimit READ linearLowerLimit WRITE setLinearLowerLimit FINAL)
    Q_PROPERTY(QVector3D linearUpperLimit READ linearUpperLimit WRITE setLinearUpperLimit FINAL)
    Q_PROPERTY(QVector3D positionInB READ positionInB WRITE setPositionInB FINAL)
    Q_PROPERTY(QVector3D positionInA READ positionInA WRITE setPositionInA FINAL)
    Q_PROPERTY(QQuaternion rotationInA READ rotationInA WRITE setRotationInA FINAL)
    Q_PROPERTY(QQuaternion rotationInB READ rotationInB WRITE setRotationInB FINAL)
    //angular motor
    Q_PROPERTY(QVector3D angularTargetVelocity READ angularTargetVelocity WRITE setAngularTargetVelocity FINAL)
    Q_PROPERTY(QVector3D angularMaxMotorForce READ angularMaxMotorForce WRITE setAngularMaxMotorForce FINAL)
    Q_PROPERTY(QVector3D angularMaxLimitForce READ angularMaxLimitForce WRITE setAngularMaxLimitForce FINAL)
    Q_PROPERTY(QVector3D angularDamping READ angularDamping WRITE setAngularDamping FINAL)
    Q_PROPERTY(QVector3D angularLimitSoftness READ angularLimitSoftness WRITE setAngularLimitSoftness FINAL)
    Q_PROPERTY(QVector3D angularNormalCFM READ angularNormalCFM WRITE setAngularNormalCFM FINAL)
    Q_PROPERTY(QVector3D angularStopERP READ angularStopERP WRITE setAngularStopERP FINAL)
    Q_PROPERTY(QVector3D angularStopCFM READ angularStopCFM WRITE setAngularStopCFM FINAL)
    Q_PROPERTY(QVector3D angularBounce READ angularBounce WRITE setAngularBounce FINAL)
    Q_PROPERTY(QVector3D angularCurrentPosition READ angularCurrentPosition WRITE setAngularCurrentPosition FINAL)
    Q_PROPERTY(bool angularXMotor READ isAngularXMotor WRITE setAngularXMotor FINAL)
    Q_PROPERTY(bool angularYMotor READ isAngularYMotor WRITE setAngularYMotor FINAL)
    Q_PROPERTY(bool angularZMotor READ isAngularZMotor WRITE setAngularZMotor FINAL)
    Q_PROPERTY(QVector3D angularMaxLimitForce READ angularMaxLimitForce WRITE setAngularMaxLimitForce FINAL)
    //linear motor
    Q_PROPERTY(QVector3D linearTargetVelocity READ linearTargetVelocity WRITE setLinearTargetVelocity FINAL)
    Q_PROPERTY(QVector3D linearAccumulatedImpulse READ linearAccumulatedImpulse WRITE setLinearAccumulatedImpulse FINAL)
    Q_PROPERTY(QVector3D linearMaxMotorForce READ linearMaxMotorForce WRITE setLinearMaxMotorForce FINAL)
    Q_PROPERTY(QVector3D linearNormalCFM READ linearNormalCFM WRITE setLinearNormalCFM FINAL)
    Q_PROPERTY(QVector3D linearStopERP READ linearStopERP WRITE setLinearStopERP FINAL)
    Q_PROPERTY(QVector3D linearStopCFM READ linearStopCFM WRITE setLinearStopCFM FINAL)
    Q_PROPERTY(qreal linearRestitution READ linearRestitution WRITE setLinearRestitution FINAL)
    Q_PROPERTY(qreal linearDamping READ linearDamping WRITE setLinearDamping FINAL)
    Q_PROPERTY(qreal linearLimitSoftness READ linearLimitSoftness WRITE setLinearLimitSoftness FINAL)
    Q_PROPERTY(bool linearXMotor READ isLinearXMotor WRITE setLinearXMotor FINAL)
    Q_PROPERTY(bool linearYMotor READ isLinearYMotor WRITE setLinearYMotor FINAL)
    Q_PROPERTY(bool linearZMotor READ isLinearZMotor WRITE setLinearZMotor FINAL)

public:
    //TODO remove pos/rot
    explicit KxGeneric6DofConstraint(KxRigidBody *rbA, KxRigidBody *rbB,
                                     const QVector3D &posInA, const QQuaternion& rotInA,
                                     const QVector3D &posInB, const QQuaternion& rotInB,
                                     QObject *parent = 0);
    ~KxGeneric6DofConstraint();
    virtual KxRigidBody *aBody() const;
    virtual KxRigidBody *bBody() const;
    inline QVector3D linearUpperLimit() const;
    inline QVector3D linearLowerLimit() const;
    inline QVector3D angularUpperLimit() const;
    inline QVector3D angularLowerLimit() const;
    inline QVector3D positionInA() const;
    inline QQuaternion rotationInA() const;
    inline QVector3D positionInB() const;
    inline QQuaternion rotationInB() const;
    inline void setLinearUpperLimit(const QVector3D& value);
    inline void setLinearLowerLimit(const QVector3D& value);
    inline void setAngularUpperLimit(const QVector3D& value);
    inline void setAngularLowerLimit(const QVector3D& value);
    inline void setPositionInA(const QVector3D& value);
    inline void setRotationInA(const QQuaternion& value);
    inline void setPositionInB(const QVector3D& value);
    inline void setRotationInB(const QQuaternion& value);
    //angular motor
    inline QVector3D angularTargetVelocity() const;
    inline QVector3D angularMaxMotorForce() const;
    inline QVector3D angularMaxLimitForce() const;
    inline QVector3D angularDamping() const;
    inline QVector3D angularLimitSoftness() const;
    inline QVector3D angularNormalCFM() const;
    inline QVector3D angularStopERP() const;
    inline QVector3D angularStopCFM() const;
    inline QVector3D angularBounce() const;
    inline QVector3D angularCurrentPosition() const;
    inline bool isAngularXMotor() const;
    inline bool isAngularYMotor() const;
    inline bool isAngularZMotor() const;
    inline void setAngularTargetVelocity(const QVector3D& value);
    inline void setAngularMaxMotorForce(const QVector3D& value);
    inline void setAngularMaxLimitForce(const QVector3D& value);
    inline void setAngularDamping(const QVector3D& value);
    inline void setAngularLimitSoftness(const QVector3D& value);
    inline void setAngularNormalCFM(const QVector3D& value);
    inline void setAngularStopERP(const QVector3D& value);
    inline void setAngularStopCFM(const QVector3D& value);
    inline void setAngularBounce(const QVector3D& value);
    inline void setAngularCurrentPosition(const QVector3D& value);
    inline void setAngularXMotor(bool enable);
    inline void setAngularYMotor(bool enable);
    inline void setAngularZMotor(bool enable);

    //linear motor
    inline QVector3D linearTargetVelocity() const;
    inline QVector3D linearAccumulatedImpulse() const;
    inline QVector3D linearMaxMotorForce() const;
    inline QVector3D linearNormalCFM() const;
    inline QVector3D linearStopERP() const;
    inline QVector3D linearStopCFM() const;
    inline qreal linearRestitution() const;
    inline qreal linearDamping() const;
    inline qreal linearLimitSoftness() const;
    inline bool isLinearXMotor() const;
    inline bool isLinearYMotor() const;
    inline bool isLinearZMotor() const;
    inline void setLinearAccumulatedImpulse(const QVector3D& value);
    inline void setLinearTargetVelocity(const QVector3D& value);
    inline void setLinearMaxMotorForce(const QVector3D& value);
    inline void setLinearNormalCFM(const QVector3D& value);
    inline void setLinearStopERP(const QVector3D& value);
    inline void setLinearStopCFM(const QVector3D& value);
    inline void setLinearRestitution(qreal value);
    inline void setLinearDamping(qreal value);
    inline void setLinearLimitSoftness(qreal value);
    inline void setLinearXMotor(bool enable);
    inline void setLinearYMotor(bool enable);
    inline void setLinearZMotor(bool enable);

protected:
    KxGeneric6DofConstraint(QObject *parent);
    inline virtual btTypedConstraint* internalBtConstraint() const;
    btGeneric6DofConstraint *m_constraint;

    friend class KxGeneric6DofConstraintCon;
};

Q_DECLARE_METATYPE(KxGeneric6DofConstraint*);


inline QVector3D KxGeneric6DofConstraint::positionInA() const
{
    return KxBulletUtil::convertScaled(m_constraint->getFrameOffsetA().getOrigin());
}

inline QVector3D KxGeneric6DofConstraint::positionInB() const
{
    return KxBulletUtil::convertScaled(m_constraint->getFrameOffsetB().getOrigin());
}

inline QQuaternion KxGeneric6DofConstraint::rotationInA() const
{
    return KxBulletUtil::convert(m_constraint->getFrameOffsetA().getRotation());
}

inline QQuaternion KxGeneric6DofConstraint::rotationInB() const
{
    return KxBulletUtil::convert(m_constraint->getFrameOffsetB().getRotation());
}

inline void KxGeneric6DofConstraint::setPositionInA(const QVector3D &value)
{
    m_constraint->getFrameOffsetA().setOrigin(KxBulletUtil::convertScaled(value));
    m_constraint->calculateTransforms();
}

inline void KxGeneric6DofConstraint::setPositionInB(const QVector3D &value)
{
    m_constraint->getFrameOffsetB().setOrigin(KxBulletUtil::convertScaled(value));
    m_constraint->calculateTransforms();
}

inline void KxGeneric6DofConstraint::setRotationInA(const QQuaternion &value)
{
    m_constraint->getFrameOffsetA().setRotation(KxBulletUtil::convert(value));
    m_constraint->calculateTransforms();
}

inline void KxGeneric6DofConstraint::setRotationInB(const QQuaternion &value)
{
    m_constraint->getFrameOffsetB().setRotation(KxBulletUtil::convert(value));
    m_constraint->calculateTransforms();
}

inline bool KxGeneric6DofConstraint::isAngularXMotor() const
{
    return m_constraint->getRotationalLimitMotor(0)->m_enableMotor;
}

inline bool KxGeneric6DofConstraint::isAngularYMotor() const
{
    return m_constraint->getRotationalLimitMotor(1)->m_enableMotor;
}

inline bool KxGeneric6DofConstraint::isAngularZMotor() const
{
    return m_constraint->getRotationalLimitMotor(2)->m_enableMotor;
}

inline bool KxGeneric6DofConstraint::isLinearXMotor() const
{
    return m_constraint->getTranslationalLimitMotor()->m_enableMotor[0];
}

inline bool KxGeneric6DofConstraint::isLinearYMotor() const
{
    return m_constraint->getTranslationalLimitMotor()->m_enableMotor[1];
}

inline bool KxGeneric6DofConstraint::isLinearZMotor() const
{
    return m_constraint->getTranslationalLimitMotor()->m_enableMotor[2];
}

inline void KxGeneric6DofConstraint::setAngularXMotor(bool enable)
{
    m_constraint->getRotationalLimitMotor(0)->m_enableMotor = enable;
}

inline void KxGeneric6DofConstraint::setAngularYMotor(bool enable)
{
    m_constraint->getRotationalLimitMotor(1)->m_enableMotor = enable;
}

inline void KxGeneric6DofConstraint::setAngularZMotor(bool enable)
{
    m_constraint->getRotationalLimitMotor(2)->m_enableMotor = enable;
}

inline void KxGeneric6DofConstraint::setLinearXMotor(bool enable)
{
    m_constraint->getTranslationalLimitMotor()->m_enableMotor[0] = enable;
}

inline void KxGeneric6DofConstraint::setLinearYMotor(bool enable)
{
    m_constraint->getTranslationalLimitMotor()->m_enableMotor[1] = enable;
}

inline void KxGeneric6DofConstraint::setLinearZMotor(bool enable)
{
    m_constraint->getTranslationalLimitMotor()->m_enableMotor[2] = enable;
}

inline btTypedConstraint *KxGeneric6DofConstraint::internalBtConstraint() const
{
    return m_constraint;
}

inline void KxGeneric6DofConstraint::setLinearUpperLimit(const QVector3D &value)
{
    m_constraint->setLinearUpperLimit(KxBulletUtil::convertScaled(value));
}

inline void KxGeneric6DofConstraint::setLinearLowerLimit(const QVector3D &value)
{
    m_constraint->setLinearLowerLimit(KxBulletUtil::convertScaled(value));
}

inline void KxGeneric6DofConstraint::setAngularLowerLimit(const QVector3D &value)
{
    m_constraint->setAngularLowerLimit(KxBulletUtil::convert(value));
}

inline void KxGeneric6DofConstraint::setAngularUpperLimit(const QVector3D &value)
{
    m_constraint->setAngularUpperLimit(KxBulletUtil::convert(value));
}

inline QVector3D KxGeneric6DofConstraint::linearLowerLimit() const
{
    return KxBulletUtil::convertScaled(m_constraint->getTranslationalLimitMotor()->m_lowerLimit);
}

inline QVector3D KxGeneric6DofConstraint::linearUpperLimit() const
{
    return KxBulletUtil::convertScaled(m_constraint->getTranslationalLimitMotor()->m_upperLimit);
}

inline QVector3D KxGeneric6DofConstraint::angularLowerLimit() const
{
    return QVector3D(m_constraint->getRotationalLimitMotor(0)->m_loLimit,
                     m_constraint->getRotationalLimitMotor(1)->m_loLimit,
                     m_constraint->getRotationalLimitMotor(2)->m_loLimit);
}

inline QVector3D KxGeneric6DofConstraint::angularUpperLimit() const
{
    return QVector3D(m_constraint->getRotationalLimitMotor(0)->m_hiLimit,
                     m_constraint->getRotationalLimitMotor(1)->m_hiLimit,
                     m_constraint->getRotationalLimitMotor(2)->m_hiLimit);
}

inline QVector3D KxGeneric6DofConstraint::angularTargetVelocity() const
{
    return QVector3D(m_constraint->getRotationalLimitMotor(0)->m_targetVelocity,
                     m_constraint->getRotationalLimitMotor(1)->m_targetVelocity,
                     m_constraint->getRotationalLimitMotor(2)->m_targetVelocity);
}

inline QVector3D KxGeneric6DofConstraint::angularMaxMotorForce() const
{
    return QVector3D(m_constraint->getRotationalLimitMotor(0)->m_maxMotorForce,
                     m_constraint->getRotationalLimitMotor(1)->m_maxMotorForce,
                     m_constraint->getRotationalLimitMotor(2)->m_maxMotorForce);
}

inline QVector3D KxGeneric6DofConstraint::angularMaxLimitForce() const
{
    return QVector3D(m_constraint->getRotationalLimitMotor(0)->m_maxLimitForce,
                     m_constraint->getRotationalLimitMotor(1)->m_maxLimitForce,
                     m_constraint->getRotationalLimitMotor(2)->m_maxLimitForce) / KxBulletUtil::scale();
}

inline QVector3D KxGeneric6DofConstraint::angularDamping() const
{
    return QVector3D(m_constraint->getRotationalLimitMotor(0)->m_damping,
                     m_constraint->getRotationalLimitMotor(1)->m_damping,
                     m_constraint->getRotationalLimitMotor(2)->m_damping);
}

inline QVector3D KxGeneric6DofConstraint::angularLimitSoftness() const
{
    return QVector3D(m_constraint->getRotationalLimitMotor(0)->m_limitSoftness,
                     m_constraint->getRotationalLimitMotor(1)->m_limitSoftness,
                     m_constraint->getRotationalLimitMotor(2)->m_limitSoftness);
}

inline QVector3D KxGeneric6DofConstraint::angularNormalCFM() const
{
    return QVector3D(m_constraint->getRotationalLimitMotor(0)->m_normalCFM,
                     m_constraint->getRotationalLimitMotor(1)->m_normalCFM,
                     m_constraint->getRotationalLimitMotor(2)->m_normalCFM);
}

inline QVector3D KxGeneric6DofConstraint::angularStopERP() const
{
    return QVector3D(m_constraint->getRotationalLimitMotor(0)->m_stopERP,
                     m_constraint->getRotationalLimitMotor(1)->m_stopERP,
                     m_constraint->getRotationalLimitMotor(2)->m_stopERP);
}

inline QVector3D KxGeneric6DofConstraint::angularStopCFM() const
{
    return QVector3D(m_constraint->getRotationalLimitMotor(0)->m_stopCFM,
                     m_constraint->getRotationalLimitMotor(1)->m_stopCFM,
                     m_constraint->getRotationalLimitMotor(2)->m_stopCFM);
}

inline QVector3D KxGeneric6DofConstraint::angularBounce() const
{
    return QVector3D(m_constraint->getRotationalLimitMotor(0)->m_bounce,
                     m_constraint->getRotationalLimitMotor(1)->m_bounce,
                     m_constraint->getRotationalLimitMotor(2)->m_bounce);
}

inline QVector3D KxGeneric6DofConstraint::angularCurrentPosition() const
{
    return QVector3D(m_constraint->getRotationalLimitMotor(0)->m_currentPosition,
                     m_constraint->getRotationalLimitMotor(1)->m_currentPosition,
                     m_constraint->getRotationalLimitMotor(2)->m_currentPosition);
}

inline void KxGeneric6DofConstraint::setAngularTargetVelocity(const QVector3D& value)
{
    m_constraint->getRotationalLimitMotor(0)->m_targetVelocity = value.x();
    m_constraint->getRotationalLimitMotor(1)->m_targetVelocity = value.y();
    m_constraint->getRotationalLimitMotor(2)->m_targetVelocity = value.z();
}

inline void KxGeneric6DofConstraint::setAngularMaxMotorForce(const QVector3D& value)
{
    m_constraint->getRotationalLimitMotor(0)->m_maxMotorForce = value.x();
    m_constraint->getRotationalLimitMotor(1)->m_maxMotorForce = value.y();
    m_constraint->getRotationalLimitMotor(2)->m_maxMotorForce = value.z();
}

inline void KxGeneric6DofConstraint::setAngularMaxLimitForce(const QVector3D& value)
{
    m_constraint->getRotationalLimitMotor(0)->m_maxLimitForce = value.x() * KxBulletUtil::scale();
    m_constraint->getRotationalLimitMotor(1)->m_maxLimitForce = value.y() * KxBulletUtil::scale();
    m_constraint->getRotationalLimitMotor(2)->m_maxLimitForce = value.z() * KxBulletUtil::scale();
}

inline void KxGeneric6DofConstraint::setAngularDamping(const QVector3D& value)
{
    m_constraint->getRotationalLimitMotor(0)->m_damping = value.x();
    m_constraint->getRotationalLimitMotor(1)->m_damping = value.y();
    m_constraint->getRotationalLimitMotor(2)->m_damping = value.z();
}

inline void KxGeneric6DofConstraint::setAngularLimitSoftness(const QVector3D& value)
{
    m_constraint->getRotationalLimitMotor(0)->m_limitSoftness = value.x();
    m_constraint->getRotationalLimitMotor(1)->m_limitSoftness = value.y();
    m_constraint->getRotationalLimitMotor(2)->m_limitSoftness = value.z();
}

inline void KxGeneric6DofConstraint::setAngularNormalCFM(const QVector3D& value)
{
    m_constraint->getRotationalLimitMotor(0)->m_normalCFM = value.x();
    m_constraint->getRotationalLimitMotor(1)->m_normalCFM = value.y();
    m_constraint->getRotationalLimitMotor(2)->m_normalCFM = value.z();
}

inline void KxGeneric6DofConstraint::setAngularStopERP(const QVector3D& value)
{
    m_constraint->getRotationalLimitMotor(0)->m_stopERP = value.x();
    m_constraint->getRotationalLimitMotor(1)->m_stopERP = value.y();
    m_constraint->getRotationalLimitMotor(2)->m_stopERP = value.z();
}

inline void KxGeneric6DofConstraint::setAngularStopCFM(const QVector3D& value)
{
    m_constraint->getRotationalLimitMotor(0)->m_stopCFM = value.x();
    m_constraint->getRotationalLimitMotor(1)->m_stopCFM = value.y();
    m_constraint->getRotationalLimitMotor(2)->m_stopCFM = value.z();
}

inline void KxGeneric6DofConstraint::setAngularBounce(const QVector3D& value)
{
    m_constraint->getRotationalLimitMotor(0)->m_bounce = value.x();
    m_constraint->getRotationalLimitMotor(1)->m_bounce = value.y();
    m_constraint->getRotationalLimitMotor(2)->m_bounce = value.z();
}

inline void KxGeneric6DofConstraint::setAngularCurrentPosition(const QVector3D& value)
{
    m_constraint->getRotationalLimitMotor(0)->m_currentPosition = value.x();
    m_constraint->getRotationalLimitMotor(1)->m_currentPosition = value.y();
    m_constraint->getRotationalLimitMotor(2)->m_currentPosition = value.z();
}

inline QVector3D KxGeneric6DofConstraint::linearTargetVelocity() const
{
    return KxBulletUtil::convertScaled(m_constraint->getTranslationalLimitMotor()->m_targetVelocity);
}

inline QVector3D KxGeneric6DofConstraint::linearAccumulatedImpulse() const
{
    return KxBulletUtil::convertScaled(m_constraint->getTranslationalLimitMotor()->m_accumulatedImpulse);
}

inline QVector3D KxGeneric6DofConstraint::linearMaxMotorForce() const
{
    return KxBulletUtil::convertScaled(m_constraint->getTranslationalLimitMotor()->m_maxMotorForce);
}

inline QVector3D KxGeneric6DofConstraint::linearNormalCFM() const
{
    return KxBulletUtil::convert(m_constraint->getTranslationalLimitMotor()->m_normalCFM);
}

inline QVector3D KxGeneric6DofConstraint::linearStopERP() const
{
    return KxBulletUtil::convert(m_constraint->getTranslationalLimitMotor()->m_stopERP);
}

inline QVector3D KxGeneric6DofConstraint::linearStopCFM() const
{
    return KxBulletUtil::convert(m_constraint->getTranslationalLimitMotor()->m_stopCFM);
}

inline qreal KxGeneric6DofConstraint::linearRestitution() const
{
    return m_constraint->getTranslationalLimitMotor()->m_restitution;
}

inline qreal KxGeneric6DofConstraint::linearDamping() const
{
    return m_constraint->getTranslationalLimitMotor()->m_damping;
}

inline qreal KxGeneric6DofConstraint::linearLimitSoftness() const
{
    return m_constraint->getTranslationalLimitMotor()->m_limitSoftness;
}

inline void KxGeneric6DofConstraint::setLinearTargetVelocity(const QVector3D& value)
{
    m_constraint->getTranslationalLimitMotor()->m_targetVelocity = KxBulletUtil::convertScaled(value);
}

inline void KxGeneric6DofConstraint::setLinearAccumulatedImpulse(const QVector3D& value)
{
    m_constraint->getTranslationalLimitMotor()->m_accumulatedImpulse = KxBulletUtil::convertScaled(value);
}

inline void KxGeneric6DofConstraint::setLinearMaxMotorForce(const QVector3D& value)
{
    m_constraint->getTranslationalLimitMotor()->m_maxMotorForce = KxBulletUtil::convertScaled(value);
}

inline void KxGeneric6DofConstraint::setLinearNormalCFM(const QVector3D& value)
{
    m_constraint->getTranslationalLimitMotor()->m_normalCFM = KxBulletUtil::convert(value);
}

inline void KxGeneric6DofConstraint::setLinearStopERP(const QVector3D& value)
{
    m_constraint->getTranslationalLimitMotor()->m_stopERP = KxBulletUtil::convert(value);
}

inline void KxGeneric6DofConstraint::setLinearStopCFM(const QVector3D& value)
{
    m_constraint->getTranslationalLimitMotor()->m_stopCFM = KxBulletUtil::convert(value);
}

inline void KxGeneric6DofConstraint::setLinearRestitution(qreal value)
{
    m_constraint->getTranslationalLimitMotor()->m_restitution = value;
}

inline void KxGeneric6DofConstraint::setLinearDamping(qreal value)
{
    m_constraint->getTranslationalLimitMotor()->m_damping = value;
}

inline void KxGeneric6DofConstraint::setLinearLimitSoftness(qreal value)
{
    m_constraint->getTranslationalLimitMotor()->m_limitSoftness = value;
}


#endif // KXGENERIC6DOFCONSTRAINT_H
