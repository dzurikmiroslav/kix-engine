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

#ifndef KXGENERIC6DOFSPRINGCONSTRAINT_H
#define KXGENERIC6DOFSPRINGCONSTRAINT_H

#include "kxgeneric6dofconstraint.h"

class KxGeneric6DofSpringConstraint : public KxGeneric6DofConstraint
{
    Q_OBJECT
    Q_PROPERTY(QVector3D angularEquilibriumPoint READ angularEquilibriumPoint WRITE setAngularEquilibriumPoint FINAL)
    Q_PROPERTY(QVector3D angularStiffness READ angularStiffness WRITE setAngularStiffness FINAL)
    Q_PROPERTY(QVector3D angularSpringDamping READ angularSpringDamping WRITE setAngularSpringDamping FINAL)
    Q_PROPERTY(QVector3D linearEquilibriumPoint READ linearEquilibriumPoint WRITE setLinearEquilibriumPoint FINAL)
    Q_PROPERTY(QVector3D linearStiffness READ linearStiffness WRITE setLinearStiffness FINAL)
    Q_PROPERTY(QVector3D linearSpringDamping READ linearSpringDamping WRITE setLinearSpringDamping FINAL)
    Q_PROPERTY(bool angularXSpring READ isAngularXSpring WRITE setAngularXSpring FINAL)
    Q_PROPERTY(bool angularYSpring READ isAngularYSpring WRITE setAngularYSpring FINAL)
    Q_PROPERTY(bool angularZSpring READ isAngularZSpring WRITE setAngularZSpring FINAL)
    Q_PROPERTY(bool linearXSpring READ isLinearXSpring WRITE setLinearXSpring FINAL)
    Q_PROPERTY(bool linearYSpring READ isLinearYSpring WRITE setLinearYSpring FINAL)
    Q_PROPERTY(bool linearZSpring READ isLinearZSpring WRITE setLinearZSpring FINAL)

public:
    explicit KxGeneric6DofSpringConstraint(KxRigidBody *rbA, KxRigidBody *rbB,
                                           const QVector3D &posInA, const QQuaternion& rotInA,
                                           const QVector3D &posInB, const QQuaternion& rotInB,
                                           QObject *parent = 0);
    //TODO
    inline QVector3D angularEquilibriumPoint() const;
    inline QVector3D angularStiffness() const;
    inline QVector3D angularSpringDamping() const;
    inline QVector3D linearEquilibriumPoint() const;
    inline QVector3D linearStiffness() const;
    inline QVector3D linearSpringDamping() const;
    inline bool isAngularXSpring() const;
    inline bool isAngularYSpring() const;
    inline bool isAngularZSpring() const;
    inline bool isLinearXSpring() const;
    inline bool isLinearYSpring() const;
    inline bool isLinearZSpring() const;
    inline void setAngularEquilibriumPoint(const QVector3D& value);
    inline void setAngularStiffness(const QVector3D& value);
    inline void setAngularSpringDamping(const QVector3D& value);
    inline void setLinearEquilibriumPoint(const QVector3D& value);
    inline void setLinearStiffness(const QVector3D& value);
    inline void setLinearSpringDamping(const QVector3D& value);
    inline void setAngularXSpring(bool enable);
    inline void setAngularYSpring(bool enable);
    inline void setAngularZSpring(bool enable);
    inline void setLinearXSpring(bool enable);
    inline void setLinearYSpring(bool enable);
    inline void setLinearZSpring(bool enable);
    inline void setEnableSpring(int id, bool enable);

protected:
#define m_springConstraint ((btGeneric6DofSpringConstraint*)m_constraint)

    friend class KxGeneric6DofSpringConstraintCon;
};

Q_DECLARE_METATYPE(KxGeneric6DofSpringConstraint*);


inline bool KxGeneric6DofSpringConstraint::isAngularXSpring() const
{
    return false;
}

inline bool KxGeneric6DofSpringConstraint::isAngularYSpring() const
{
    return false;
}

inline bool KxGeneric6DofSpringConstraint::isAngularZSpring() const
{
    return false;
}

