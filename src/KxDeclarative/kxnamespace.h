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

#ifndef KXNAMESPACE_H
#define KXNAMESPACE_H

#include "KxEngine/kxglobal.h"
#include <QtCore/qobject.h>
#include <QtGui/qvector2d.h>
#include <QtGui/qvector3d.h>
#include <QtGui/qquaternion.h>
#include <QtGui/qcolor.h>
#include <QtCore/qurl.h>
#include "KxPhysics/kxphysicsworld.h"
#include "KxScene/kxscene.h"
#include "KxEntity/kxentity.h"
#include "KxEngine/kxengine.h"


class KxNamespace : public QObject
{
    Q_OBJECT
    Q_ENUMS(Axis)   //FIXME
    Q_PROPERTY(QUrl dataPath READ dataPath FINAL)
    Q_PROPERTY(KxEngine *engine READ engine CONSTANT FINAL)

public:
    enum Axis {
        X = 0,
        Y = 1,
        Z = 2
    };
    explicit KxNamespace(QObject *parent = 0);
    KxEngine *engine();
    QUrl dataPath() const;
    Q_INVOKABLE QString readFile(const QString &fileName) const;
    Q_INVOKABLE KxMaterial *loadMaterial(const QString &fileName, QObject *parent) const;
    Q_INVOKABLE inline QVector4D vector4d(qreal x, qreal y, qreal z, qreal w) const;
    Q_INVOKABLE inline QVector4D vector4d(const QVector3D &v, qreal w) const;
    Q_INVOKABLE inline QVector3D vector3d(qreal x, qreal y, qreal z) const;
    Q_INVOKABLE inline QVector2D vector2d(qreal x, qreal y) const;
    Q_INVOKABLE inline QQuaternion quaternion(qreal scalar, qreal x, qreal y, qreal z) const;
    Q_INVOKABLE inline QQuaternion quaternionFromAxisAndAngle(qreal x, qreal y, qreal z, qreal angle) const;
    Q_INVOKABLE inline QVector3D vector3dAdd(const QVector3D& a, const QVector3D& b) const;
    Q_INVOKABLE inline QVector3D vector3dSub(const QVector3D& a, const QVector3D& b) const;
    Q_INVOKABLE inline QVector3D vector3dScaled(const QVector3D& vec, qreal scale) const;
    Q_INVOKABLE inline QVector3D vector3dNormalized(const QVector3D& vec) const;
    Q_INVOKABLE QVector3D directionFromAE(qreal azimut, qreal elevation) const;
    //shapes
    Q_INVOKABLE inline KxBoxShape *boxShape(const QVector3D& halfExtends, QObject *parent) const;
    Q_INVOKABLE inline KxCapsuleShape *capsuleShape(qreal radius, qreal height, int upAxis, QObject *parent) const;
    Q_INVOKABLE inline KxConeShape* coneShape(qreal radius, qreal height, int upAxis, QObject *parent) const;
    Q_INVOKABLE inline KxCylinderShape* cylinderShape(const QVector3D& halfExtends, int upAxis, QObject *parent) const;
    Q_INVOKABLE inline KxSphereShape *sphereShape(qreal radius, QObject *parent) const;
    Q_INVOKABLE inline KxStaticPlaneShape *staticPlaneShape(const QVector3D& planeNormal, qreal planeConstant, QObject *parent) const;
    Q_INVOKABLE inline KxTriangleMeshShape *triangleMeshShape(QObject *geometryData, QObject *parent) const;
    Q_INVOKABLE inline KxTriangleMeshShape *loadTriangleMeshShape(const QString fileName, QObject *parent) const;
    Q_INVOKABLE inline KxConvexHullShape *convexHullShape(QObject *geometryData, QObject *parent) const;
    Q_INVOKABLE inline KxConvexHullShape *loadConvexHullShape(const QString fileName, QObject *parent) const;

    /* Deprecated !!! */
    //col obj
    Q_INVOKABLE inline KxRigidBody *rigidBody(KxCollisionShape *shape, qreal mass, QObject *parent) const;
    Q_INVOKABLE inline KxCharacterController *characterController(KxConvexShape *shape, int upAxis, QObject *parent) const;
    Q_INVOKABLE inline KxRaycastVehicle *raycastVehicle(KxCollisionShape *collisionShape, qreal mass, QObject *parent) const;
    //constraints
    Q_INVOKABLE inline KxGeneric6DofConstraint *gen6DofConstraint(QObject *rbA, QObject *rbB,
                                                                  const QVector3D &posInA, const QQuaternion& rotInA,
                                                                  const QVector3D &posInB, const QQuaternion& rotInB,
                                                                  QObject *parent = 0) const;
    Q_INVOKABLE inline KxGeneric6DofSpringConstraint *gen6DofSpringConstraint(QObject *rbA, QObject *rbB,
                                                                              const QVector3D &posInA, const QQuaternion& rotInA,
                                                                              const QVector3D &posInB, const QQuaternion& rotInB,
                                                                              QObject *parent = 0) const;

};

QML_DECLARE_TYPE(KxNamespace);


inline KxGeneric6DofConstraint *KxNamespace::gen6DofConstraint(QObject *rbA, QObject *rbB,
                                                               const QVector3D &posInA, const QQuaternion &rotInA,
                                                               const QVector3D &posInB, const QQuaternion &rotInB,
                                                               QObject *parent) const
{
    if((!qobject_cast<KxRigidBody*>(rbA)) || (!qobject_cast<KxRigidBody*>(rbB))) {
        qWarning() << "KxNamespace::generic6DofConstraint invalid rigidBody";
        return NULL;
    }
    return new KxGeneric6DofConstraint(qobject_cast<KxRigidBody*>(rbA), qobject_cast<KxRigidBody*>(rbB), posInA, rotInA, posInB, rotInB, parent);
}

