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

#ifndef KXSIMDUTILS_H
#define KXSIMDUTILS_H

#include "KxScene/kxmath.h"

struct KxMd5ModelMeshVertexInfo;
struct KxMd5ModelMeshWeight;

class KxSIMDUtils
{
public:
    static KxSIMDUtils *instance();

    //geometry data
    virtual void normalize(QVector3D *vectors, int count);

    virtual void computeNormals(QVector3D *normals, const QVector3D *vertices, int count);
    virtual void computeIndexedNormals(QVector3D *normals,
                                       const QVector3D *vertices, int vertexCount,
                                       const uint *indices, int indexCount);
    virtual void computeTangents(QVector3D *tangents, const QVector3D *vertices, const QVector3D *normals,
                                 const QVector2D *texCoords, int count);
    virtual void computeIndexedTangents(QVector3D *tangents, const QVector3D *vertices, const QVector3D *normals,
                                        const QVector2D *texCoords, int vertexCount,
                                        const uint *indices, int indexCount);

    // MD5 model + animation
    virtual void interpolateJoints(KxTransform *joints, const KxTransform *prevJoints,
                                   const KxTransform *nextJoints, int count, qreal factor);

    virtual void applyJoints(QVector3D *vertices, QVector3D *normals, QVector3D *tangents,
                            const KxMd5ModelMeshVertexInfo *infos, int vertexCount,
                            const KxMd5ModelMeshWeight *weights, const KxTransform *joints);

    virtual void computWeightNormalsTangents(KxMd5ModelMeshWeight *weights, int weithCount,
                                             const QVector3D *normals, const QVector3D *tangents,
                                             const KxMd5ModelMeshVertexInfo *infos, int vertexCount,
                                             const KxTransform *joints);

protected:
    KxSIMDUtils();
    virtual ~KxSIMDUtils();

    static KxSIMDUtils *m_instance;

    friend class KxEngine;
};

#define kxSIMDUtils KxSIMDUtils::instance()

#endif // KXSIMDUTILS_H
