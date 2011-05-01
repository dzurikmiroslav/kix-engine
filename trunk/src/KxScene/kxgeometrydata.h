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

#ifndef KXGEOMETRYDATA_H
#define KXGEOMETRYDATA_H

#include <QtDeclarative/qdeclarative.h>
#include <QtCore/qvector.h>
#include <QtGui/qvector3d.h>
#include <QtGui/qvector2d.h>
#include "kxmath.h"

class KxCamera;

class KxGeometryData : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int trianglesCount READ trianglesCount FINAL)

public:
    explicit KxGeometryData(QObject *parent = 0);

    virtual inline int trianglesCount() const;

    inline const QVector<QVector3D> &vertices() const;
    inline void setVertices(const QVector<QVector3D> &value);

    inline const QVector<QVector3D> &normals() const;
    inline void setNormals(const QVector<QVector3D> &value);
    inline bool hasNormals() const;
    virtual bool computeNormals();  //Non smooth normals :(

    inline const QVector<QVector3D> &tangents() const;
    inline void setTangents(const QVector<QVector3D> &value);
    inline bool hasTangents() const;
    virtual bool computeTangents(); //Non smooth tangents :(

    inline const QVector<QVector2D> &texCoords() const;
    inline void setTexCoords(const QVector<QVector2D> &value);
    inline bool hasTexCoords() const;

    virtual void draw() const;

    bool loadFromFile(const QString &fileName);

protected:
    bool loadObjFile(const QString &fileName);

    static bool loadObjFile(const QString &fileName, QList<KxGeometryData *> &geometries, QStringList *materials = 0);

    QVector<QVector3D> m_vertices;
    QVector<QVector3D> m_normals;
    QVector<QVector2D> m_texCoords;
    QVector<QVector3D> m_tangents;

    friend class KxTriangleMesh;
    friend class KxConvecHull;
    friend class KxModel;
    friend class KxModelCon;
    friend class KxMd5Model;
    friend class KxMd5ModelMesh;
};

QML_DECLARE_TYPE(KxGeometryData);


inline int KxGeometryData::trianglesCount() const
{
    return m_vertices.count() / 3;
}

inline bool KxGeometryData::hasNormals() const
{
    return !m_normals.isEmpty();
}

inline bool KxGeometryData::hasTexCoords() const
{
    return !m_texCoords.isEmpty();
}

inline bool KxGeometryData::hasTangents() const
{
    return !m_tangents.isEmpty();
}

inline const QVector<QVector3D> &KxGeometryData::vertices() const
{
    return m_vertices;
}

inline const QVector<QVector3D> &KxGeometryData::normals() const
{
    return m_normals;
}

inline const QVector<QVector3D> &KxGeometryData::tangents() const
{
    return m_tangents;
}

inline const QVector<QVector2D> &KxGeometryData::texCoords() const
{
    return m_texCoords;
}

inline void KxGeometryData::setVertices(const QVector<QVector3D> &value)
{
    m_vertices = value;
    //m_aabb = KxAABB(vertices);
}

inline void KxGeometryData::setNormals(const QVector<QVector3D> &value)
{
    m_normals = value;
}

inline void KxGeometryData::setTangents(const QVector<QVector3D> &value)
{
    m_tangents = value;
}

inline void KxGeometryData::setTexCoords(const QVector<QVector2D> &value)
{
    m_texCoords = value;
}


#endif // KXGEOMETRYDATA_H
