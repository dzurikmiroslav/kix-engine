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

#ifndef KXGENERIC6DOFSPRINGCONSTRAINTCON_H
#define KXGENERIC6DOFSPRINGCONSTRAINTCON_H

#include "kxgeneric6dofconstraintcon.h"

class KxGeneric6DofSpringConstraint;

class KxGeneric6DofSpringConstraintCon : public KxGeneric6DofConstraintCon
{
    Q_OBJECT
    Q_PROPERTY(QVector3D angularEquilibriumPoint READ angularEquilibriumPoint WRITE setAngularEquilibriumPoint FINAL);
    Q_PROPERTY(QVector3D angularStiffness READ angularStiffness WRITE setAngularStiffness FINAL);
    Q_PROPERTY(QVector3D angularSpringDamping READ angularSpringDamping WRITE setAngularSpringDamping FINAL);
    Q_PROPERTY(QVector3D linearEquilibriumPoint READ linearEquilibriumPoint WRITE setLinearEquilibriumPoint FINAL);
    Q_PROPERTY(QVector3D linearStiffness READ linearStiffness WRITE setLinearStiffness FINAL);
    Q_PROPERTY(QVector3D linearSpringDamping READ linearSpringDamping WRITE setLinearSpringDamping FINAL);
    Q_PROPERTY(bool angularXSpring READ isAngularXSpring WRITE setAngularXSpring FINAL);
    Q_PROPERTY(bool angularYSpring READ isAngularYSpring WRITE setAngularYSpring FINAL);
    Q_PROPERTY(bool angularZSpring READ isAngularZSpring WRITE setAngularZSpring FINAL);
    Q_PROPERTY(bool linearXSpring READ isLinearXSpring WRITE setLinearXSpring FINAL);
    Q_PROPERTY(bool linearYSpring READ isLinearYSpring WRITE setLinearYSpring FINAL);
    Q_PROPERTY(bool linearZSpring READ isLinearZSpring WRITE setLinearZSpring FINAL);

public:
    explicit KxGeneric6DofSpringConstraintCon(QObject *parent = 0);
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
    KxGeneric6DofSpringConstraint *create(KxRigidBody *aBody, KxRigidBody *bBody, QObject *parent) const;
    Q_INVOKABLE KxGeneric6DofSpringConstraint *create(QObject *aBody, QObject *bBody, QObject *parent) const;

private:
    QVector3D m_angularEquilibriumPoint;
    QVector3D m_angularSpringStiffness;
    QVector3D m_angularSpringDamping;
    QVector3D m_linearEquilibriumPoint;
    QVector3D m_linearSpringStiffness;
    QVector3D m_linearSpringDamping;
    QBitArray m_springs;

};


inline bool KxGeneric6DofSpringConstraintCon::isAngularXSpring() const
{
    return m_springs.at(0);
}

inline bool KxGeneric6DofSpringConstraintCon::isAngularYSpring() const
{
    return m_springs.at(1);
}

inline bool KxGeneric6DofSpringConstraintCon::isAngularZSpring() const
{
    return m_springs.at(2);
}

inline bool KxGeneric6DofSpringConstraintCon::isLinearXSpring() const
{
    return m_springs.at(3);
}

inline bool KxGeneric6DofSpringConstraintCon::isLinearYSpring() const
{
    return m_springs.at(4);
}

inline bool KxGeneric6DofSpringConstraintCon::isLinearZSpring() const
{
    return m_springs.at(5);
}

inline void KxGeneric6DofSpringConstraintCon::setAngularXSpring(bool enable)
{
    m_springs.setBit(3, enable);
}

inline void KxGeneric6DofSpringConstraintCon::setAngularYSpring(bool enable)
{
    m_springs.setBit(4, enable);
}

inline void KxGeneric6DofSpringConstraintCon::setAngularZSpring(bool enable)
{
    m_springs.setBit(5, enable);
}

inline void KxGeneric6DofSpringConstraintCon::setLinearXSpring(bool enable)
{
    m_springs.setBit(0, enable);
}

inline void KxGeneric6DofSpringConstraintCon::setLinearYSpring(bool enable)
{
    m_springs.setBit(1, enable);
}

inline void KxGeneric6DofSpringConstraintCon::setLinearZSpring(bool enable)
{
    m_springs.setBit(2, enable);
}

inline QVector3D KxGeneric6DofSpringConstraintCon::angularEquilibriumPoint() const
{
    return m_angularEquilibriumPoint;
}

inline QVector3D KxGeneric6DofSpringConstraintCon::angularStiffness() const
{
    return m_angularSpringStiffness;
}

inline QVector3D KxGeneric6DofSpringConstraintCon::angularSpringDamping() const
{
    return m_angularSpringDamping;
}

inline QVector3D KxGeneric6DofSpringConstraintCon::linearEquilibriumPoint() const
{
    return m_linearEquilibriumPoint;
}

inline QVector3D KxGeneric6DofSpringConstraintCon::linearStiffness() const
{
    return m_linearSpringStiffness;
}

inline QVector3D KxGeneric6DofSpringConstraintCon::linearSpringDamping() const
{
    return m_linearSpringDamping;
}

inline void KxGeneric6DofSpringConstraintCon::setAngularEquilibriumPoint(const QVector3D& value)
{
    m_angularEquilibriumPoint = value;
}

inline void KxGeneric6DofSpringConstraintCon::setAngularStiffness(const QVector3D& value)
{
    m_angularSpringStiffness = value;
}

inline void KxGeneric6DofSpringConstraintCon::setAngularSpringDamping(const QVector3D& value)
{
    m_angularSpringDamping = value;
}

inline void KxGeneric6DofSpringConstraintCon::setLinearEquilibriumPoint(const QVector3D& value)
{
    m_linearEquilibriumPoint = value;
}

inline void KxGeneric6DofSpringConstraintCon::setLinearStiffness(const QVector3D& value)
{
    m_linearSpringStiffness = value;
}

inline void KxGeneric6DofSpringConstraintCon::setLinearSpringDamping(const QVector3D& value)
{
    m_linearSpringDamping = value;
}

#endif // KXGENERIC6DOFSPRINGCONSTRAINTCON_H
