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

#include "kxsimdutils.h"
#include <QtCore/qdebug.h>
#include "KxScene/kxmd5modelmesh.h"

KxSIMDUtils *KxSIMDUtils::m_instance;

KxSIMDUtils::KxSIMDUtils()
{
}

KxSIMDUtils::~KxSIMDUtils()
{
}

KxSIMDUtils *KxSIMDUtils::instance()
{
    return m_instance;
}

void KxSIMDUtils::computeIndexedNormals(QVector3D *normals,
                                        const QVector3D *vertices, int vertexCount,
                                        const uint *indices, int indexCount)
{
    for (int i = 0; i < indexCount; i += 3) {
        QVector3D a = vertices[indices[i + 0]] - vertices[indices[i + 1]];
        QVector3D b = vertices[indices[i + 0]] - vertices[indices[i + 2]];
        QVector3D n = QVector3D::crossProduct(b, a).normalized();
        normals[indices[i + 0]] += n;
        normals[indices[i + 1]] += n;
        normals[indices[i + 2]] += n;
    }
    normalize(normals, vertexCount);
}

void KxSIMDUtils::computeIndexedTangents(QVector3D *tangents, const QVector3D *vertices,
                                         const QVector3D *normals, const QVector2D *texCoords,
                                         int vertexCount, const uint *indices, int indexCount)
{
    QVector<QVector3D> sTan(vertexCount);
    QVector<QVector3D> tTan(vertexCount);
    for (int i = 0; i < indexCount; i+= 3) {
        const QVector3D &v0 = vertices[indices[i + 0]];
        const QVector3D &v1 = vertices[indices[i + 1]];
        const QVector3D &v2 = vertices[indices[i + 2]];
        const QVector2D &w0 = texCoords[indices[i + 0]];
        const QVector2D &w1 = texCoords[indices[i + 1]];
        const QVector2D &w2 = texCoords[indices[i + 2]];
        float x1 = v1.x() - v0.x();
        float x2 = v2.x() - v0.x();
        float y1 = v1.y() - v0.y();
        float y2 = v2.y() - v0.y();
        float z1 = v1.z() - v0.z();
        float z2 = v2.z() - v0.z();
        float s1 = w1.x() - w0.x();
        float s2 = w2.x() - w0.x();
        float t1 = w1.y() - w0.y();
        float t2 = w2.y() - w0.y();
        float r = (s1 * t2) - (s2 * t1);
        if (r == 0.0f)
            r = 1.0f;
        float oneOverR = 1.0f / r;
        QVector3D sDir ((t2 * x1 - t1 * x2) * oneOverR,
                        (t2 * y1 - t1 * y2) * oneOverR,
                        (t2 * z1 - t1 * z2) * oneOverR);
        QVector3D tDir ((s1 * x2 - s2 * x1) * oneOverR,
                        (s1 * y2 - s2 * y1) * oneOverR,
                        (s1 * z2 - s2 * z1) * oneOverR);
        for (int j = 0; j < 3; ++j) {
            sTan[indices[i + j]] += sDir;
            tTan[indices[i + j]] += tDir;
        }
    }
    for (int i = 0; i < vertexCount; i++) {
        const QVector3D &n = normals[i];
        const QVector3D &t = sTan[i];
        // Gram-Schmidt orthogonalize
        tangents[i] = (t - n * QVector3D::dotProduct(n, t));
        tangents[i].normalize();
        // Calculate handedness
        if (QVector3D::dotProduct(QVector3D::crossProduct(n, t), tTan[i]) < 0.0f)
            tangents[i] = -tangents[i];
    }
}

void KxSIMDUtils::normalize(QVector3D *vectors, int count)
{
    for (int i = 0; i < count; i++)
        vectors[i].normalize();
}

void KxSIMDUtils::computeNormals(QVector3D *normals, const QVector3D *vertices, int count)
{
    for (int i = 0; i < count; i += 3) {
        QVector3D a = vertices[i + 0] - vertices[i + 1];
        QVector3D b = vertices[i + 0] - vertices[i + 2];
        QVector3D n = QVector3D::crossProduct(b, a).normalized();
        for (int j = 0; j < 3; j++)
            normals[i + j] = n;
    }
}

void KxSIMDUtils::computeTangents(QVector3D *tangents, const QVector3D *vertices, const QVector3D *normals,
                                  const QVector2D *texCoords, int count)
{
    QVector<QVector3D> sTan(count);
    QVector<QVector3D> tTan(count);
    for (int i = 0; i < count; i+= 3) {
        const QVector3D &v0 = vertices[i + 0];
        const QVector3D &v1 = vertices[i + 1];
        const QVector3D &v2 = vertices[i + 2];
        const QVector2D &w0 = texCoords[i + 0];
        const QVector2D &w1 = texCoords[i + 1];
        const QVector2D &w2 = texCoords[i + 2];
        float x1 = v1.x() - v0.x();
        float x2 = v2.x() - v0.x();
        float y1 = v1.y() - v0.y();
        float y2 = v2.y() - v0.y();
        float z1 = v1.z() - v0.z();
        float z2 = v2.z() - v0.z();
        float s1 = w1.x() - w0.x();
        float s2 = w2.x() - w0.x();
        float t1 = w1.y() - w0.y();
        float t2 = w2.y() - w0.y();
        float r = (s1 * t2) - (s2 * t1);
        if (r == 0.0f)
            r = 1.0f;
        float oneOverR = 1.0f / r;
        QVector3D sDir ((t2 * x1 - t1 * x2) * oneOverR,
                        (t2 * y1 - t1 * y2) * oneOverR,
                        (t2 * z1 - t1 * z2) * oneOverR);
        QVector3D tDir ((s1 * x2 - s2 * x1) * oneOverR,
                        (s1 * y2 - s2 * y1) * oneOverR,
                        (s1 * z2 - s2 * z1) * oneOverR);
        for (int j = 0; j < 3; ++j) {
            sTan[i + j] += sDir;
            tTan[i + j] += tDir;
        }
    }
    for (int i = 0; i < count; i++) {
        const QVector3D &n = normals[i];
        const QVector3D &t = sTan[i];
        // Gram-Schmidt orthogonalize
        tangents[i] = (t - n * QVector3D::dotProduct(n, t));
        tangents[i].normalize();
        // Calculate handedness
        if (QVector3D::dotProduct(QVector3D::crossProduct(n, t), tTan[i]) < 0.0f)
            tangents[i] = -tangents[i];
    }
}


