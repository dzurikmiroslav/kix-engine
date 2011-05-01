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

#ifndef KXCHARACTERCONTROLLERCON_H
#define KXCHARACTERCONTROLLERCON_H

#include <QtGui/qvector3d.h>
#include <QtGui/qquaternion.h>
#include "kxconvexshape.h"

class KxCharacterController;

class KxCharacterControllerCon : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int upAxis READ upAxis WRITE setUpAxis NOTIFY propertyChanged FINAL)
    Q_PROPERTY(KxConvexShape *collisionShape READ collisionShape WRITE setCollisionShape NOTIFY propertyChanged FINAL)
    Q_PROPERTY(short mask READ mask WRITE setMask NOTIFY propertyChanged FINAL)
    Q_PROPERTY(short group READ group WRITE setGroup NOTIFY propertyChanged FINAL)
    Q_PROPERTY(qreal fallSpeed READ fallSpeed WRITE setFallSpeed NOTIFY propertyChanged FINAL)
    Q_PROPERTY(qreal jumpSpeed READ jumpSpeed WRITE setJumpSpeed NOTIFY propertyChanged FINAL)
    Q_PROPERTY(qreal maxJumpHeight READ maxJumpHeight WRITE setMaxJumpHeight NOTIFY propertyChanged FINAL)
    Q_PROPERTY(qreal maxSlope READ maxSlope WRITE setMaxSlope NOTIFY propertyChanged FINAL)
    Q_PROPERTY(QVector3D position READ position WRITE setPosition NOTIFY propertyChanged FINAL)
    Q_PROPERTY(QQuaternion rotation READ rotation WRITE setRotation NOTIFY propertyChanged FINAL)

public:
    explicit KxCharacterControllerCon(QObject *parent = 0);

    qreal fallSpeed() const;
    void setFallSpeed(qreal value);

    qreal jumpSpeed() const;
    void setJumpSpeed(qreal value);

    qreal maxJumpHeight() const;
    void setMaxJumpHeight(qreal value);

    qreal maxSlope() const;
    void setMaxSlope(qreal value);

    KxConvexShape *collisionShape() const;
    void setCollisionShape(KxConvexShape *value);

    int upAxis() const;
    void setUpAxis(int value);

    short mask() const;
    void setMask(short value);

    short group() const;
    void setGroup(short value);

    const QVector3D& position() const;
    void setPosition(const QVector3D& value);

    const QQuaternion& rotation() const;
    void setRotation(const QQuaternion& value);

    Q_INVOKABLE QVariant create(const QVariant &parent) const;
    KxCharacterController *create(QObject *parent = 0) const;

signals:
    void propertyChanged();

private:
    int m_upAxis;
    short m_mask;
    short m_group;
    qreal m_fallSpeed;
    qreal m_maxSlope;
    qreal m_maxJumpHeight;
    qreal m_jumpSpeed;
    QVector3D m_position;
    QQuaternion m_rotation;
    KxConvexShape *m_collisionShape;

};

QML_DECLARE_TYPE(KxCharacterControllerCon);


#endif // KXCHARACTERCONTROLLERCON_H
