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

#include "kxscenenode.h"
#include "kxcamera.h"
#include "kxgeometrydata.h"
#include "KxEngine/kxgldrawer.h"
#include "kxscene.h"
#include "KxEngine/kxengine.h"

KxSceneNode::KxSceneNode(QObject *parent) :
    QObject(parent)
{
    m_parentNode = NULL;
    m_visible = true;
    m_scale = QVector3D(1, 1, 1);
}

KxSceneNode::~KxSceneNode()
{
    if (m_parentNode)
        m_parentNode->removeChildNode(this);
    foreach (KxSceneNode *childNode, m_childrenNodes)
        childNode->m_parentNode = NULL;
}

void KxSceneNode::bubbleUpLightNode(KxSceneNode *node)
{
    if (m_parentNode)
        m_parentNode->bubbleUpLightNode(node);
}

void KxSceneNode::applyTransforms()
{
    kxGLDrawer->modelViewMatrix().translate(m_position);
    kxGLDrawer->modelViewMatrix().rotate(m_rotation);
    kxGLDrawer->modelViewMatrix().translate(m_localPosition);
    kxGLDrawer->modelViewMatrix().rotate(m_localRotation);
    kxGLDrawer->modelViewMatrix().scale(m_scale);
}

void KxSceneNode::draw(KxCamera *camera, DrawFlags flags)
{
    QMutexLocker locker(&m_mutex);
    Q_UNUSED(locker);
    if (!m_visible)
        return;
    kxGLDrawer->pushModelViewMatrix();  //save
    applyTransforms();
    foreach (KxSceneNode *n, m_childrenNodes)
        n->draw(camera, flags);
    kxGLDrawer->popModelViewMatrix();   //load
}

void KxSceneNode::addChildNode(KxSceneNode *node)
{
    if (!m_childrenNodes.contains(node)) {
        if (node->nodeType() == LightNode)
            bubbleUpLightNode(node);
        m_childrenNodes.append(node);
        node->m_parentNode = this;
        emit childrenNodesChanged();
    } else {
        qWarning() << "KxSceneNode::addChildNode children node alredy added";
    }
}

void KxSceneNode::setParentNode(KxSceneNode *value)
{
    if (m_parentNode)
        m_parentNode->removeChildNode(this);
    if (value)
        value->addChildNode(this);
    else
        m_parentNode = NULL;
}

KxAABB KxSceneNode::aabb() const
{
    return KxAABB();
}


QDeclarativeListProperty<KxSceneNode> KxSceneNode::qmlChildrenNodes()
{
    return QDeclarativeListProperty<KxSceneNode>(this, m_childrenNodes);
}

void KxSceneNode::transform(const QVector3D& position, const QQuaternion& rotation)
{
    m_rotation *= rotation;
    m_position += rotation.rotatedVector(position);
    emit transformChanged(m_position, m_rotation);
    emit positionChanged(m_position);
    emit rotationChanged(m_rotation);
}

void KxSceneNode::localTransform(const QVector3D& position, const QQuaternion& rotation)
{
    m_localRotation *= rotation;
    m_localPosition += rotation.rotatedVector(position);
}

int KxSceneNode::childrenNodesCount() const
{
    return m_childrenNodes.count();
}

void KxSceneNode::update(int ms)
{
    foreach(KxSceneNode *node, m_childrenNodes)
        node->update(ms);
}

bool KxSceneNode::isVisible() const
{
    return m_visible;
}

void KxSceneNode::setVisible(bool hide)
{
    m_visible = hide;
}

QVector3D KxSceneNode::absolutePosition() const
{
    QVector3D pos = m_position;
    const KxSceneNode *parNode = m_parentNode;
    while (parNode) {
        pos = parNode->m_rotation.rotatedVector(pos);
        pos += parNode->m_position;
        pos = parNode->m_localRotation.rotatedVector(pos);
        pos += parNode->m_localPosition;
        parNode = parNode->m_parentNode;
    }
    return pos;
}

QQuaternion KxSceneNode::absoluteRotation() const
{
    QQuaternion rot = m_rotation;
    const KxSceneNode *parNode = m_parentNode;
    while (parNode) {
        rot *= parNode->m_rotation;
        rot *= parNode->m_localRotation;
        parNode = parNode->m_parentNode;
    }
    return rot;
}

const QVector3D& KxSceneNode::position() const
{
    return m_position;
}

const QQuaternion& KxSceneNode::rotation() const
{
    return m_rotation;
}

const QQuaternion& KxSceneNode::localRotation() const
{
    return m_localRotation;
}

const QVector3D& KxSceneNode::localPosition() const
{
    return m_localPosition;
}

const QVector3D& KxSceneNode::scale() const
{
    return m_scale;
}

void KxSceneNode::setPosition(const QVector3D& position)
{
    m_position = position;
    emit transformChanged(m_position, m_rotation);
    emit positionChanged(m_position);
}

void KxSceneNode::setRotation(const QQuaternion &rotation)
{
    m_rotation = rotation;
    emit transformChanged(m_position, m_rotation);
    emit rotationChanged(m_rotation);
}

void KxSceneNode::setLocalPosition(const QVector3D &value)
{
    m_localPosition = value;
}

void KxSceneNode::setLocalRotation(const QQuaternion &value)
{
    m_localRotation = value;
}

void KxSceneNode::setScale(const QVector3D& scale)
{
    m_scale = scale;
}

void KxSceneNode::setTransform(const QVector3D& position, const QQuaternion& rotation)
{
    m_position = position;
    m_rotation = rotation;
    emit transformChanged(m_position, m_rotation);
    emit positionChanged(m_position);
    emit rotationChanged(m_rotation);
}

void KxSceneNode::setLocalTransform(const QVector3D& position, const QQuaternion& rotation)
{
    m_localPosition = position;
    m_localRotation = rotation;
}

void KxSceneNode::rotate(const QQuaternion &value)
{
    m_rotation *= value;
    emit transformChanged(m_position, m_rotation);
    emit rotationChanged(m_rotation);
}

void KxSceneNode::translate(const QVector3D &value)
{
    m_position += value;
    emit transformChanged(m_position, m_rotation);
    emit positionChanged(m_position);
}

int KxSceneNode::nodeType() const
{
    return AbstractNode;
}

const KxScene *KxSceneNode::scene() const
{
    if (!m_parentNode)
        return qobject_cast<const KxScene *>(this);
    else
        return m_parentNode->scene();
}

void KxSceneNode::localRotate(const QQuaternion &value)
{
    m_localRotation *= value;
}

void KxSceneNode::localTranslate(const QVector3D &value)
{
    m_localPosition += value;
}

const QList<KxSceneNode*>& KxSceneNode::childrenNodes() const
{
    return m_childrenNodes;
}

KxSceneNode *KxSceneNode::parentNode() const
{
    return m_parentNode;
}

void KxSceneNode::removeChildNode(KxSceneNode *node)
{
    m_mutex.lock();
    m_childrenNodes.removeAll(node);
    m_mutex.unlock();
}
