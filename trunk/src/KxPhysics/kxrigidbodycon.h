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

#ifndef KXRIGIDBODYCON_H
#define KXRIGIDBODYCON_H

#include <QtDeclarative/qdeclarative.h>
#include <QtGui/qvector3d.h>
#include <QtGui/qquaternion.h>
#include "kxcollisionshape.h"

class KxRigidBody;

class KxRigidBodyCon : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QObject *parent READ parent WRITE setParent FINAL);
    Q_PROPERTY(qreal mass READ mass WRITE setMass NOTIFY massChanged FINAL);
    Q_PROPERTY(KxCollisionShape *collisionShape READ collisionShape WRITE setCollisionShape NOTIFY collisionShapeChanged FINAL);
    Q_PROPERTY(short mask READ mask WRITE setMask NOTIFY maskChanged FINAL);
    Q_PROPERTY(short group READ group WRITE setGroup NOTIFY groupChanged FINAL);
    Q_PROPERTY(QVector3D position READ position WRITE setPosition NOTIFY positionChanged FINAL);
    Q_PROPERTY(QQuaternion rotation READ rotation WRITE setRotation NOTIFY rotationChanged FINAL);
    Q_PROPERTY(qreal friction READ friction WRITE setFriction FINAL);

public:
    explicit KxRigidBodyCon(QObject *parent = 0);
    inline void setCollisionShape(KxCollisionShape *value);
    inline void setMass(qreal value);
    inline void setFriction(qreal value);
    inline void setMask(short value);
    inline void setGroup(short value);
    inline void setPosition(const QVector3D& value);
    inline void setRotation(const QQuaternion& value);
    inline KxCollisionShape *collisionShape() const;
    inline qreal mass() const;
    inline qreal friction() const;
    inline short mask() const;
    inline short group() const;
    inline const QVector3D& position() const;
    inline const QQuaternion& rotation() const;
    KxRigidBody *create(QObject *parent = 0) const;
    Q_INVOKABLE QVariant create(const QVariant &parent) const;

signals:
    //qml
    void massChanged();
    void maskChanged();
    void groupChanged();
    void collisionShapeChanged();
    void positionChanged();
    void rotationChanged();

protected:
    KxCollisionShape *m_collisionShape;
    qreal m_mass;
    qreal m_friction;
    short m_group;
    short m_mask;
    QVector3D m_position;
    QQuaternion m_rotation;

};

QML_DECLARE_TYPE(KxRigidBodyCon);


inline void KxRigidBodyCon::setPosition(const QVector3D &value)
{
    m_position = value;
}

inline void KxRigidBodyCon::setRotation(const QQuaternion &value)
{
    m_rotation = value;
}

inline void KxRigidBodyCon::setCollisionShape(KxCollisionShape *value)
{
    m_collisionShape = value;
}

inline void KxRigidBodyCon::setMass(qreal value)
{
    m_mass = value;
}

inline void KxRigidBodyCon::setFriction(qreal value)
{
    m_friction = value;
}

inline void KxRigidBodyCon::setMask(short value)
{
    m_mask = value;
}

inline void KxRigidBodyCon::setGroup(short value)
{
    m_group = value;
}

inline KxCollisionShape *KxRigidBodyCon::collisionShape() const
{
    return m_collisionShape;
}

inline qreal KxRigidBodyCon::mass() const
{
    return m_mass;
}

inline qreal KxRigidBodyCon::friction() const
{
    return m_friction;
}

inline short KxRigidBodyCon::mask() const
{
    return m_mask;
}

inline short KxRigidBodyCon::group() const
{
    return m_group;
}

inline const QVector3D& KxRigidBodyCon::position() const
{
    return m_position;
}

inline const QQuaternion& KxRigidBodyCon::rotation() const
{
    return m_rotation;
}

#endif // KXRIGIDBODYCON_H
