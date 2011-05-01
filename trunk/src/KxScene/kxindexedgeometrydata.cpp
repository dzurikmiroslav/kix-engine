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

#include "kxindexedgeometrydata.h"
#include <QtOpenGL/qgl.h>
#include "KxEngine/kxsimdutils.h"

KxIndexedGeometryData::KxIndexedGeometryData(QObject *parent) :
    KxGeometryData(parent)
{
}

void KxIndexedGeometryData::draw() const
{
    glDrawElements(GL_TRIANGLES, m_indices.count(), GL_UNSIGNED_INT, m_indices.constData());
}

bool KxIndexedGeometryData::computeNormals()
{
    if (m_indices.isEmpty() || m_vertices.isEmpty())
        return false;
    if (m_normals.count() != m_vertices.count())
        m_normals.resize(m_vertices.count());
    kxSIMDUtils->computeIndexedNormals(m_normals.data(),
                                       m_vertices.constData(), m_vertices.count(),
                                       m_indices.constData(), m_indices.count());
    /*for (int i = 0; i < m_indices.count(); i += 3) {
        QVector3D a = m_vertices[m_indices[i + 0]] - m_vertices[m_indices[i + 1]];
        QVector3D b = m_vertices[m_indices[i + 0]] - m_vertices[m_indices[i + 2]];
        QVector3D n = QVector3D::crossProduct(b, a).normalized();
        m_normals[m_indices[i + 0]] += n;
        m_normals[m_indices[i + 1]] += n;
        m_normals[m_indices[i + 2]] += n;
    }
    for (int i = 0; i < m_normals.count(); i++)
        m_normals[i].normalize();
    */
    return true;
}

bool KxIndexedGeometryData::computeTangents()
{
    if(m_vertices.isEmpty() || m_texCoords.isEmpty() || m_indices.isEmpty())
        return false;
    if(m_tangents.count() != m_vertices.count())
        m_tangents.resize(m_vertices.count());
    kxSIMDUtils->computeIndexedTangents(m_tangents.data(),
                                        m_vertices.constData(), m_normals.constData(), m_texCoords.constData(),
                                        m_vertices.count(), m_indices.constData(), m_indices.count());
    /*QVector<QVector3D> sTan(m_vertices.count());
    QVector<QVector3D> tTan(m_vertices.count());
    for (int i = 0; i < m_indices.count(); i+= 3) {
        const QVector3D &v0 = m_vertices[m_indices[i + 0]];
        const QVector3D &v1 = m_vertices[m_indices[i + 1]];
        const QVector3D &v2 = m_vertices[m_indices[i + 2]];
        const QVector2D &w0 = m_texCoords[m_indices[i + 0]];
        const QVector2D &w1 = m_texCoords[m_indices[i + 1]];
        const QVector2D &w2 = m_texCoords[m_indices[i + 2]];
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
            sTan[m_indices[i + j]] += sDir;
            tTan[m_indices[i + j]] += tDir;
        }
    }
    for (int i = 0; i < m_vertices.count(); i++) {
        const QVector3D &n = m_normals[i];
        const QVector3D &t = sTan[i];
        // Gram-Schmidt orthogonalize
        m_tangents[i] = (t - n * QVector3D::dotProduct(n, t));
        m_tangents[i].normalize();
        // Calculate handedness
        if (QVector3D::dotProduct(QVector3D::crossProduct(n, t), tTan[i]) < 0.0f)
            m_tangents[i] = -m_tangents[i];
    }*/
    return true;
}
