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

#include "kxmath.h"

KxTransform::KxTransform() :
    m_rotation(),
    m_position()
{
}

KxTransform::KxTransform(const KxTransform &other)
{
    m_position = other.m_position;
    m_rotation = other.m_rotation;
}

KxTransform::KxTransform(const QVector3D &position, const QQuaternion &rotation)
{
    m_position = position;
    m_rotation = rotation;
}

KxAABB::KxAABB(const QVector<QVector3D> &vertices)
{
    m_max = vertices.first();
    m_min = vertices.first();
    foreach(QVector3D v, vertices) {
        if(v.x() < m_min.x())
            m_min.setX(v.x());
        if(v.y() < m_min.y())
            m_min.setY(v.y());
        if(v.z() < m_min.z())
            m_min.setZ(v.z());
        if(v.x() > m_max.x())
            m_max.setX(v.x());
        if(v.y() > m_max.y())
            m_max.setY(v.y());
        if(v.z() > m_max.z())
            m_max.setZ(v.z());
    }
}

KxAABB::KxAABB(const QVector3D& min, const QVector3D& max) :
        m_max(max),
        m_min(min)
{
}

const KxAABB& KxAABB::operator + (const KxAABB& other)
{
    //TODO
    return *this;
}

KxAABB& KxAABB::operator += (const KxAABB& other)
{
    //TODO
    return *this;
}
