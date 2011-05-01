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
#include "KxDeclarative/kxdeclarative.h"
#include <QtCore/qfile.h>
#include <QtCore/qmath.h>
#include "KxEngine/kxsimdutils.h"

KxMd5Model::KxMd5Model(QObject *parent) :
    KxModel(parent)
{
    m_useOriginTranslate = true;
    m_nextFrameJoints = NULL;
    m_prevFrameJoints = NULL;
    m_animation = NULL;
    m_animating = false;
}

KxMd5Model::~KxMd5Model()
{
    if (m_parentNode) {
        m_parentNode->removeChildNode(this);
        m_parentNode = NULL;
    }
    if (m_nextFrameJoints) {
        delete m_nextFrameJoints;
        delete m_prevFrameJoints;
    }
}

void KxMd5Model::emitFrameChanged(int newFrame)
{
    emit frameChanged(newFrame);
}

void KxMd5Model::emitAnimationChanged()
{
    emit animationChanged();
}

void KxMd5Model::emitAnimationFinished(KxMd5Animation *animation)
{
    emit animationFinished(animation);
}

bool KxMd5Model::isLoopAnimating() const
{
    return m_loopAnimating;
}

void KxMd5Model::setLoopAnimating(bool value)
{
    m_loopAnimating = value;
}

bool KxMd5Model::isAnimating() const
{
    return m_animating;
}

void KxMd5Model::setAnimating(bool value)
{
    m_animating = value;
}

int KxMd5Model::frame() const
{
    return m_currFrame;
}

KxMd5Animation *KxMd5Model::animation() const
{
    return m_animation;
}

void KxMd5Model::setAnimation(KxMd5Animation *value)
{
    m_mutex.lock();
    if (value == m_animation) {
        m_animating = true;
        //m_frameTime = 0;
        //m_deltaFrames = 1;
        /* //CHECK
        if (m_animation->framesCount() > 2) {
            m_currFrame = 1;
            m_nextFrame = 2;
        } else {
            m_currFrame = 0;
            m_nextFrame = 1;
        }*/
    } else if (value->m_jointCount == jointCount()) {
        m_animation = value;
        m_animating = true;
        m_frameTime = 0;
        m_currFrame = 0;
        m_nextFrame = 1;
        m_deltaFrames = 1;
    } else {
        qWarning() << "KxMd5Model::setAnimation try set bad animation";
        m_mutex.unlock();
        return;
    }
    //setup first frame
    qSwap(m_nextFrameJoints, m_prevFrameJoints);
    for(int i = 0; i < m_joints.count(); i++) {
        const int &parentId = m_jointParentIds[i];
        if (parentId == -1)
            m_nextFrameJoints[i] = m_animation->m_frames[m_nextFrame].m_joints[i];
        else
            m_nextFrameJoints[i] = m_animation->m_frames[m_nextFrame].m_joints[i] * m_nextFrameJoints[parentId];
    }
    m_mutex.unlock();
}

bool KxMd5Model::isUseOriginTranslate() const
{
    return m_useOriginTranslate;
}

void KxMd5Model::setUseOriginTranstale(bool value)
{
    m_useOriginTranslate = value;
}

int KxMd5Model::jointCount() const
{
    return m_joints.count();
}

