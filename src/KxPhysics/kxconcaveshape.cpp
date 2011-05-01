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

#include "kxconcaveshape.h"
#include "kxbulletutil.h"
#include "KxScene/kxgeometrydata.h"
#include "KxScene/kxindexedgeometrydata.h"
#include <QtCore/qfile.h>
#include <QtXml/qdom.h>
#include <QtCore/qstringlist.h>

KxConcaveShape::KxConcaveShape(QObject *parent) :
        KxCollisionShape(parent)
{
}

/* static plane */

KxStaticPlaneShape::KxStaticPlaneShape(const QVector3D &planeNormal, qreal planeConstant, QObject *parent) :
        KxConcaveShape(parent)
{
    m_shape = new btStaticPlaneShape(KxBulletUtil::convert(planeNormal), planeConstant * KxBulletUtil::scale());
    m_shape->setUserPointer(this);
}

KxStaticPlaneShape::~KxStaticPlaneShape()
{
    delete m_shape;
}

btCollisionShape* KxStaticPlaneShape::internalBtShape() const
{
    return m_shape;
}

btConcaveShape* KxStaticPlaneShape::internalBtConcaveShape() const
{
    return m_shape;
}

QVector3D KxStaticPlaneShape::planeNormal() const
{
    return KxBulletUtil::convert(m_shape->getPlaneNormal());
}

qreal KxStaticPlaneShape::planeConstant() const
{
    return m_shape->getPlaneConstant() * KxBulletUtil::oneOverScale();
}

/* triangle mesh */

KxTriangleMeshShape::KxTriangleMeshShape(const QString &fileName, QObject *parent) :
        KxConcaveShape(parent)
{
    m_shape = NULL;
    qDebug() << "KxTriangleMeshShape::KxTriangleMeshShape" << fileName;
    if (fileName.endsWith(".obj", Qt::CaseInsensitive))
         loadObjFile(fileName);
    else
        qWarning() << "KxTriangleMeshShape::KxTriangleMeshShape uknow format addictive";
}

KxTriangleMeshShape::KxTriangleMeshShape(KxGeometryData *geometry, QObject *parent) :
        KxConcaveShape(parent)
{
    m_shape = NULL;
    KxIndexedGeometryData *data = qobject_cast<KxIndexedGeometryData*>(geometry);
    btStridingMeshInterface *trimesh;
    if (data) {
        btIndexedMesh mesh;
        mesh.m_numTriangles = data->m_indices.count() / 3;
        mesh.m_numVertices = data->m_vertices.count();
        mesh.m_triangleIndexBase = (const unsigned char*) data->m_indices.data();
        mesh.m_vertexBase = (const unsigned char*) data->m_vertices.data();
        mesh.m_triangleIndexStride = sizeof(uint) * 3;
        mesh.m_indexType = PHY_INTEGER; //TODO nem dobre asi :-/
        mesh.m_vertexStride = sizeof(QVector3D);
        mesh.m_vertexType = PHY_FLOAT;
        trimesh = new btTriangleIndexVertexArray;
        ((btTriangleIndexVertexArray*)trimesh)->addIndexedMesh(mesh, PHY_INTEGER);
    } else {
        qWarning() << "KxTriangleMeshShape::KxTriangleMeshShape geometry data is not indexed, maybe very slow";
        trimesh = new btTriangleMesh();
        const QVector3D *vertices = geometry->vertices().constData();
        int count = geometry->vertices().count();
        for (int i = 0; i < count; i += 3)
            ((btTriangleMesh*)trimesh)->addTriangle(KxBulletUtil::convert(vertices[i + 0]),
                                                    KxBulletUtil::convert(vertices[i + 1]),
                                                    KxBulletUtil::convert(vertices[i + 2]));
    }
    m_shape = new btBvhTriangleMeshShape(trimesh, true, true);
    m_shape->setLocalScaling(btVector3(KxBulletUtil::scale(), KxBulletUtil::scale(), KxBulletUtil::scale()));
}

btCollisionShape* KxTriangleMeshShape::internalBtShape() const
{
    return m_shape;
}

btConcaveShape* KxTriangleMeshShape::internalBtConcaveShape() const
{
    return m_shape;
}

void KxTriangleMeshShape::loadObjFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "KxTriangleMeshShape::loadObjFile cant read file" << fileName;
        return;
    }
    QTextStream stream(&file);
    QRegExp vReg("v\\s+(\\S+)\\s+(\\S+)\\s+(\\S+).*");
    QRegExp fReg1("f\\s+(\\d+)\\s+(\\d+)\\s+(\\d+).*");
    QRegExp fReg2("f\\s+(\\d+)//\\d+\\s+(\\d+)//\\d+\\s+(\\d+)//\\d+.*");
    QRegExp fReg3("f\\s+(\\d+)/\\d+/\\d+\\s+(\\d+)/\\d+/\\d+\\s+(\\d+)/\\d+/\\d+.*");
    QString line;
    do {
        line = stream.readLine();
        if (vReg.indexIn(line) > -1)
            m_vertices << QVector3D(vReg.cap(1).toFloat(), vReg.cap(2).toFloat(), vReg.cap(3).toFloat());
        else if (fReg3.indexIn(line) > -1) {
            m_indices << fReg3.cap(1).toInt() - 1;
            m_indices << fReg3.cap(2).toInt() - 1;
            m_indices << fReg3.cap(3).toInt() - 1;
        } else if (fReg2.indexIn(line) > -1) {
            //bez textur
            m_indices << fReg2.cap(1).toInt() - 1;
            m_indices << fReg2.cap(2).toInt() - 1;
            m_indices << fReg2.cap(3).toInt() - 1;
        } else if (fReg1.indexIn(line) > -1) {
            m_indices << fReg1.cap(1).toInt() - 1;
            m_indices << fReg1.cap(2).toInt() - 1;
            m_indices << fReg1.cap(3).toInt() - 1;
        }
    } while (!line.isNull());
    file.close();
    btIndexedMesh mesh;
    mesh.m_numTriangles = m_indices.count() / 3;
    mesh.m_numVertices = m_vertices.count();
    mesh.m_triangleIndexBase = (const unsigned char*) m_indices.data();
    mesh.m_vertexBase = (const unsigned char*) m_vertices.data();
    mesh.m_triangleIndexStride = sizeof(uint) * 3;
    mesh.m_indexType = PHY_INTEGER; //TODO not very good, unsigned int !!
    mesh.m_vertexStride = sizeof(QVector3D);
    mesh.m_vertexType = PHY_FLOAT;
    btTriangleIndexVertexArray *trimesh = new btTriangleIndexVertexArray;
    trimesh->addIndexedMesh(mesh, PHY_INTEGER);
    m_shape = new btBvhTriangleMeshShape(trimesh, true, true);
    m_shape->setLocalScaling(btVector3(KxBulletUtil::scale(), KxBulletUtil::scale(), KxBulletUtil::scale()));
}
