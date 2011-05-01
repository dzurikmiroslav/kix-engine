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

#include "kxscenenodecon.h"
#include "kxscenenode.h"

KxSceneNodeCon::KxSceneNodeCon(QObject *parent) :
    QObject(parent)
{
    m_scale = QVector3D(1, 1, 1);
}

QVariant KxSceneNodeCon::create(const QVariant &parent) const
{
    if (parent.value<QObject*>()) {
       return QVariant::fromValue(create(parent.value<QObject*>()));
    } else {
        qWarning() << "KxSceneNodeCon::create parent is not QObject";
        return QVariant::fromValue(create());
    }
}

KxSceneNode *KxSceneNodeCon::create(QObject *parent) const
{
   // qWarning() << "KxSceneNodeCon::create not usefull method :-), try use child classes";
    KxSceneNode *node = new KxSceneNode(parent);
    foreach(KxSceneNodeCon *nodeInfo, m_childrenNodes)
        node->addChildNode(nodeInfo->create(node));
    node->setParentNode(m_parentNode);
    node->setPosition(m_position);
    node->setRotation(m_rotation);
    node->setLocalPosition(m_localPosition);
    node->setLocalRotation(m_localRotation);
    node->setScale(m_scale);
    node->setVisible(m_visible);
    //node->m_fromConstructionInfo = true;
    return node;
}

