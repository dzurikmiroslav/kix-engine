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

#include "kxmodel.h"
#include "KxDeclarative/kxdeclarative.h"
#include <QtCore/qfile.h>

KxModel::KxModel(QObject *parent) :
    KxSceneNode(parent)
{
}

KxModel::KxModel(const QString &fileName, QObject *parent) :
    KxSceneNode(parent)
{
    setSource(fileName);
}

/*
KxModel::~KxModel()
{
    emit beforeDestroy(this);
}*/

void KxModel::setSource(const QString &value)
{
    if(loadFromFile(value))
        m_source = value;
}

bool KxModel::loadFromFile(const QString &fileName)
{
    if(QFile::exists(fileName)) {
        if(fileName.endsWith(".obj", Qt::CaseInsensitive)) {
            loadObjFile(fileName);
            return true;
        }
        qWarning() << "KxModel::loadFromFile uknow format addictive" << fileName;
        return false;
    } else {
        qWarning() << "KxModel::loadFromFile fole not exisit" << fileName;
        return false;
    }
}

bool KxModel::loadObjFile(const QString &fileName)
{
    qDebug() << "KxModel::loadObjFile" << fileName;
    QStringList materials;
    QList<KxGeometryData*> geometryDatas;
    if(KxGeometryData::loadObjFile(fileName, geometryDatas, &materials)) {
        foreach(KxGeometryData *geometryData, geometryDatas) {           
            KxDrawableSceneNode *mesh = new KxDrawableSceneNode(this);
            geometryData->setParent(mesh);
            mesh->setGeometryData(geometryData);
            mesh->setMaterial(kxDeclarative->loadMaterial(materials.first(), mesh));
            materials.removeFirst();
            addChildNode(mesh);
        }
        return true;
    }
    return false;
}
