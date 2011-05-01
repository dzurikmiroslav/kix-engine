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

#ifndef KXRIGIDBODY_H
#define KXRIGIDBODY_H

#include "kxcollisionobject.h"
#include <btBulletDynamicsCommon.h>

class KxPhysicsWorld;
class KxCollisionShape;

class KxRigidBody : public KxCollisionObject, private btMotionState
{
    Q_OBJECT
    Q_PROPERTY(QVector3D linearVelocity READ linearVelocity WRITE setLinearVelocity FINAL)
    Q_PROPERTY(QVector3D angularVelocity READ angularVelocity WRITE setAngularVelocity FINAL)
    Q_PROPERTY(QVector3D gravity READ gravity WRITE setGravity FINAL)
    Q_PROPERTY(QVector3D linearFactor READ linearFactor WRITE setLinearFactor FINAL)
    Q_PROPERTY(QVector3D angularFactor READ angularFactor WRITE setAngularFactor FINAL)
    Q_PROPERTY(QVector3D totalForce READ totalForce FINAL)
    Q_PROPERTY(QVector3D totalTorque READ totalTorque FINAL)
    Q_PROPERTY(qreal angularDamping READ angularDamping WRITE setAngularDamping FINAL)
    Q_PROPERTY(qreal linearDamping READ linearDamping WRITE setLinearDamping FINAL)
    Q_PROPERTY(qreal friction READ friction WRITE setFriction FINAL)

public:
    explicit KxRigidBody(KxCollisionShape *shape, qreal mass, QObject *parent = 0);
    virtual ~KxRigidBody();

    virtual KxCollisionShape *collisionShape() const;

    virtual short mask() const;
    virtual short group() const;

    virtual QVector3D position() const;
    virtual void setPosition(const QVector3D& value);

    virtual QQuaternion rotation() const;
    virtual void setRotation(const QQuaternion& value);

    QVector3D linearVelocity() const;
    void setLinearVelocity(const QVector3D& value);

    QVector3D angularVelocity() const;
    void setAngularVelocity(const QVector3D& value);

    QVector3D linearFactor() const;
    void setLinearFactor(const QVector3D& value);

    QVector3D angularFactor() const;
    void setAngularFactor(const QVector3D& value);

    QVector3D gravity() const;
    void setGravity(const QVector3D& value);

    qreal linearDamping() const;
    void setLinearDamping(qreal value);

    qreal angularDamping() const;
    void setAngularDamping(qreal value);

    inline qreal friction() const;
    inline void setFriction(qreal value);

    QVector3D totalForce() const;
    Q_INVOKABLE void applyCentralForce(const QVector3D& force);
    Q_INVOKABLE void applyForce(const QVector3D &force, const QVector3D &relPos);

    QVector3D totalTorque() const;
    Q_INVOKABLE void applyTorque(const QVector3D &torque);

    Q_INVOKABLE void applyImpulse(const QVector3D &impulse, const QVector3D &relPos);
    Q_INVOKABLE void applyCentralImpulse(const QVector3D &impulse);
    Q_INVOKABLE void applyTorqueImpulse(const QVector3D &torque);

    Q_INVOKABLE void clearForces();

    virtual bool isRigidBody() const;
    Q_INVOKABLE bool isDynamic() const;

protected:
    void setup(KxCollisionShape *shape, qreal mass);

    virtual void getWorldTransform(btTransform& centerOfMassWorldTrans) const;
    virtual void setWorldTransform(const btTransform& centerOfMassWorldTrans);

    btRigidBody *m_body;
    btTransform m_worldTransform;

    friend class KxPhysicsWorld;
    friend class KxGeneric6DofConstraint;
    friend class KxGeneric6DofSpringConstraint;
};

Q_DECLARE_METATYPE(KxRigidBody*);


inline qreal KxRigidBody::friction() const
{
    return m_body->getFriction();
}

inline void KxRigidBody::setFriction(qreal value)
{
    m_body->setFriction(value);
}

#endif // KXRIGIDBODY_H
