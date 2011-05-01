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

#ifndef KXDRAWABLESCENENODECON_H
#define KXDRAWABLESCENENODECON_H

#include "kxscenenodecon.h"

class KxSceneNode;
class KxDrawableSceneNode;
class KxMaterial;
class KxGeometryData;

class KxDrawableSceneNodeCon : public KxSceneNodeCon
{
    Q_OBJECT
    Q_PROPERTY(KxGeometryData* geometryData READ geometryData WRITE setGeometryData NOTIFY geometryDataChanged FINAL);
    Q_PROPERTY(KxMaterial *material READ material WRITE setMaterial NOTIFY materialChanged FINAL);

public:
    explicit KxDrawableSceneNodeCon(QObject *parent = 0);

     KxGeometryData *geometryData() const;
     void setGeometryData(KxGeometryData *value);

      KxMaterial *material() const;
      void setMaterial(KxMaterial *value);

     KxSceneNode *create(QObject *parent = 0) const;

signals:
    void materialChanged();
    void geometryDataChanged();

protected:
    KxMaterial *m_material;
    KxGeometryData *m_geometryData;

};

QML_DECLARE_TYPE(KxDrawableSceneNodeCon);


#endif // KXDRAWABLESCENENODECON_H
