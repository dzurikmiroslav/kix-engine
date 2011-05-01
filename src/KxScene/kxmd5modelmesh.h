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

#ifndef KXMD5MODELMESH_H
#define KXMD5MODELMESH_H

#include "kxdrawablescenenode.h"
#include "kxindexedgeometrydata.h"

class KxMd5Model;

struct KxMd5ModelMeshVertexInfo
{
    int m_weighIndex;
    int m_weightElem;
};

struct KxMd5ModelMeshWeight
{
    int m_jointIndex;
    qreal m_weightValue;
    QVector3D m_position;
    QVector3D m_normal;
    QVector3D m_tangent;
};

class KxMd5ModelMesh : public KxDrawableSceneNode
{
    //Q_OBJECT

public:
    virtual inline void setGeometryData(KxGeometryData *value);

    virtual void update(int ms);

    virtual int nodeType() const { return DrawableNode; }

private:
    explicit KxMd5ModelMesh(KxMd5Model *model);

    void computeNormalsAndTangents();

    void applyJoints();

    QVector<KxMd5ModelMeshVertexInfo> m_vertexInfos;
    QVector<KxMd5ModelMeshWeight> m_weights;
    KxMd5Model *m_model;

    friend class KxMd5Model;
};

inline void KxMd5ModelMesh::setGeometryData(KxGeometryData *value)
{
    Q_UNUSED(value);
    qFatal("KxMd5ModelMesh::setGeometryData this mesh cant change geometry data");
}


#endif // KXMD5MODELMESH_H
