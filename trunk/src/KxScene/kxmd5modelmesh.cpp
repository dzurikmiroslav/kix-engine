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

#include "kxmd5model.h"
#include "kxmd5modelmesh.h"
#include "KxEngine/kxsimdutils.h"

KxMd5ModelMesh::KxMd5ModelMesh(KxMd5Model *model) :
        KxDrawableSceneNode(model)
{
    m_model = model;
}

void KxMd5ModelMesh::applyJoints()
{
    kxSIMDUtils->applyJoints(m_geometryData->m_vertices.data(),
                            m_geometryData->m_normals.data(),
                            m_geometryData->m_tangents.data(),
                            m_vertexInfos.constData(), m_vertexInfos.count(),
                            m_weights.constData(), m_model->m_joints.constData());
}

void KxMd5ModelMesh::update(int ms)
{
    Q_UNUSED(ms);
    if (m_model->m_animation && m_model->m_animating)
        applyJoints();
}

void KxMd5ModelMesh::computeNormalsAndTangents()
{
    //apply joints to vertices
    /*QVector3D *vertices = m_geometryData->m_vertices.data();
    for (int i = 0; i < m_geometryData->m_vertices.count(); i++) {
        QVector3D pos;
        for (int j = 0; j < m_vertexInfos[i].m_weightElem; j++) {
            const KxTransform &trans = m_model->m_joints[m_weights[m_vertexInfos[i].m_weighIndex + j].m_jointIndex];
            const qreal &weightWalue = m_weights[m_vertexInfos[i].m_weighIndex + j].m_weightValue;
            pos += (trans * m_weights[m_vertexInfos[i].m_weighIndex + j].m_position) * weightWalue;
        }
        vertices[i] = pos;
    }*/
    kxSIMDUtils->applyJoints(m_geometryData->m_vertices.data(),
                            NULL,
                            NULL,
                            m_vertexInfos.constData(), m_vertexInfos.count(),
                            m_weights.constData(), m_model->m_joints.constData());

    //compute normals + tangents
    m_geometryData->computeNormals();
    m_geometryData->computeTangents();
    kxSIMDUtils->computWeightNormalsTangents(m_weights.data(), m_weights.count(),
                                             m_geometryData->normals().constData(),
                                             m_geometryData->tangents().constData(),
                                             m_vertexInfos.constData(), m_vertexInfos.count(),
                                             m_model->m_joints.constData());
    /*
    const QVector3D *tangents = m_geometryData->m_tangents.constData();
    QVector3D *normals = m_geometryData->m_normals.data();
    for (int i = 0; i < m_vertexInfos.count(); i++) {
        for (int j = 0; j < m_vertexInfos[i].m_weightElem; j++) {
            const KxTransform &trans = m_model->m_joints[m_weights[m_vertexInfos[i].m_weighIndex + j].m_jointIndex];
            m_weights[m_vertexInfos[i].m_weighIndex + j].m_normal += trans.rotation().conjugate().rotatedVector(normals[i]);
            m_weights[m_vertexInfos[i].m_weighIndex + j].m_tangent += trans.rotation().conjugate().rotatedVector(tangents[i]);
        }
    }
    for (int i = 0; i < m_weights.count(); i++) {
        m_weights[i].m_normal.normalize();
        m_weights[i].m_tangent.normalize();
    }*/
}
