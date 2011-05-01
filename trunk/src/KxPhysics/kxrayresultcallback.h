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

#ifndef KXRAYRESULTCALLBACK_H
#define KXRAYRESULTCALLBACK_H

#include <QtGui/qvector3d.h>
#include <QtDeclarative/qdeclarative.h>
#include <btBulletCollisionCommon.h>

class KxCollisionObject;

class KxRayResultCallback : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVector3D from READ from WRITE setFrom FINAL)
    Q_PROPERTY(QVector3D direction READ direction WRITE setDirection FINAL)
    Q_PROPERTY(qreal maxFraction READ maxFraction WRITE setMaxFraction FINAL)
    Q_PROPERTY(short mask READ mask WRITE setMask FINAL)
    Q_PROPERTY(short group READ group WRITE setGroup FINAL)
    Q_PROPERTY(QVector3D hitPosition READ hitPosition FINAL)
    Q_PROPERTY(qreal hitFraction READ hitFraction FINAL)
    Q_PROPERTY(KxCollisionObject* collisionObject READ collisionObject FINAL)

public:
    explicit KxRayResultCallback(QObject *parent = 0);

    Q_INVOKABLE bool hasHit() const;

    KxCollisionObject* collisionObject() const;

    short group() const;
    void setGroup(short group);

    short mask() const;
    void setMask(short mask);

    qreal hitFraction() const;
    QVector3D hitPosition() const;

    QVector3D from() const;
    void setFrom(const QVector3D& value);

    QVector3D direction() const;
    void setDirection(const QVector3D& value);

    qreal maxFraction() const;
    void setMaxFraction(qreal value);

private:
    btCollisionWorld::ClosestRayResultCallback &prepare();

    QVector3D m_direction;
    qreal m_maxFraction;
    btCollisionWorld::ClosestRayResultCallback m_rayResultCallback;

    friend class KxPhysicsWorld;
};

QML_DECLARE_TYPE(KxRayResultCallback);

#endif // KXRAYRESULTCALLBACK_H
