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

#ifndef KXCHARACTERCONTROLLER_H
#define KXCHARACTERCONTROLLER_H

#include "kxcollisionobject.h"
#include "KxEngine/kxglobal.h"
#include <QtDeclarative/qdeclarative.h>
#include <btBulletDynamicsCommon.h>
#include <BulletCollision/CollisionDispatch/btGhostObject.h>
#include <BulletDynamics/Character/btKinematicCharacterController.h>
#include "kxbulletutil.h"

class KxConvexShape;

class KxCharacterController : public KxCollisionObject, private btActionInterface
{
    Q_OBJECT
    Q_PROPERTY(QVector3D walkDirection READ QVector3D WRITE setWalkDirection FINAL)
    Q_PROPERTY(qreal fallSpeed READ fallSpeed WRITE setFallSpeed FINAL)
    Q_PROPERTY(qreal jumpSpeed READ jumpSpeed WRITE setJumpSpeed FINAL)
    Q_PROPERTY(qreal maxJumpHeight READ maxJumpHeight WRITE setMaxJumpHeight FINAL)
    Q_PROPERTY(qreal maxSlope READ maxSlope WRITE setMaxSlope FINAL)
    Q_PROPERTY(QVector3D velocity READ QVector3D WRITE setVelocity FINAL)

public:
    explicit KxCharacterController(KxConvexShape *shape, int upAxis = Kx::Y, QObject *parent = 0);
    ~KxCharacterController();

    qreal fallSpeed() const;
    void setFallSpeed(qreal value);

    qreal jumpSpeed() const;
    void setJumpSpeed(qreal value);

    qreal maxJumpHeight() const;
    void setMaxJumpHeight(qreal vale);

    qreal maxSlope() const;
    void setMaxSlope(qreal value);

    virtual KxCollisionShape *collisionShape() const;

    virtual short mask() const;
    virtual short group() const;

    virtual QVector3D position() const;
    virtual void setPosition(const QVector3D& value);

    virtual QQuaternion rotation() const;
    virtual void setRotation(const QQuaternion& value);

    Q_INVOKABLE void jump();

    virtual bool isCharacterController() const;

public slots:
    void setWalkDirection(const QVector3D &value);
    void setVelocity(const QVector3D &value);

private:
    void setup(KxConvexShape *shape, int upAxis);

    virtual void updateAction(btCollisionWorld* collisionWorld, btScalar deltaTimeStep);
    virtual void debugDraw(btIDebugDraw* debugDrawer);

    QVector3D m_walkDirection;
    bool m_useWalkDirection;
    btKinematicCharacterController *m_character;
    btPairCachingGhostObject *m_ghostObject;

    friend class KxPhysicsWorld;
};

QML_DECLARE_TYPE(KxCharacterController);

#endif // KXCHARACTERCONTROLLER_H
