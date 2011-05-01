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
#ifndef KXBULLETUTIL_H
#define KXBULLETUTIL_H

#include <btBulletDynamicsCommon.h>
#include <QtGui/qvector3d.h>
#include <QtGui/qquaternion.h>
#include <QtGui/qmatrix4x4.h>

class KxPhysicsWorld;

namespace KxBulletUtil
{
    qreal scale();
    qreal oneOverScale();
    const KxPhysicsWorld *physicsWorld();

    //bullet physics --> qt
    QQuaternion convert(const btQuaternion& value);
    QVector3D convert(const btVector3& vector);
    QVector3D convertScaled(const btVector3& value);

    //qt --> bullet physics
    btQuaternion convert(const QQuaternion& value);
    btVector3 convert(const QVector3D& vector);
    btVector3 convertScaled(const QVector3D& value);    
}


#endif // KXBULLETUTIL_H