void KxMd5Model::update(int ms)
{
    bool emitAnimFinish = false;
    m_mutex.lock();
    if (m_animation && m_animating) {
        int prevFrame = -1;
        m_frameTime += ms;
        quint8 deltaFrames = qCeil(m_frameTime / m_animation->frameTime());
        m_frameTime -= deltaFrames * m_animation->frameTime();
        if (deltaFrames) {  //set next frame
            m_deltaFrames = deltaFrames;
            prevFrame = m_currFrame;
            m_currFrame = m_nextFrame;
            m_nextFrame += deltaFrames;
            if (m_nextFrame >= m_animation->framesCount()) {
                m_nextFrame++;
                while (m_nextFrame >= m_animation->framesCount())
                    m_nextFrame -= m_animation->framesCount();
                if (!m_loopAnimating) {
                    m_animating = false;
                    emitAnimFinish = true;
                }
            }
        }
        if (m_animating) {
            m_frameFactor = (qreal)m_frameTime / (qreal)(m_animation->frameTime() * m_deltaFrames);
            if (deltaFrames) {
                //emit frameChanged
                if (prevFrame >= m_currFrame) {
                    for (int i = prevFrame + 1; i < m_animation->framesCount(); i++)
                        emit frameChanged(i);
                    for (int i = 0; i <= m_currFrame; i++)
                        emit frameChanged(i);
                } else {
                    for (int i = prevFrame + 1; i <= m_currFrame; i++)
                        emit frameChanged(i);
                }
                //set new frame
                qSwap(m_nextFrameJoints, m_prevFrameJoints);
                m_nextFrameJoints[0] = m_animation->m_frames[m_nextFrame].m_joints[0];  //FIX !!! QVector out of range
                if (!m_useOriginTranslate)
                    m_nextFrameJoints[0].setPosition(QVector3D());
                for (int i = 1; i < m_joints.count(); i++)
                    m_nextFrameJoints[i] = m_animation->m_frames[m_nextFrame].m_joints[i] *  m_nextFrameJoints[m_jointParentIds[i]];

            }
            kxSIMDUtils->interpolateJoints(m_joints.data(), m_prevFrameJoints,
                                           m_nextFrameJoints, m_joints.count(), m_frameFactor);
            //emit origin
            QVector3D origin;
            if (receivers(SIGNAL(originChanged(QVector3D))) > 0) {
                const QVector3D &currPos = m_animation->m_frames[m_currFrame].m_joints[0].position();
                const QVector3D &nextPos = m_animation->m_frames[m_nextFrame].m_joints[0].position();
                if (m_currFrame >= m_nextFrame) {
                    const QVector3D &lastPos = m_animation->m_frames[m_animation->framesCount() - 1].m_joints[0].position();
                    const QVector3D &firstPos = m_animation->m_frames[0].m_joints[0].position();
                    origin = currPos + ((lastPos - currPos) + (nextPos - firstPos)) * m_frameFactor;
                } else {
                    origin = currPos + (nextPos - currPos) * m_frameFactor;
                }
                origin = m_rotation.rotatedVector(origin);
                origin = m_localRotation.rotatedVector(origin);
                emit originChanged(origin);
            }
            if (receivers(SIGNAL(originDeltaChanged(QVector3D))) > 0) {
                //FIXME  loop animating !!!
                const QVector3D &currPos = m_animation->m_frames[m_currFrame].m_joints[0].position();
                const QVector3D &nextPos = m_animation->m_frames[m_nextFrame].m_joints[0].position();
                if (m_currFrame >= m_nextFrame) {
                    const QVector3D &lastPos = m_animation->m_frames[m_animation->framesCount() - 1].m_joints[0].position();
                    const QVector3D &firstPos = m_animation->m_frames[1].m_joints[0].position();
                    origin = ((lastPos - currPos) + (nextPos - firstPos));
                } else {
                    origin = (nextPos - currPos);
                }
                origin *= (qreal)ms / (qreal)(m_animation->frameTime() * m_deltaFrames);
                origin = m_rotation.rotatedVector(origin);
                origin = m_localRotation.rotatedVector(origin);
                emit originDeltaChanged(origin);
            }
        }
    }
    foreach (KxSceneNode *node, m_childrenNodes)
        node->update(ms);
    m_mutex.unlock();
    if (emitAnimFinish)
        emit animationFinished(m_animation);
}

bool KxMd5Model::loadFromFile(const QString& fileName)
{
    if (QFile::exists(fileName)) {
        if (fileName.endsWith(".md5mesh", Qt::CaseInsensitive)) {
            qDebug() << "KxMd5Model::loadFromFile" << fileName;
            return loadMd5File(fileName);
        }
        qWarning() << "KxMd5Model::loadFromFile uknow format addictive" << fileName;
        return false;
    } else {
        qWarning() << "KxMd5Model::loadFromFile file not exist" << fileName;
        return false;
    }
}

