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

#include "kxdrawablescenenode.h"
#include "kxcamera.h"
#include "KxEngine/kxgldrawer.h"

KxDrawableSceneNode::KxDrawableSceneNode(QObject *parent) :
    KxSceneNode(parent)
{
    m_material = NULL;
    m_geometryData = NULL;
    m_fromConstructionInfo = false;
}

void KxDrawableSceneNode::draw(KxCamera *camera, DrawFlags flags)
{
    QMutexLocker locker(&m_mutex);
    Q_UNUSED(locker);
    if (!m_visible)
        return;
    if ((flags & SortedToQueue) && material()) {
        if (material()->isSorting()) {
            camera->addSortedNode(this);
            return;
        }
    }
    kxGLDrawer->pushModelViewMatrix();  //save
    if (flags & UseAbsoluteTransform) {
        QStack<KxSceneNode *> parNodes;
        KxSceneNode *node = this;
        while (node) {
            node = node->parentNode();
            parNodes << node;
        }
        parNodes.pop();
        while (!parNodes.isEmpty())
            parNodes.pop()->applyTransforms();
    }
    applyTransforms();
    if (geometryData() && material()) {
        material()->bind(camera, this);
        geometryData()->draw();
        material()->release();
    }
    //draw children nodes
    foreach (KxSceneNode *n, m_childrenNodes)
        n->draw(camera, flags);
    kxGLDrawer->popModelViewMatrix();   //load
}

KxMaterial *KxDrawableSceneNode::material() const
{
    return m_material;
}

void KxDrawableSceneNode::setMaterial(KxMaterial *value)
{
    m_material = value;
    emit materialChanged();
}

KxGeometryData *KxDrawableSceneNode::geometryData() const
{
    return m_geometryData;
}

void KxDrawableSceneNode::setGeometryData(KxGeometryData *value)
{
    m_geometryData = value;
    emit geometryDataChanged();
}