inline KxGeneric6DofSpringConstraint *KxNamespace::gen6DofSpringConstraint(QObject *rbA,
                                                                           QObject *rbB,
                                                                           const QVector3D &posInA,
                                                                           const QQuaternion &rotInA,
                                                                           const QVector3D &posInB,
                                                                           const QQuaternion &rotInB,
                                                                           QObject *parent) const
{
    if((!qobject_cast<KxRigidBody*>(rbA)) || (!qobject_cast<KxRigidBody*>(rbB))) {
        qWarning() << "KxNamespace::generic6DofSpringConstraint invalid rigidBody";
        return NULL;
    }
    return new KxGeneric6DofSpringConstraint(qobject_cast<KxRigidBody*>(rbA), qobject_cast<KxRigidBody*>(rbB), posInA, rotInA, posInB, rotInB, parent);
}

inline KxBoxShape *KxNamespace::boxShape(const QVector3D &halfExtends, QObject *parent) const
{
    return new KxBoxShape(halfExtends, parent);
}

inline KxCapsuleShape *KxNamespace::capsuleShape(qreal radius, qreal height, int upAxis, QObject *parent) const
{
    return new KxCapsuleShape(radius, height, upAxis, parent);
}

inline KxConeShape *KxNamespace::coneShape(qreal radius, qreal height, int upAxis, QObject *parent) const
{
    return new KxConeShape(radius, height, upAxis, parent);
}

inline KxCylinderShape *KxNamespace::cylinderShape(const QVector3D& halfExtends, int upAxis, QObject *parent) const
{
    return new KxCylinderShape(halfExtends, upAxis, parent);
}

inline KxSphereShape *KxNamespace::sphereShape(qreal radius, QObject *parent) const
{
    return new KxSphereShape(radius, parent);
}

inline KxStaticPlaneShape *KxNamespace::staticPlaneShape(const QVector3D& planeNormal, qreal planeConstant, QObject *parent) const
{
    return new KxStaticPlaneShape(planeNormal, planeConstant, parent);
}

inline KxTriangleMeshShape *KxNamespace::triangleMeshShape(QObject *geometryData, QObject *parent) const
{
    if(!qobject_cast<KxGeometryData*>(geometryData)) {
        qWarning() << "KxNamespace::triangleMeshShape invalid geometry data";
        return NULL;
    }
    return new KxTriangleMeshShape(qobject_cast<KxGeometryData*>(geometryData), parent);
}

inline KxConvexHullShape *KxNamespace::convexHullShape(QObject *geometryData, QObject *parent) const
{
    if(!qobject_cast<KxGeometryData*>(geometryData)) {
        qWarning() << "KxNamespace::convexHullShape invalid geometry data";
        return NULL;
    }
    return new KxConvexHullShape(qobject_cast<KxGeometryData*>(geometryData), parent);
}

inline KxConvexHullShape *KxNamespace::loadConvexHullShape(const QString fileName, QObject *parent) const
{
    return new KxConvexHullShape(fileName, parent);
}

inline KxTriangleMeshShape *KxNamespace::loadTriangleMeshShape(const QString fileName, QObject *parent) const
{
    return new KxTriangleMeshShape(fileName, parent);
}

inline KxRigidBody *KxNamespace::rigidBody(KxCollisionShape *shape, qreal mass, QObject *parent) const
{
    return new KxRigidBody(shape, mass, parent);
}

inline KxCharacterController *KxNamespace::characterController(KxConvexShape *shape, int upAxis, QObject *parent) const
{
    return new KxCharacterController(shape, upAxis, parent);
}

inline KxRaycastVehicle *KxNamespace::raycastVehicle(KxCollisionShape *collisionShape, qreal mass, QObject *parent) const
{
    return new KxRaycastVehicle(collisionShape, mass, parent);
}

inline QVector4D KxNamespace::vector4d(qreal x, qreal y, qreal z, qreal w) const
{
    return QVector4D(x, y, z, w);
}

inline QVector4D KxNamespace::vector4d(const QVector3D& v, qreal w) const
{
    return QVector4D(v, w);
}

inline QVector3D KxNamespace::vector3d(qreal x, qreal y, qreal z) const
{
    return QVector3D(x, y, z);
}

inline QVector2D KxNamespace::vector2d(qreal x, qreal y) const
{
    return QVector2D(x, y);
}

inline QQuaternion KxNamespace::quaternion(qreal scalar, qreal x, qreal y, qreal z) const
{
    return QQuaternion(scalar, x, y, z);
}

inline QQuaternion KxNamespace::quaternionFromAxisAndAngle(qreal x, qreal y, qreal z, qreal angle) const
{
    return QQuaternion::fromAxisAndAngle(x, y, z, angle);
}

inline QVector3D KxNamespace::vector3dAdd(const QVector3D &a, const QVector3D &b) const
{
    return a + b;
}

inline QVector3D KxNamespace::vector3dSub(const QVector3D &a, const QVector3D &b) const
{
    return a - b;
}

inline QVector3D KxNamespace::vector3dScaled(const QVector3D &vec, qreal scale) const
{
    return vec * scale;
}

inline QVector3D KxNamespace::vector3dNormalized(const QVector3D &vec) const
{
    return vec.normalized();
}


#endif // KXNAMESPACE_H