bool KxMd5Model::loadMd5File(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "KxMd5Model::loadMd5File cant read file" << fileName;
        return false;
    }

    QTextStream stream(&file);
    QString line;

    QRegExp regex("\\s*numJoints\\s+(\\d+).*");
    do {
        line = stream.readLine();
    } while((regex.indexIn(line) == -1) && (!line.isNull()));
    int numJoints = regex.cap(1).toInt();

    regex.setPattern("\\s*numMeshes\\s+(\\d+).*");
    do {
        line = stream.readLine();
    } while((regex.indexIn(line) == -1) && (!line.isNull()));
    int numMeshes = regex.cap(1).toInt();

    regex.setPattern("\\s*joints\\s*\\{");
    do {
        line = stream.readLine();
    } while((!regex.exactMatch(line)) && (!line.isNull()));

    regex.setPattern("\\s*\"(.*)\"\\s*(\\S+)\\s*\\(\\s*(\\S+)\\s+(\\S+)\\s+(\\S+)\\s*\\)\\s*\\(\\s*(\\S+)\\s+(\\S+)\\s+(\\S+)\\s*\\).*");
    m_nextFrameJoints = new KxTransform[numJoints];
    m_prevFrameJoints = new KxTransform[numJoints];
    m_joints.reserve(numJoints);
    m_jointParentIds.reserve(numJoints);
    m_jointNames.reserve(numJoints);
    for (int i = 0; i < numJoints; i++) {
        do {
            line = stream.readLine();
        } while((regex.indexIn(line) == -1) && (!line.isNull()));
        KxTransform j;
        m_jointNames << regex.cap(1);
        m_jointParentIds << regex.cap(2).toInt();
        j.position().setX(regex.cap(3).toFloat());
        j.position().setY(regex.cap(5).toFloat());
        j.position().setZ(-regex.cap(4).toFloat());
        j.rotation().setX(regex.cap(6).toFloat());
        j.rotation().setY(regex.cap(8).toFloat());
        j.rotation().setZ(-regex.cap(7).toFloat());
        j.rotation().setScalar(1);
        KxMd5Animation::computeQuatScallar(j.rotation());
        m_joints << j;
    }
    qMemCopy(m_nextFrameJoints, m_joints.constData(), numJoints * sizeof(KxTransform));
    qMemCopy(m_prevFrameJoints, m_joints.constData(), numJoints * sizeof(KxTransform));
    //meshes
    regex.setPattern("\\s*mesh\\s*\\{");
    QRegExp shaderReg("\\s*shader\\s*\\\"(.*)\\\".*");
    QRegExp numVertsReg("\\s*numverts\\s*(\\S+).*");
    QRegExp vertReg("\\s*vert\\s*\\d+\\s*\\(\\s*(\\S+)\\s+(\\S+)\\s*\\)\\s*(\\d+)\\s+(\\d+).*");
    QRegExp numTrisReg("\\s*numtris\\s*(\\S+).*");
    QRegExp triReg("\\s*tri\\s+\\d+\\s+(\\d+)\\s+(\\d+)\\s+(\\d+).*");
    QRegExp numWeightsReg("\\s*numweights\\s*(\\S+).*");
    QRegExp weightReg("\\s*weight\\s+\\d+\\s+(\\d+)\\s+(\\S+)\\s+\\(\\s*(\\S+)\\s+(\\S+)\\s+(\\S+)\\s*\\).*");

    for (int i = 0; i < numMeshes; i++) {
        do {
            line = stream.readLine();
        } while((regex.indexIn(line) == -1) && (!line.isNull()));
        KxMd5ModelMesh *mesh = new KxMd5ModelMesh(this);
        KxIndexedGeometryData *geometryData = new KxIndexedGeometryData(mesh);
        mesh->m_geometryData = geometryData;
        /*material*/
        do {
            line = stream.readLine();
        } while((shaderReg.indexIn(line) == -1) && (!line.isNull()));
        mesh->m_material = kxDeclarative->loadMaterial(shaderReg.cap(1));
        /*verts*/
        do {
            line = stream.readLine();
        } while((numVertsReg.indexIn(line) == -1) && (!line.isNull()));
        int count = numVertsReg.cap(1).toInt();
        mesh->m_vertexInfos.resize(count);
        geometryData->m_texCoords.resize(count);
        geometryData->m_vertices.resize(count);
        geometryData->m_normals.resize(count);
        geometryData->m_tangents.resize(count);
        for (int j = 0; j < count; j++) {
            do {
                line = stream.readLine();
            } while((vertReg.indexIn(line) == -1) && (!line.isNull()));
            mesh->m_vertexInfos[j].m_weighIndex = vertReg.cap(3).toInt();
            mesh->m_vertexInfos[j].m_weightElem = vertReg.cap(4).toInt();
            QVector2D coord;
            coord.setX(vertReg.cap(1).toFloat());
            coord.setY(1.0f - vertReg.cap(2).toFloat());
            geometryData->m_texCoords[j] = coord;
        }
        /*tris*/
        do {
            line = stream.readLine();
        } while((numTrisReg.indexIn(line) == -1) && (!line.isNull()));
        count = numTrisReg.cap(1).toInt();
        for (int j = 0; j < count; j++) {
            do {
                line = stream.readLine();
            } while((triReg.indexIn(line) == -1) && (!line.isNull()));
            geometryData->m_indices << triReg.cap(1).toInt();
            geometryData->m_indices << triReg.cap(2).toInt();
            geometryData->m_indices << triReg.cap(3).toInt();
        }
        /*weights*/
        do {
            line = stream.readLine();
        } while((numWeightsReg.indexIn(line) == -1) && (!line.isNull()));
        count = numWeightsReg.cap(1).toInt();
        mesh->m_weights.resize(count);
        for (int j = 0; j < count; j++) {
            do {
                line = stream.readLine();
            } while((weightReg.indexIn(line) == -1) && (!line.isNull()));
            mesh->m_weights[j].m_jointIndex = weightReg.cap(1).toInt();
            mesh->m_weights[j].m_weightValue = weightReg.cap(2).toFloat();
            mesh->m_weights[j].m_position.setX(weightReg.cap(3).toFloat());
            mesh->m_weights[j].m_position.setZ(-weightReg.cap(4).toFloat());
            mesh->m_weights[j].m_position.setY(weightReg.cap(5).toFloat());
        }
        mesh->computeNormalsAndTangents();
        addChildNode(mesh);
    }
    file.close();
    return true;
}

