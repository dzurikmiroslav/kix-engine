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

#ifndef KXSCENENODE_H
#define KXSCENENODE_H

#include <QtDeclarative/qdeclarative.h>
#include <QtGui/qmatrix4x4.h>
#include "kxmath.h"
#include "kxmaterial.h"
#include "kxgeometrydata.h"

class KxCamera;

class KxSceneNode : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QDeclarativeListProperty<KxSceneNode> childrenNodes READ qmlChildrenNodes NOTIFY childrenNodesChanged FINAL)
    Q_PROPERTY(int childrenNodesCount READ childrenNodesCount FINAL)
    Q_PROPERTY(bool visible READ isVisible WRITE setVisible FINAL)
    Q_PROPERTY(QVector3D position READ position WRITE setPosition NOTIFY transformChanged NOTIFY positionChanged FINAL)
    Q_PROPERTY(QQuaternion rotation READ rotation WRITE setRotation NOTIFY transformChanged NOTIFY rotationChanged FINAL)
    Q_PROPERTY(QVector3D localPosition READ localPosition WRITE setLocalPosition FINAL)
    Q_PROPERTY(QQuaternion localRotation READ localRotation WRITE setLocalRotation FINAL)
    Q_PROPERTY(QVector3D absolutePosition READ absolutePosition FINAL)
    Q_PROPERTY(QQuaternion absoluteRotation READ absoluteRotation FINAL)
    Q_PROPERTY(QVector3D scale READ scale WRITE setScale FINAL)
    Q_PROPERTY(KxSceneNode *parentNode READ parentNode WRITE setParentNode NOTIFY parentNodeChanged FINAL)

public:
    enum DrawFlags {
        None = 0,
        SortedToQueue = 1 << 0,   //ak material ma vlastnost 'sorting' sa odlozia do radu v KxCamera
        DrawOnlyShape = 1 << 1, //len tvar
        UseAbsoluteTransform = 1 << 2 //absolutna pozicia, vynasoby poz. rodicov
    };

    enum NodeType {
        AbstractNode,
        SceneNode,
        DrawableNode,
        CameraNode,
        LightNode
    };

    explicit KxSceneNode(QObject *parent = 0);
    ~KxSceneNode();

    virtual void update(int ms); //delta time, milisec

    virtual void draw(KxCamera *camera, DrawFlags flags = None);

    virtual KxAABB aabb() const;    //TODO

    KxSceneNode *parentNode() const;
    void setParentNode(KxSceneNode *value);

    const QList<KxSceneNode*>& childrenNodes() const;
    Q_INVOKABLE void addChildNode(KxSceneNode *node);
    Q_INVOKABLE void removeChildNode(KxSceneNode *node);
    int childrenNodesCount() const;

    bool isVisible() const;
    void setVisible(bool value);

    void setScale(const QVector3D& value);
    const QVector3D& scale() const;

    const QVector3D& position() const;
    Q_SLOT void setPosition(const QVector3D& value);
    Q_SLOT void translate(const QVector3D& value); //posunie

    QVector3D absolutePosition() const;

    QQuaternion absoluteRotation() const;

    const QQuaternion& rotation() const;
    Q_SLOT void setRotation(const QQuaternion& value);
    Q_SLOT void rotate(const QQuaternion& value);  //zrotuje

    const QVector3D& localPosition() const;
    Q_SLOT void setLocalPosition(const QVector3D& value);
    Q_SLOT void localTranslate(const QVector3D& value); //posunie

    const QQuaternion& localRotation() const;
    Q_SLOT void setLocalRotation(const QQuaternion& value);
    Q_SLOT void localRotate(const QQuaternion& value);  //zrotuje

    virtual int nodeType() const;

    const KxScene *scene() const;

public slots:
    void setTransform(const QVector3D& position, const QQuaternion& rotation);
    void setLocalTransform(const QVector3D& position, const QQuaternion& rotation);
    void transform(const QVector3D& position, const QQuaternion& rotation);
    void localTransform(const QVector3D& position, const QQuaternion& rotation);

signals:
    void transformChanged(QVector3D position, QQuaternion rotation);
    void positionChanged(const QVector3D &position);
    void rotationChanged(const QQuaternion &rotation);
    void childrenNodesChanged();
    void parentNodeChanged();

protected:
    QDeclarativeListProperty<KxSceneNode> qmlChildrenNodes();
    void applyTransforms();
    virtual void bubbleUpLightNode(KxSceneNode *node);

    QMutex m_mutex;
    bool m_visible : 1;
    QList<KxSceneNode*> m_childrenNodes;
    KxSceneNode *m_parentNode;
    QVector3D m_position;
    QQuaternion m_rotation;
    QVector3D m_localPosition;
    QQuaternion m_localRotation;
    QVector3D m_scale;

    friend class KxSceneNodeCon;
    friend class KxModelCon;
    friend class KxModelMeshCon;
    friend class KxCamera;
    friend class KxLight;
    friend class KxDrawableSceneNode;
    friend class KxScene;
};

QML_DECLARE_TYPE(KxSceneNode);

#endif // KXSCENENODE_H