inline bool KxGeneric6DofSpringConstraint::isLinearXSpring() const
{
    return false;
}

inline bool KxGeneric6DofSpringConstraint::isLinearYSpring() const
{
    return false;
}

inline bool KxGeneric6DofSpringConstraint::isLinearZSpring() const
{
    return false;
}

inline void KxGeneric6DofSpringConstraint::setAngularXSpring(bool enable)
{
    m_springConstraint->enableSpring(3, enable);
}

inline void KxGeneric6DofSpringConstraint::setAngularYSpring(bool enable)
{
    m_springConstraint->enableSpring(4, enable);
}

inline void KxGeneric6DofSpringConstraint::setAngularZSpring(bool enable)
{
    m_springConstraint->enableSpring(5, enable);
}

inline void KxGeneric6DofSpringConstraint::setLinearXSpring(bool enable)
{
    m_springConstraint->enableSpring(0, enable);
}

inline void KxGeneric6DofSpringConstraint::setLinearYSpring(bool enable)
{
    m_springConstraint->enableSpring(1, enable);
}

inline void KxGeneric6DofSpringConstraint::setLinearZSpring(bool enable)
{
    m_springConstraint->enableSpring(2, enable);
}

inline void KxGeneric6DofSpringConstraint::setEnableSpring(int index, bool value)
{
    m_springConstraint->enableSpring(index, value);
}

inline QVector3D KxGeneric6DofSpringConstraint::angularEquilibriumPoint() const
{
    return QVector3D();
}

inline QVector3D KxGeneric6DofSpringConstraint::angularStiffness() const
{
    return QVector3D();
}

inline QVector3D KxGeneric6DofSpringConstraint::angularSpringDamping() const
{
    return QVector3D();
}

inline QVector3D KxGeneric6DofSpringConstraint::linearEquilibriumPoint() const
{
    return QVector3D();
}

inline QVector3D KxGeneric6DofSpringConstraint::linearStiffness() const
{
    return QVector3D();
}

inline QVector3D KxGeneric6DofSpringConstraint::linearSpringDamping() const
{
    return QVector3D();
}

inline void KxGeneric6DofSpringConstraint::setAngularEquilibriumPoint(const QVector3D& value)
{
    m_springConstraint->setEquilibriumPoint(3, value.x());
    m_springConstraint->setEquilibriumPoint(4, value.y());
    m_springConstraint->setEquilibriumPoint(5, value.z());
}

inline void KxGeneric6DofSpringConstraint::setAngularStiffness(const QVector3D& value)
{
    m_springConstraint->setStiffness(3, value.x());
    m_springConstraint->setStiffness(4, value.y());
    m_springConstraint->setStiffness(5, value.z());
}

inline void KxGeneric6DofSpringConstraint::setAngularSpringDamping(const QVector3D& value)
{
    m_springConstraint->setDamping(3, value.x());
    m_springConstraint->setDamping(4, value.y());
    m_springConstraint->setDamping(5, value.z());
}

inline void KxGeneric6DofSpringConstraint::setLinearEquilibriumPoint(const QVector3D& value)
{
    m_springConstraint->setEquilibriumPoint(0, KxBulletUtil::scale() * value.x());
    m_springConstraint->setEquilibriumPoint(1, KxBulletUtil::scale() * value.y());
    m_springConstraint->setEquilibriumPoint(2, KxBulletUtil::scale() * value.z());
}

inline void KxGeneric6DofSpringConstraint::setLinearStiffness(const QVector3D& value)
{
    m_springConstraint->setStiffness(0, KxBulletUtil::scale() * value.x());
    m_springConstraint->setStiffness(1, KxBulletUtil::scale() * value.y());
    m_springConstraint->setStiffness(2, KxBulletUtil::scale() * value.z());
}

inline void KxGeneric6DofSpringConstraint::setLinearSpringDamping(const QVector3D& value)
{
    m_springConstraint->setDamping(0, value.x());
    m_springConstraint->setDamping(1, value.y());
    m_springConstraint->setDamping(2, value.z());
}


#endif // KXGENERIC6DOFSPRINGCONSTRAINT_H
