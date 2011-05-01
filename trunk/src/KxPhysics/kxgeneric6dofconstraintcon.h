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

#ifndef KXGENERIC6DOFCONSTRAINTCON_H
#define KXGENERIC6DOFCONSTRAINTCON_H

#include <QtCore/qobject.h>
#include <QtCore/qbitarray.h>
#include <QtGui/qquaternion.h>
#include <QtDeclarative/qdeclarative.h>

class KxRigidBody;
class KxGeneric6DofConstraint;

class KxGeneric6DofConstraintCon : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVector3D positionInB READ positionInB WRITE setPositionInB FINAL);
    Q_PROPERTY(QVector3D positionInA READ positionInA WRITE setPositionInA FINAL);
    Q_PROPERTY(QQuaternion rotationInA READ rotationInA WRITE setRotationInA FINAL);
    Q_PROPERTY(QQuaternion rotationInB READ rotationInB WRITE setRotationInB FINAL);
    Q_PROPERTY(QVector3D linearLowerLimit READ linearLowerLimit WRITE setLinearLowerLimit FINAL);
    Q_PROPERTY(QVector3D linearUpperLimit READ linearUpperLimit WRITE setLinearUpperLimit FINAL);
    Q_PROPERTY(QVector3D angularLowerLimit READ angularLowerLimit WRITE setAngularLowerLimit FINAL);
    Q_PROPERTY(QVector3D angularUpperLimit READ angularUpperLimit WRITE setAngularUpperLimit FINAL);
    Q_PROPERTY(QVector3D angularDamping READ angularDamping WRITE setAngularDamping FINAL);
    Q_PROPERTY(QVector3D angularLimitSoftness READ angularLimitSoftness WRITE setAngularLimitSoftness FINAL);
    Q_PROPERTY(QVector3D angularNormalCFM READ angularNormalCFM WRITE setAngularNormalCFM FINAL);
    Q_PROPERTY(QVector3D angularStopERP READ angularStopERP WRITE setAngularStopERP FINAL);
    Q_PROPERTY(QVector3D angularStopCFM READ angularStopCFM WRITE setAngularStopCFM FINAL);
    Q_PROPERTY(QVector3D angularBounce READ angularBounce WRITE setAngularBounce FINAL);
    Q_PROPERTY(QVector3D angularMaxLimitForce READ angularMaxLimitForce WRITE setAngularMaxLimitForce FINAL);
    Q_PROPERTY(bool angularXMotor READ isAngularXMotor WRITE setAngularXMotor FINAL);
    Q_PROPERTY(bool angularYMotor READ isAngularYMotor WRITE setAngularYMotor FINAL);
    Q_PROPERTY(bool angularZMotor READ isAngularZMotor WRITE setAngularZMotor FINAL);
    Q_PROPERTY(QVector3D linearNormalCFM READ linearNormalCFM WRITE setLinearNormalCFM FINAL);
    Q_PROPERTY(QVector3D linearStopERP READ linearStopERP WRITE setLinearStopERP FINAL);
    Q_PROPERTY(QVector3D linearStopCFM READ linearStopCFM WRITE setLinearStopCFM FINAL);
    Q_PROPERTY(qreal linearRestitution READ linearRestitution WRITE setLinearRestitution FINAL);
    Q_PROPERTY(qreal linearDamping READ linearDamping WRITE setLinearDamping FINAL);
    Q_PROPERTY(qreal linearLimitSoftness READ linearLimitSoftness WRITE setLinearLimitSoftness FINAL);
    Q_PROPERTY(bool linearXMotor READ isLinearXMotor WRITE setLinearXMotor FINAL);
    Q_PROPERTY(bool linearYMotor READ isLinearYMotor WRITE setLinearYMotor FINAL);
    Q_PROPERTY(bool linearZMotor READ isLinearZMotor WRITE setLinearZMotor FINAL);

