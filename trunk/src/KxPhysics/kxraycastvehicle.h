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

#ifndef KXRAYCASTVEHICLE_H
#define KXRAYCASTVEHICLE_H

#include <BulletDynamics/Vehicle/btRaycastVehicle.h>
#include "kxrigidbody.h"
#include <QtDeclarative/qdeclarative.h>

class KxRaycastVehicle;

class KxWheelInfo : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qreal steering READ steering WRITE setSteering FINAL);
    Q_PROPERTY(qreal engineForce READ engineForce WRITE setEngineForce FINAL);
    Q_PROPERTY(qreal brake READ brake WRITE setBrake FINAL);

public:

    qreal steering() const
    {
        return m_vechile->getWheelInfo(m_wheelId).m_rotation;
    }

    qreal engineForce() const
    {
        return m_vechile->getWheelInfo(m_wheelId).m_engineForce;
    }

    qreal brake() const
    {
       return m_vechile->getWheelInfo(m_wheelId).m_brake;
    }

    void setSteering(qreal value)
    {
        m_vechile->setSteeringValue(value, m_wheelId);
    }

    void setEngineForce(qreal value)
    {
        m_vechile->applyEngineForce(value, m_wheelId);
    }

    void setBrake(qreal value)
    {
        m_vechile->setBrake(value, m_wheelId);
    }

signals:
    void transformChanged(const QVector3D &position, const QQuaternion &rotation);

private:
    explicit KxWheelInfo(int wheelIndex, KxRaycastVehicle *vehicle);
    void emitTransform();
    int m_wheelId;
    btRaycastVehicle *m_vechile;

    friend class KxRaycastVehicle;
};

QML_DECLARE_TYPE(KxWheelInfo);


class KxRaycastVehicle : public KxRigidBody ,private btActionInterface
{
    Q_OBJECT
    Q_PROPERTY(QDeclarativeListProperty<KxWheelInfo> wheels READ qmlWheels FINAL);

public:
    explicit KxRaycastVehicle(KxCollisionShape *shape, qreal mass, QObject *parent = 0);

    Q_INVOKABLE KxWheelInfo *addWheel(const QVector3D &connectionPointCS0,
                                      const QVector3D &wheelDirectionCS0,
                                      const QVector3D &wheelAxleCS,
                                      qreal suspensionRestLength,
                                      qreal wheelRadius,
                                      bool isFrontWheel);
    Q_INVOKABLE void setSteeringValue(qreal steering,int wheel);
    QDeclarativeListProperty<KxWheelInfo> qmlWheels();

signals:

public slots:

private:
    btRaycastVehicle::btVehicleTuning m_turing;
    btRaycastVehicle *m_vechile;
    QList<KxWheelInfo*> m_wheels;

    virtual void updateAction(btCollisionWorld* collisionWorld, btScalar deltaTimeStep);
    virtual void debugDraw(btIDebugDraw* debugDrawer);

    friend class KxPhysicsWorld;
    friend class KxWheelInfo;
};

Q_DECLARE_METATYPE(KxRaycastVehicle*);


#endif // KXRAYCASTVEHICLE_H
