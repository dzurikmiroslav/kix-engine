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

#ifndef KXPHYSICSWORLD_H
#define KXPHYSICSWORLD_H

#include <QtCore/qmutex.h>
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
#include "KxEngine/kxglobal.h"
#include "kxbulletdebugdrawer.h"
#include "kxconcaveshape.h"
#include "kxconvexshape.h"
#include "kxrigidbody.h"
#include "kxrigidbodycon.h"
#include "kxcharactercontroller.h"
#include "kxcharactercontrollercon.h"
#include "kxraycastvehicle.h"
#include "kxraycastvehiclecon.h"
#include "kxrayresultcallback.h"
#include "kxgeneric6dofconstraint.h"
#include "kxgeneric6dofconstraintcon.h"
#include "kxgeneric6dofspringconstraint.h"
#include "kxgeneric6dofspringconstraintcon.h"

class btGhostPairCallback;

class KxPhysicsWorld : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVector3D gravity READ gravity WRITE setGravity FINAL)
    Q_PROPERTY(bool sleep READ isSleep WRITE setSleep FINAL)

public: 
    explicit KxPhysicsWorld(QObject *parent = 0);
    ~KxPhysicsWorld();

    QVector3D gravity() const;
    void setGravity(const QVector3D& value);

    inline bool isSleep() const;
    void setSleep(bool value);

    void rayTest(KxRayResultCallback *rayCallback);
    Q_INVOKABLE void rayTest(const QVariant &rayCallback);

    void addCollisionObject(KxCollisionObject *object, short group = 1, short mask = 1);
    Q_INVOKABLE void addCollisionObject(const QVariant &object, const QVariant &group, const QVariant &mask);
    Q_SLOT void removeCollisionObject(KxCollisionObject *object);

    void addConstraint(KxTypedConstraint *constraint, bool disCollBetween = false);
    Q_INVOKABLE void addConstraint(const QVariant &constraint, const QVariant &disCollBetween);
    Q_SLOT void removeConstraint(KxTypedConstraint *constraint);

private:
    void update(int deltaTime);
    void debugDraw();
    btVehicleRaycaster *vechicleRaycaster() const;

    QMutex m_mutex;
    btCollisionConfiguration *m_collisionConfiguration;
    btDiscreteDynamicsWorld *m_dynamicsWorld;
    btBroadphaseInterface *m_broadphase;
    btSequentialImpulseConstraintSolver *m_solver;
    btCollisionDispatcher *m_dispatcher;
    btVehicleRaycaster *m_vehicleRaycaster;
    KxBulletDebugDrawer *m_drawer;
    bool m_sleep : 1;

    friend class KxRaycastVehicle;
    friend class KxEngine;
    friend class KxGLDrawer;
};

QML_DECLARE_TYPE(KxPhysicsWorld);


inline bool KxPhysicsWorld::isSleep() const
{
    return m_sleep;
}

#endif // KXPHYSICSWORLD_H