public:
    explicit KxGeneric6DofConstraintCon(QObject *parent = 0);
    inline const QVector3D& positionInA() const;
    inline const QQuaternion& rotationInA() const;
    inline const QVector3D& positionInB() const;
    inline const QQuaternion& rotationInB() const;
    inline const QVector3D& linearUpperLimit() const;
    inline const QVector3D& linearLowerLimit() const;
    inline const QVector3D& angularUpperLimit() const;
    inline const QVector3D& angularLowerLimit() const;
    inline const QVector3D& angularMaxLimitForce() const;

    inline void setPositionInA(const QVector3D& value);
    inline void setRotationInA(const QQuaternion& value);
    inline void setPositionInB(const QVector3D& value);
    inline void setRotationInB(const QQuaternion& value);
    inline void setLinearUpperLimit(const QVector3D& value);
    inline void setLinearLowerLimit(const QVector3D& value);
    inline void setAngularUpperLimit(const QVector3D& value);
    inline void setAngularLowerLimit(const QVector3D& value);
    inline void setAngularMaxLimitForce(const QVector3D& value);

    //angular motor
    inline const QVector3D& angularDamping() const;
    inline const QVector3D& angularLimitSoftness() const;
    inline const QVector3D& angularNormalCFM() const;
    inline const QVector3D& angularStopERP() const;
    inline const QVector3D& angularStopCFM() const;
    inline const QVector3D& angularBounce() const;
    inline bool isAngularXMotor() const;
    inline bool isAngularYMotor() const;
    inline bool isAngularZMotor() const;
    inline void setAngularDamping(const QVector3D& value);
    inline void setAngularLimitSoftness(const QVector3D& value);
    inline void setAngularNormalCFM(const QVector3D& value);
    inline void setAngularStopERP(const QVector3D& value);
    inline void setAngularStopCFM(const QVector3D& value);
    inline void setAngularBounce(const QVector3D& value);
    inline void setAngularXMotor(bool enable);
    inline void setAngularYMotor(bool enable);
    inline void setAngularZMotor(bool enable);
    //linear motor
    inline const QVector3D& linearNormalCFM() const;
    inline const QVector3D& linearStopERP() const;
    inline const QVector3D& linearStopCFM() const;
    inline qreal linearRestitution() const;
    inline qreal linearDamping() const;
    inline qreal linearLimitSoftness() const;
    inline bool isLinearXMotor() const;
    inline bool isLinearYMotor() const;
    inline bool isLinearZMotor() const;
    inline void setLinearNormalCFM(const QVector3D& value);
    inline void setLinearStopERP(const QVector3D& value);
    inline void setLinearStopCFM(const QVector3D& value);
    inline void setLinearRestitution(qreal value);
    inline void setLinearDamping(qreal value);
    inline void setLinearLimitSoftness(qreal value);
    inline void setLinearXMotor(bool enable);
    inline void setLinearYMotor(bool enable);
    inline void setLinearZMotor(bool enable);
    KxGeneric6DofConstraint* create(KxRigidBody *aBody, KxRigidBody *bBody, QObject *parent) const;
    Q_INVOKABLE KxGeneric6DofConstraint* create(QObject *aBody, QObject *bBody, QObject *paren) const;

protected:
    void setup6DofConstraintProperties(KxGeneric6DofConstraint *constraint) const;
    QVector3D m_posInA;
    QQuaternion m_rotInA;
    QVector3D m_posInB;
    QQuaternion m_rotInB;
    QVector3D m_linearUpperLimit;
    QVector3D m_linearLowerLimit;
    QVector3D m_angularUpperLimit;
    QVector3D m_angularLowerLimit;
    QVector3D m_angularDamping;
    QVector3D m_angularLimitSoftness;
    QVector3D m_angularNormalCFM;
    QVector3D m_angularStopERP;
    QVector3D m_angularStopCFM;
    QVector3D m_angularBounce;
    QVector3D m_angularMaxLimitForce;
    QVector3D m_linearNormalCFM;
    QVector3D m_linearStopERP;
    QVector3D m_linearStopCFM;
    qreal m_linearRestitution;
    qreal m_linearDamping;
    qreal m_linearLimitSoftness;
    QBitArray m_motors;
};

QML_DECLARE_TYPE(KxGeneric6DofConstraintCon);


inline const QVector3D& KxGeneric6DofConstraintCon::angularMaxLimitForce() const
{
    return m_angularMaxLimitForce;
}

inline bool KxGeneric6DofConstraintCon::isAngularXMotor() const
{
    return m_motors.at(3);
}

inline bool KxGeneric6DofConstraintCon::isAngularYMotor() const
{
    return m_motors.at(4);
}

inline bool KxGeneric6DofConstraintCon::isAngularZMotor() const
{
    return m_motors.at(5);
}

inline bool KxGeneric6DofConstraintCon::isLinearXMotor() const
{
    return m_motors.at(0);
}

inline bool KxGeneric6DofConstraintCon::isLinearYMotor() const
{
    return m_motors.at(1);
}

inline bool KxGeneric6DofConstraintCon::isLinearZMotor() const
{
    return m_motors.at(2);
}


inline void KxGeneric6DofConstraintCon::setAngularMaxLimitForce(const QVector3D &value)
{
    m_angularMaxLimitForce = value;
}

inline void KxGeneric6DofConstraintCon::setAngularXMotor(bool enable)
{
    m_motors.setBit(3, enable);
}

inline void KxGeneric6DofConstraintCon::setAngularYMotor(bool enable)
{
    m_motors.setBit(4, enable);
}

inline void KxGeneric6DofConstraintCon::setAngularZMotor(bool enable)
{
    m_motors.setBit(5, enable);
}

inline void KxGeneric6DofConstraintCon::setLinearXMotor(bool enable)
{
    m_motors.setBit(0, enable);
}

inline void KxGeneric6DofConstraintCon::setLinearYMotor(bool enable)
{
    m_motors.setBit(1, enable);
}

inline void KxGeneric6DofConstraintCon::setLinearZMotor(bool enable)
{
    m_motors.setBit(2, enable);
}

inline const QVector3D& KxGeneric6DofConstraintCon::positionInA() const
{
    return m_posInA;
}

inline const QQuaternion& KxGeneric6DofConstraintCon::rotationInA() const
{
    return m_rotInA;
}

