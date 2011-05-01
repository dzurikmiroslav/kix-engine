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

#include "kxscene.h"
#include "kxcamera.h"
#include "KxEngine/kxengine.h"
#include "kxlight.h"


KxScene::KxScene(QObject *parent) :
    KxSceneNode(parent)
{
    setObjectName("root node");
}

KxScene::~KxScene()
{
    //delete modelFactory;
    //delete graphicMaterialFactory;
    //delete shareWidget;
}

/*
void KxScene::update(int ms)
{
    update(ms);
    foreach (KxCamera *camera, m_cameras)
        camera->update(ms);
}*/

//TODO
QList<KxLight*> KxScene::lightsForNode(KxSceneNode *node) const
{
    Q_UNUSED(node);
    QList<KxLight*> lights;
    for (int i = 0; i < 8 && i < m_lights.count(); i++) {
        if (m_lights[i]->isVisible())
            lights << m_lights[i];
    }
    return lights;
}

void KxScene::bubbleUpLightNode(KxSceneNode *node)
{
    if (node->nodeType() == LightNode)
        m_lights << qobject_cast<KxLight*>(node);
}

void KxScene::addCamera(KxCamera *camera)
{
    m_cameras << camera;
}

void KxScene::removeCamera(KxCamera *camera)
{
    m_cameras.removeAll(camera);
}

void KxScene::removeLight(KxLight *light)
{
    //m_mutex.lock();
    m_lights.removeAll(light);
    //m_mutex.unlock();
}

void KxScene::addLight(KxLight *light)
{
    //m_mutex.lock();
    m_lights << light;
    //m_mutex.unlock();
}
