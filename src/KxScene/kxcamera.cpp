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

#include "kxcamera.h"
#include "KxEngine/kxuserinputs.h"
#include "KxEngine/kxengine.h"
#include "kxscene.h"
#include "kxlight.h"
#include <QtCore/qmath.h>
#include "KxPhysics/kxphysicsworld.h"


KxCamera::KxCamera(QObject *parent) :
        KxSceneNode(parent)
{
    m_fieldOfView = 50;
    m_farPlane = 10000;
    m_nearPlane = 0.1;
    m_center = QVector3D(0, 0, -1);
    m_up = QVector3D(0, 1, 0);
    m_rootNode = new KxSceneNode(this);
    m_currentLightPolicy = false;
}

KxCamera::~KxCamera()
{
}

void KxCamera::lookAt(const QVector3D &eye, const QVector3D &center, const QVector3D &up)
{
    m_position = eye;
    m_center = center;
    m_up = up;
    emit upChanged(m_up);
    emit eyeChanged(m_position);
    emit centerChanged(m_center);
}

void KxCamera::translate(const QVector3D &value)
{
    m_mutex.lock();
    m_position += value;
    m_center += value;
    m_mutex.unlock();
    emit eyeChanged(m_position);
    emit centerChanged(m_center);
}

void KxCamera::update(int ms)
{
    m_rootNode->update(ms);
}

const QVector3D &KxCamera::position() const
{
    return m_position;
}

void KxCamera::setPosition(const QVector3D &position)
{
    m_mutex.lock();
    QVector3D dir = m_position - m_center;
    m_position = position;
    m_center = position - dir;
    m_mutex.unlock();
    emit eyeChanged(m_position);
    emit centerChanged(m_center);
}

qreal KxCamera::nearPlane() const
{
    return m_nearPlane;
}

qreal KxCamera::farPlane() const
{
    return m_farPlane;
}

qreal KxCamera::fieldOfView() const
{
    return m_fieldOfView;
}

void KxCamera::setNearPlane(qreal value)
{
    m_nearPlane = value;
}

void KxCamera::setFarPlane(qreal value)
{
    m_farPlane = value;
}

void KxCamera::setFieldOfView(qreal value)
{
    m_fieldOfView =value;
}

QVector3D KxCamera::direction() const
{
    return (m_center - m_position).normalized();
}

const QVector3D& KxCamera::eye() const
{
    return m_position;
}

const QVector3D& KxCamera::center() const
{
    return m_center;
}

const QVector3D& KxCamera::up() const
{
    return m_up;
}

void KxCamera::setEye(const QVector3D& eye)
{
    m_position = eye;
    emit eyeChanged(m_position);
}

void KxCamera::setCenter(const QVector3D& center)
{
    m_center = center;
    emit centerChanged(m_center);
}

void KxCamera::setUp(const QVector3D& up)
{
    m_position = up;
    emit upChanged(m_up);
}

void KxCamera::addSortedNode(KxSceneNode *node)
{
    m_sortedNodes << node;
}

KxSceneNode* KxCamera::rootNode() const
{
    return m_rootNode;
}

QList<KxLight *> KxCamera::lightsForNode(KxSceneNode *node) const
{
    if (m_currentLightPolicy)
        return m_currentLightPolicy->lightsForNode(node);
    else
        return QList<KxLight *>();
}

void KxCamera::drawScene()
{
    if (!m_visible || !m_parentNode)
        return;
    KxSceneNode *parNode = m_parentNode;
    while (parNode->nodeType() != SceneNode && parNode)
        parNode = parNode->m_parentNode;
    m_currentLightPolicy = (KxScene*)parNode;

    if (parNode)
        parNode->draw(this, KxSceneNode::SortedToQueue);
    glDepthMask(GL_FALSE);
    foreach (KxSceneNode *node, m_sortedNodes)
        node->draw(this, KxSceneNode::UseAbsoluteTransform);
    glDepthMask(GL_TRUE);
    m_sortedNodes.clear();
    //camera space
    kxGLDrawer->pushModelViewMatrix();
    kxGLDrawer->modelViewMatrix().setToIdentity();
    m_rootNode->draw(this, KxSceneNode::SortedToQueue);
    glDepthMask(GL_FALSE);
    foreach (KxSceneNode *node, m_sortedNodes)
        node->draw(this, KxSceneNode::UseAbsoluteTransform);
    glDepthMask(GL_TRUE);
    kxGLDrawer->popModelViewMatrix();
    m_sortedNodes.clear();
}

void KxCamera::sphereRotate(const QVector2D& delta)
{
    //qDebug() << delta;
    m_mutex.lock();
    QVector3D direction = m_center - m_position;
    direction.normalize();
    QMatrix4x4 rot;
    rot.rotate(delta.x(), 0, 1, 0);
    QVector3D  yPlaneDir = direction;
    yPlaneDir.setY(0);
    yPlaneDir.normalize();
    rot.rotate(delta.y(), -yPlaneDir.z(), 0, yPlaneDir.x());
    rot.optimize();
    direction = rot * direction;
    if (direction.y() > 0.999) {
        direction.setY(0.999);
        direction.normalize();
    } else if (direction.y() < -0.999) {
        direction.setY(-0.999);
        direction.normalize();
    }
    m_center = direction + m_position;
    m_mutex.unlock();
    emit directionArroundYChanged(yPlaneDir);
    emit eyeChanged(m_position);
    emit centerChanged(m_center);
}

void KxCamera::computeProjectionMatrix(QMatrix4x4 &matrix, qreal aspectRation)
{
    matrix.setToIdentity();
    matrix.perspective(m_fieldOfView, aspectRation, m_nearPlane, m_farPlane);
}

void KxCamera::computeModelViewMatrix(QMatrix4x4 &matrix)
{
    QVector3D absPosition(m_position);
    QVector3D absCenter(m_center);
    QVector3D absUp(m_up);
    KxSceneNode *parNode = m_parentNode;
    while (parNode) {
        absPosition = parNode->m_rotation.rotatedVector(absPosition);
        absPosition += parNode->m_position;
        absPosition = parNode->m_localRotation.rotatedVector(absPosition);
        absPosition += parNode->m_localPosition;
        absCenter = parNode->m_rotation.rotatedVector(absCenter);
        absCenter += parNode->m_position;
        absCenter = parNode->m_localRotation.rotatedVector(absCenter);
        absCenter += parNode->m_localPosition;
        absUp = parNode->m_rotation.rotatedVector(absUp);
        absUp = parNode->m_localRotation.rotatedVector(absUp);
        parNode = parNode->m_parentNode;
    }
    matrix.setToIdentity();
    matrix.lookAt(absPosition, absCenter, absUp);
}

void KxCamera::setDirection(const QVector3D &direction)
{
    m_mutex.lock();
    m_center = m_position + direction;
    QVector3D arroundY = direction;
    arroundY.setY(0);
    emit directionArroundYChanged(arroundY.normalized());
    m_mutex.unlock();
}
