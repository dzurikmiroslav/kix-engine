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

#include "kxmodelcon.h"
#include "kxmodel.h"
#include "kxmaterial.h"
#include "kxgeometrydata.h"
#include "KxDeclarative/kxdeclarative.h"
#include <QtCore/qfile.h>


KxModelCon::KxModelCon(QObject *parent) :
    KxDrawableSceneNodeCon(parent)
{
    m_source = "";
}

void KxModelCon::setSource(const QString &value)
{
    if(loadFromFile(value))
        m_source = value;
}

KxModel *KxModelCon::create(QObject *parent) const
{
    KxModel *node = new KxModel(parent);
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

bool KxModelCon::loadFromFile(const QString &fileName)
{
    if(QFile::exists(fileName)) {
        if(fileName.endsWith(".obj", Qt::CaseInsensitive)) {
            loadObjFile(fileName);
            return true;
        }
        qWarning() << "KxModelCon::loadFromFile uknow format addictive" << fileName;
        return false;
    } else {
        qWarning() << "KxModelCon::loadFromFile fole not exisit" << fileName;
        return false;
    }
}

bool KxModelCon::loadObjFile(const QString &fileName)
{
    qDebug() << "KxModelCon::loadObjFile" << fileName;
    QStringList materials;
    QList<KxGeometryData*> geometryDatas;
    if(KxGeometryData::loadObjFile(fileName, geometryDatas, &materials)) {
        foreach(KxGeometryData *geometryData, geometryDatas) {
            KxDrawableSceneNodeCon *mesh = new KxDrawableSceneNodeCon(this);
            geometryData->setParent(mesh);
            mesh->setGeometryData(geometryData);
            mesh->setMaterial(kxDeclarative->loadMaterial(materials.first(), mesh));
            materials.removeFirst();
            m_childrenNodes << mesh;
        }
        return true;
    }
    return false;
}