void KxSIMDUtils::interpolateJoints(KxTransform *joints,
                                    const KxTransform *prevJoints,
                                    const KxTransform *nextJoints,
                                    int count, qreal factor)
{
    for (int i = 0; i < count; i++)
        joints[i] = KxTransform::interpolate(prevJoints[i], nextJoints[i], factor);
}


void KxSIMDUtils::computWeightNormalsTangents(KxMd5ModelMeshWeight *weights, int weightCount,
                                              const QVector3D *normals, const QVector3D *tangents,
                                              const KxMd5ModelMeshVertexInfo *infos, int vertexCount,
                                              const KxTransform *joints)
{
    for (int i = 0; i < vertexCount; i++) {
        for (int j = 0; j < infos[i].m_weightElem; j++) {
            const KxTransform &trans = joints[weights[infos[i].m_weighIndex + j].m_jointIndex];
            weights[infos[i].m_weighIndex + j].m_normal += trans.rotation().conjugate().rotatedVector(normals[i]);
            weights[infos[i].m_weighIndex + j].m_tangent += trans.rotation().conjugate().rotatedVector(tangents[i]);
        }
    }
    for (int i = 0; i < weightCount; i++) {
        weights[i].m_normal.normalize();
        weights[i].m_tangent.normalize();
    }
}

void KxSIMDUtils::applyJoints(QVector3D *vertices, QVector3D *normals, QVector3D *tangents,
                             const KxMd5ModelMeshVertexInfo *infos, int vertexCount,
                             const KxMd5ModelMeshWeight *weights, const KxTransform *joints)
{
    if (normals && tangents) {
        //all
        for (int i = 0; i < vertexCount; i++) {
            QVector3D &pos = vertices[i];
            QVector3D &nor = normals[i];
            QVector3D &tan = tangents[i];
            pos = nor = tan = QVector3D();
            for (int j = 0; j < infos[i].m_weightElem; j++) {
                const KxTransform &trans = joints[weights[infos[i].m_weighIndex + j].m_jointIndex];
                qreal weightWalue = weights[infos[i].m_weighIndex + j].m_weightValue;
                pos += (trans * weights[infos[i].m_weighIndex + j].m_position) * weightWalue;
                nor += trans.rotation().rotatedVector(weights[infos[i].m_weighIndex + j].m_normal) * weightWalue;
                tan += trans.rotation().rotatedVector(weights[infos[i].m_weighIndex + j].m_tangent) * weightWalue;
            }
        }
    } else if (tangents) {
        //no normals
        for (int i = 0; i < vertexCount; i++) {
            QVector3D &pos = vertices[i];
            QVector3D &tan = tangents[i];
            pos = tan = QVector3D();
            for (int j = 0; j < infos[i].m_weightElem; j++) {
                const KxTransform &trans = joints[weights[infos[i].m_weighIndex + j].m_jointIndex];
                qreal weightWalue = weights[infos[i].m_weighIndex + j].m_weightValue;
                pos += (trans * weights[infos[i].m_weighIndex + j].m_position) * weightWalue;
                tan += trans.rotation().rotatedVector(weights[infos[i].m_weighIndex + j].m_tangent) * weightWalue;
            }
        }
    } else if (normals) {
        //no tangents
        for (int i = 0; i < vertexCount; i++) {
            QVector3D &pos = vertices[i];
            QVector3D &nor = normals[i];
            pos = nor = QVector3D();
            for (int j = 0; j < infos[i].m_weightElem; j++) {
                const KxTransform &trans = joints[weights[infos[i].m_weighIndex + j].m_jointIndex];
                qreal weightWalue = weights[infos[i].m_weighIndex + j].m_weightValue;
                pos += (trans * weights[infos[i].m_weighIndex + j].m_position) * weightWalue;
                nor += trans.rotation().rotatedVector(weights[infos[i].m_weighIndex + j].m_normal) * weightWalue;
            }
        }
    } else {
        //no normals + tangents
        for (int i = 0; i < vertexCount; i++) {
            QVector3D &pos = vertices[i];
            pos = QVector3D();
            for (int j = 0; j < infos[i].m_weightElem; j++) {
                const KxTransform &trans = joints[weights[infos[i].m_weighIndex + j].m_jointIndex];
                qreal weightWalue = weights[infos[i].m_weighIndex + j].m_weightValue;
                pos += (trans * weights[infos[i].m_weighIndex + j].m_position) * weightWalue;
            }
        }
    }
}