inline const QVector3D& KxGeneric6DofConstraintCon::positionInB() const
{
    return m_posInB;
}

inline const QQuaternion& KxGeneric6DofConstraintCon::rotationInB() const
{
    return m_rotInB;
}

inline const QVector3D& KxGeneric6DofConstraintCon::linearUpperLimit() const
{
    return m_linearUpperLimit;
}

inline const QVector3D& KxGeneric6DofConstraintCon::linearLowerLimit() const
{
    return m_linearLowerLimit;
}

inline const QVector3D& KxGeneric6DofConstraintCon::angularUpperLimit() const
{
    return m_angularUpperLimit;
}

inline const QVector3D& KxGeneric6DofConstraintCon::angularLowerLimit() const
{
    return m_angularLowerLimit;
}

inline void KxGeneric6DofConstraintCon::setPositionInA(const QVector3D& value)
{
    m_posInA = value;
}

inline void KxGeneric6DofConstraintCon::setRotationInA(const QQuaternion& value)
{
    m_rotInA = value;
}

inline void KxGeneric6DofConstraintCon::setPositionInB(const QVector3D& value)
{
    m_posInB = value;
}

inline void KxGeneric6DofConstraintCon::setRotationInB(const QQuaternion& value)
{
    m_rotInB = value;
}

inline void KxGeneric6DofConstraintCon::setLinearUpperLimit(const QVector3D& value)
{
    m_linearUpperLimit = value;
}

inline void KxGeneric6DofConstraintCon::setLinearLowerLimit(const QVector3D& value)
{
    m_linearLowerLimit = value;
}

inline void KxGeneric6DofConstraintCon::setAngularUpperLimit(const QVector3D& value)
{
    m_angularUpperLimit = value;
}

inline void KxGeneric6DofConstraintCon::setAngularLowerLimit(const QVector3D& value)
{
    m_angularLowerLimit = value;
}

//angul motor
inline const QVector3D& KxGeneric6DofConstraintCon::angularDamping() const
{
    return m_angularDamping;
}

inline const QVector3D& KxGeneric6DofConstraintCon::angularLimitSoftness() const
{
    return m_angularLimitSoftness;
}

inline const QVector3D& KxGeneric6DofConstraintCon::angularNormalCFM() const
{
    return m_angularStopCFM;
}

inline const QVector3D& KxGeneric6DofConstraintCon::angularStopERP() const
{
    return m_angularStopERP;
}

inline const QVector3D& KxGeneric6DofConstraintCon::angularStopCFM() const
{
    return m_angularStopCFM;
}

inline const QVector3D& KxGeneric6DofConstraintCon::angularBounce() const
{
    return m_angularBounce;
}

inline void KxGeneric6DofConstraintCon::setAngularDamping(const QVector3D& value)
{
    m_angularDamping = value;
}

inline void KxGeneric6DofConstraintCon::setAngularLimitSoftness(const QVector3D& value)
{
    m_angularLimitSoftness = value;
}

inline void KxGeneric6DofConstraintCon::setAngularNormalCFM(const QVector3D& value)
{
    m_angularNormalCFM = value;
}

inline void KxGeneric6DofConstraintCon::setAngularStopERP(const QVector3D& value)
{
    m_angularStopERP = value;
}

inline void KxGeneric6DofConstraintCon::setAngularStopCFM(const QVector3D& value)
{
    m_angularStopCFM = value;
}

inline void KxGeneric6DofConstraintCon::setAngularBounce(const QVector3D& value)
{
    m_angularBounce = value;
}

//linear motor
inline const QVector3D& KxGeneric6DofConstraintCon::linearNormalCFM() const
{
    return m_linearNormalCFM;
}

inline const QVector3D& KxGeneric6DofConstraintCon::linearStopERP() const
{
    return m_linearStopCFM;
}

inline const QVector3D& KxGeneric6DofConstraintCon::linearStopCFM() const
{
    return m_linearStopCFM;
}

inline qreal KxGeneric6DofConstraintCon::linearRestitution() const
{
    return m_linearRestitution;
}

inline qreal KxGeneric6DofConstraintCon::linearDamping() const
{
    return m_linearDamping;
}

inline qreal KxGeneric6DofConstraintCon::linearLimitSoftness() const
{
    return m_linearLimitSoftness;
}

inline void KxGeneric6DofConstraintCon::setLinearNormalCFM(const QVector3D& value)
{
    m_linearNormalCFM = value;
}

inline void KxGeneric6DofConstraintCon::setLinearStopERP(const QVector3D& value)
{
    m_linearStopERP = value;
}

inline void KxGeneric6DofConstraintCon::setLinearStopCFM(const QVector3D& value)
{
    m_linearNormalCFM = value;
}

inline void KxGeneric6DofConstraintCon::setLinearRestitution(qreal value)
{
    m_linearRestitution = value;
}

inline void KxGeneric6DofConstraintCon::setLinearDamping(qreal value)
{
    m_linearDamping = value;
}

inline void KxGeneric6DofConstraintCon::setLinearLimitSoftness(qreal value)
{
    m_linearLimitSoftness = value;
}


#endif // KXGENERIC6DOFCONSTRAINTCON_H
