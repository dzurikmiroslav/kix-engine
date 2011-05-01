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

#include "kxbulletutil.h"
#include "KxEngine/kxengine.h"
#include <QtCore/qvariant.h>

const KxPhysicsWorld* KxBulletUtil::physicsWorld()
{
    return kxEngine->physicsWorld();
}

QVector3D KxBulletUtil::convert(const btVector3 &vector)
{
    return QVector3D(vector.getX(), vector.getY(), vector.getZ());
}

btVector3 KxBulletUtil::convert(const QVector3D &vector)
{
    return btVector3(vector.x(), vector.y(), vector.z());
}

qreal KxBulletUtil::scale()
{
   return kxEngine->settings()["physics.scaling"].toReal();
}

qreal KxBulletUtil::oneOverScale()
{
    return 1 / kxEngine->settings()["physics.scaling"].toReal();
}

/*
QMatrix4x4 KxBulletUtil::convert(const btTransform &transform, qreal scale)
{
    qreal data[16];
    transform.getOpenGLMatrix(data);
    data[12] *= scale;
    data[13] *= scale;
    data[14] *= scale;
    const qreal *d = data;
    return QMatrix4x4(d).transposed();
}

btTransform KxBulletUtil::convert(const QMatrix4x4 &matrix, qreal scale)
{
    btTransform transform;
    transform.setFromOpenGLMatrix(matrix.data());
    transform.getOrigin() *= scale;
    return transform;
}
*/

QQuaternion KxBulletUtil::convert(const btQuaternion &value)
{
    return QQuaternion(value.getW(), value.getX(), value.getY(), value.getZ());
}

QVector3D KxBulletUtil::convertScaled(const btVector3 &value)
{
    return QVector3D(value.getX(), value.getY(), value.getZ()) * oneOverScale();
}

btVector3 KxBulletUtil::convertScaled(const QVector3D &value)
{
    return btVector3(value.x(), value.y(), value.z()) * scale();
}

btQuaternion KxBulletUtil::convert(const QQuaternion &value)
{
    return btQuaternion(value.x(), value.y(), value.z(), value.scalar());
}
