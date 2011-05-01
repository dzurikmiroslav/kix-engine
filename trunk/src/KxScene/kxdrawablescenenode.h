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

#ifndef KXDRAWABLESCENENODE_H
#define KXDRAWABLESCENENODE_H

#include "kxscenenode.h"

class KxDrawableSceneNode : public KxSceneNode
{
    Q_OBJECT
    Q_PROPERTY(KxMaterial *material READ material WRITE setMaterial NOTIFY materialChanged FINAL)
    Q_PROPERTY(KxGeometryData* geometryData READ geometryData WRITE setGeometryData NOTIFY geometryDataChanged FINAL)

public:
    KxDrawableSceneNode(QObject *parent = 0);

    virtual void draw(KxCamera *camera, DrawFlags flags = None);

    virtual KxMaterial *material() const;
    virtual void setMaterial(KxMaterial *value);

    virtual KxGeometryData *geometryData() const;
    virtual void setGeometryData(KxGeometryData *value);

signals:
    void materialChanged();
    void geometryDataChanged();

protected:
    KxMaterial *m_material;
    KxGeometryData *m_geometryData;
    bool m_fromConstructionInfo : 1;

    friend class KxDrawableSceneNodeCon;
    friend class KxModelMeshCon;
};

QML_DECLARE_TYPE(KxDrawableSceneNode);

#endif // KXDRAWABLESCENENODE_H
