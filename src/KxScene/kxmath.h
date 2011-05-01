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

#ifndef KXMATH_H
#define KXMATH_H

#include <QtGui/qvector3d.h>
#include <QtGui/qquaternion.h>
#include <QtCore/qvector.h>

class KxTransform
{
public:
    KxTransform();
    KxTransform(const KxTransform &other);
    KxTransform(const QVector3D &position, const QQuaternion &roation);

    inline const QQuaternion &rotation() const;
    inline QQuaternion &rotation();
    inline void setRotation(const QQuaternion &value);

    inline const QVector3D &position() const;
    inline QVector3D &position();
    inline void setPosition(const QVector3D &value);

    inline KxTransform inverted() const;

    inline KxTransform &operator *=(const KxTransform &other);
    friend inline KxTransform operator *(const KxTransform &t1, const KxTransform &t2);
    friend inline QVector3D operator *(const KxTransform &t, const QVector3D &v);

    inline static KxTransform interpolate(const KxTransform &t1, const KxTransform &t2, qreal t);

protected:
    QQuaternion m_rotation;
    QVector3D m_position;

};

class KxAABB
{
public:
    explicit KxAABB(const QVector<QVector3D> &vertices);
    explicit KxAABB(const QVector3D &min = QVector3D(), const QVector3D &max = QVector3D());

    inline const QVector3D &max() const;
    inline QVector3D &max();
    inline void setMax(const QVector3D &max);

    inline const QVector3D &min() const;
    inline QVector3D &min();
    inline void setMin(const QVector3D &min);

    //TODO
    //bool isColide(const KxAABB &other) const;
    //bool isInside(const QVector3D &p) const;
    //qreal distance(const KxPlane &plane) const;

    const KxAABB &operator + (const KxAABB &vector);
    KxAABB &operator += (const KxAABB &vector);

protected:
    QVector3D m_max;
    QVector3D m_min;

};


inline KxTransform KxTransform::interpolate(const KxTransform &t1, const KxTransform &t2, qreal t)
{
    KxTransform trans;
    trans.m_rotation = QQuaternion::slerp(t1.m_rotation, t2.m_rotation, t);
    trans.m_position = t1.m_position + (t2.m_position - t1.m_position) * t;
    return trans;
}

inline KxTransform KxTransform::inverted() const
{
    return KxTransform(m_rotation.conjugate().rotatedVector(-m_position), m_rotation.conjugate());
}

inline KxTransform operator *(const KxTransform &t1, const KxTransform &t2)
{
    KxTransform res;
    res.m_rotation = t2.m_rotation * t1.m_rotation;
    res.m_position = t2.m_rotation.rotatedVector(t1.m_position) + t2.m_position;
    return res;
}

inline QVector3D operator *(const KxTransform &t, const QVector3D &v)
{
    return t.m_rotation.rotatedVector(v) + t.m_position;
}

inline KxTransform &KxTransform::operator *=(const KxTransform &other)
{
    m_rotation *= other.m_rotation;
    m_position = other.m_rotation.rotatedVector(m_position) + other.m_position;
    return *this;
}

inline const QQuaternion &KxTransform::rotation() const
{
    return m_rotation;
}

inline const QVector3D &KxTransform::position() const
{
    return m_position;
}

inline QQuaternion &KxTransform::rotation()
{
    return m_rotation;
}

inline QVector3D &KxTransform::position()
{
    return m_position;
}

inline void KxTransform::setRotation(const QQuaternion &value)
{
    m_rotation = value;
}

inline void KxTransform::setPosition(const QVector3D &value)
{
    m_position = value;
}

inline const QVector3D &KxAABB::max() const
{
    return m_max;
}

inline const QVector3D &KxAABB::min() const
{
    return m_min;
}

inline QVector3D &KxAABB::max()
{
    return m_max;
}

inline QVector3D &KxAABB::min()
{
    return m_min;
}

inline void KxAABB::setMin(const QVector3D &min)
{
    m_min = min;
}

inline void KxAABB::setMax(const QVector3D &max)
{
    m_max = max;
}

#endif // KXMATH_H
