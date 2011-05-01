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

#ifndef KXCONVEXSHAPE_H
#define KXCONVEXSHAPE_H

#include "kxcollisionshape.h"
#include <btBulletCollisionCommon.h>
#include <QtGui/qvector3d.h>
#include <QtCore/qvector.h>
#include "KxEngine/kxglobal.h"
#include "KxScene/kxgeometrydata.h"

class KxConvexShape : public KxCollisionShape
{
    Q_OBJECT    

protected:
    explicit KxConvexShape(QObject *parent = 0);

    virtual btConvexShape* internalConvexShape() const = 0;

    friend class KxCharacterController;
};

Q_DECLARE_METATYPE(KxConvexShape*);


class KxBoxShape : public KxConvexShape
{
    Q_OBJECT
    Q_PROPERTY(QVector3D halfExtentsWithMargin READ halfExtentsWithMargin FINAL)
    Q_PROPERTY(QVector3D halfExtentsWithoutMargin READ halfExtentsWithoutMargin FINAL)

public:
    explicit KxBoxShape(const QVector3D& halfExteds, QObject *parent = 0);
    ~KxBoxShape();

    QVector3D halfExtentsWithMargin() const;
    QVector3D halfExtentsWithoutMargin() const;

private:
    virtual btCollisionShape* internalBtShape() const;
    virtual btConvexShape* internalConvexShape() const;

    btBoxShape *m_shape;

};

QML_DECLARE_TYPE(KxBoxShape);


class KxSphereShape : public KxConvexShape
{
    Q_OBJECT
    Q_PROPERTY(qreal radius READ radius FINAL)

public:
    explicit KxSphereShape(qreal radius, QObject *parent = 0);
    ~KxSphereShape();

    qreal radius() const;

private:
    virtual btCollisionShape* internalBtShape() const;
    virtual btConvexShape* internalConvexShape() const;

    btSphereShape *m_shape;

};

QML_DECLARE_TYPE(KxSphereShape);


class KxCapsuleShape : public KxConvexShape
{
    Q_OBJECT
    Q_PROPERTY(qreal radius READ radius FINAL)
    Q_PROPERTY(qreal halfHeight READ halfHeight FINAL)

public:
    explicit KxCapsuleShape(qreal radius, qreal height, int axis = Kx::Y, QObject *parent = 0);
    ~KxCapsuleShape();

    int upAxis() const;

    qreal radius() const;

    qreal halfHeight() const;

private:
    virtual btCollisionShape* internalBtShape() const;
    virtual btConvexShape* internalConvexShape() const;

    btCapsuleShape *m_shape;

};

QML_DECLARE_TYPE(KxCapsuleShape);


class KxCylinderShape : public KxConvexShape
{
    Q_OBJECT
    Q_PROPERTY(QVector3D halfExtentsWithMargin READ halfExtentsWithMargin FINAL)
    Q_PROPERTY(QVector3D halfExtentsWithoutMargin READ halfExtentsWithoutMargin FINAL)

public:
    explicit KxCylinderShape(const QVector3D& halfExtends, int upAxis = Kx::Y, QObject *parent = 0);
    ~KxCylinderShape();

    int upAxis() const;

    QVector3D halfExtentsWithMargin() const;
    QVector3D halfExtentsWithoutMargin() const;

private:
    virtual btCollisionShape* internalBtShape() const;
    virtual btConvexShape* internalConvexShape() const;

    btCylinderShape *m_shape;

};

QML_DECLARE_TYPE(KxCylinderShape);


class KxConeShape : public KxConvexShape
{
    Q_OBJECT
    Q_PROPERTY(qreal radius READ radius FINAL)
    Q_PROPERTY(qreal height READ height FINAL)

public:
    explicit KxConeShape(qreal radius, qreal height, int upAxis = Kx::Y, QObject *parent = 0);
    ~KxConeShape();

    int upAxis() const;

    qreal radius() const;
    qreal height() const;

private:
    virtual btCollisionShape* internalBtShape() const;
    virtual btConvexShape* internalConvexShape() const;

    btConeShape *m_shape;

};

QML_DECLARE_TYPE(KxConeShape);


class KxConvexHullShape : public KxConvexShape
{
    Q_OBJECT

public:
    explicit KxConvexHullShape(const QString& fileName, QObject *parent = 0);
    explicit KxConvexHullShape(KxGeometryData *geometry, QObject *parent = 0);
    ~KxConvexHullShape();

private:
    void loadObjFile(const QString& fileName);

    virtual btCollisionShape* internalBtShape() const;
    virtual btConvexShape* internalConvexShape() const;

    btConvexHullShape *m_shape;

};

QML_DECLARE_TYPE(KxConvexHullShape);


#endif // KXCONVEXSHAPE_H
