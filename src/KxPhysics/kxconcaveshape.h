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

#ifndef KXCONCAVESHAPE_H
#define KXCONCAVESHAPE_H

#include "kxcollisionshape.h"
#include <btBulletCollisionCommon.h>
#include <QtGui/qvector3d.h>
#include <QtCore/qvector.h>

class KxGeometryData;

class KxConcaveShape : public KxCollisionShape
{
    Q_OBJECT

protected:
    explicit KxConcaveShape(QObject *parent = 0);

    virtual btConcaveShape* internalBtConcaveShape() const = 0;

};

QML_DECLARE_TYPE(KxConcaveShape);


class KxStaticPlaneShape : public KxConcaveShape
{
    Q_OBJECT
    Q_PROPERTY(QVector3D planeNormal READ planeNormal FINAL)
    Q_PROPERTY(qreal planeConstant READ planeConstant FINAL)

public:
    explicit KxStaticPlaneShape(const QVector3D& planeNormal, qreal planeConstant, QObject *parent = 0);
    ~KxStaticPlaneShape();

    QVector3D planeNormal() const;

    qreal planeConstant() const;

private:
    virtual btCollisionShape* internalBtShape() const;
    virtual btConcaveShape* internalBtConcaveShape() const;

    btStaticPlaneShape *m_shape;

};

QML_DECLARE_TYPE(KxStaticPlaneShape);


class KxTriangleMeshShape : public KxConcaveShape
{
    Q_OBJECT

public:
    explicit KxTriangleMeshShape(const QString& fileName, QObject *parent = 0);
    explicit KxTriangleMeshShape(KxGeometryData *geometry, QObject *parent = 0);

private:
    void loadObjFile(const QString& fileName);

    virtual btCollisionShape* internalBtShape() const;
    virtual btConcaveShape* internalBtConcaveShape() const;

    btBvhTriangleMeshShape *m_shape;
    QVector<QVector3D> m_vertices;
    QVector<int> m_indices;

};

QML_DECLARE_TYPE(KxTriangleMeshShape);



#endif // KXCONCAVESHAPE_H
