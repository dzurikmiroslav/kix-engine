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

#ifndef KXCOLLISIONOBJECT_H
#define KXCOLLISIONOBJECT_H

#include <QtCore/qobject.h>
#include <QtGui/qvector3d.h>
#include <QtGui/qquaternion.h>
#include <QtCore/qmetatype.h>
#include <btBulletCollisionCommon.h>

class KxCollisionShape;

class KxCollisionObject : public QObject
{
    Q_OBJECT
    Q_PROPERTY(short mask READ mask FINAL)
    Q_PROPERTY(short group READ group FINAL)
    Q_PROPERTY(QVector3D position READ position WRITE setPosition FINAL)
    Q_PROPERTY(QQuaternion rotation READ rotation WRITE setRotation FINAL)
    Q_PROPERTY(QObject *parent READ parent WRITE setParent FINAL)

public:
    virtual QVector3D position() const = 0;
    Q_SLOT virtual void setPosition(const QVector3D& value) = 0;

    virtual QQuaternion rotation() const = 0;
    Q_SLOT virtual void setRotation(const QQuaternion& value) = 0;

    Q_INVOKABLE QVector3D converToLocal(const QVector3D &position) const;

    virtual KxCollisionShape *collisionShape() const = 0;

    virtual short mask() const = 0;
    virtual short group() const = 0;

    Q_INVOKABLE virtual bool isRigidBody() const;
    Q_INVOKABLE virtual bool isCharacterController() const;

signals:
    void beforeDestroy(KxCollisionObject *object); //musi emitovat navyzsi potomok
    void transformChanged(const QVector3D& position, const QQuaternion& rotation);
    void positionChanged(const QVector3D& position);
    void rotationChanged(const QQuaternion& rotation);

protected:
    explicit KxCollisionObject(QObject *parent = 0);

    friend class KxPhysicsWorld;
};

Q_DECLARE_METATYPE(KxCollisionObject*);

#endif // KXCOLLISIONOBJECT_H
