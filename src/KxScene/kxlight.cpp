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

#include "kxlight.h"
#include "KxEngine/kxengine.h"
#include "kxscene.h"

KxLight::KxLight(QObject *parent) :
    KxSceneNode(parent)
{
    m_directional = false;
    m_linearAttenuation = 0;
    m_quadraticAttenuation = 0;
    m_constantAttenuation = 1;
    m_spotExponent = 1;
    m_spotCutoff = 0;
}

KxLight::~KxLight()
{
}

QVector3D KxLight::absoluteSpotDirection() const
{
    QVector3D dir = m_spotDirection;
    const KxSceneNode *parNode = m_parentNode;
    while (parNode) {
        dir = parNode->m_rotation.rotatedVector(dir);
        dir = parNode->m_localRotation.rotatedVector(dir);
        parNode = parNode->m_parentNode;
    }
    return dir;
}


/*
void KxLight::setScene(KxScene *value)
{
    if ((!value) && m_scene) {
        m_scene->removeLight(this);
        m_scene = NULL;
        emit sceneChanged();
    } else if(m_scene != value) {
        m_scene = value;
        m_scene->addLight(this);
        emit sceneChanged();
    }
}
*/
