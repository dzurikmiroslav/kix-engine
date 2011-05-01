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

#ifndef KXSCENE_H
#define KXSCENE_H

#include "kxcamera.h"
#include "kxlight.h"
#include "kxmodel.h"
#include "kxmd5model.h"

class KxLightPolicyInterface
{
public:
    virtual QList<KxLight *> lightsForNode(KxSceneNode *node) const = 0;
};

class KxScene: public KxSceneNode, public KxLightPolicyInterface
{
    Q_OBJECT

public:
    KxScene(QObject *parent = 0);
    ~KxScene();

    inline const QList<KxLight *> &lights() const;

    //void update(int ms);


    virtual int nodeType() const { return SceneNode; }

private slots:
    void removeLight(KxLight *light);
    void removeCamera(KxCamera *camera);

private:
    void addLight(KxLight *light);
    void addCamera(KxCamera *camera);

    virtual QList<KxLight *> lightsForNode(KxSceneNode *node) const;   //TODO nearest lights for node

    virtual void bubbleUpLightNode(KxSceneNode *node);

    QList<KxCamera*> m_cameras;
    QList<KxLight*> m_lights;

    friend class KxCamera;
    friend class KxLight;
    friend class KxSceneNode;
};

Q_DECLARE_METATYPE(KxScene*);


inline const QList<KxLight*>& KxScene::lights() const
{
    return m_lights;
}


#endif /* KX_SCENE_H */

