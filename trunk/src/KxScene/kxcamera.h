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

#ifndef KX_CAMERA_H
#define KX_CAMERA_H

#include <QtCore/qvector.h>
#include <QtCore/qqueue.h>
#include <QtCore/qstack.h>
#include <QtCore/qmutex.h>
#include <QtGui/qmatrix4x4.h>
#include <QtGui/qvector2d.h>
#include <QtOpenGL/qgl.h>
#include <QtDeclarative/qdeclarative.h>
#include "kxscenenode.h"

class KxUserInputs;
class KxScene;
class KxLight;
class KxLightPolicyInterface;

class KxCamera: public KxSceneNode
{
    Q_OBJECT
    Q_PROPERTY(KxSceneNode *rootNode READ rootNode FINAL CONSTANT)
    Q_PROPERTY(QVector3D eye READ eye WRITE setEye NOTIFY eyeChanged FINAL)
    Q_PROPERTY(QVector3D center READ center WRITE setCenter NOTIFY centerChanged FINAL)
    Q_PROPERTY(QVector3D up READ up WRITE setUp NOTIFY upChanged FINAL)
    Q_PROPERTY(qreal fieldOfView READ fieldOfView WRITE setFieldOfView FINAL)
    Q_PROPERTY(qreal nearPlane READ nearPlane WRITE setNearPlane FINAL)
    Q_PROPERTY(qreal farPlane READ farPlane WRITE setFarPlane FINAL)
    Q_PROPERTY(QVector3D direction READ direction WRITE setDirection NOTIFY centerChanged FINAL)

public:
    explicit KxCamera(QObject *parent = 0);
    ~KxCamera();

    virtual void update(int ms);

    const QVector3D& eye() const;
    Q_SLOT void setEye(const QVector3D& eye);

    const QVector3D& center() const;
    Q_SLOT virtual void setCenter(const QVector3D& center);

    const QVector3D& up() const;
    void setUp(const QVector3D& up);

    qreal nearPlane() const;
    void setNearPlane(qreal value);

    qreal farPlane() const;
    void setFarPlane(qreal value);

    qreal fieldOfView() const;
    void setFieldOfView(qreal value);

    KxScene *scene() const;
    void setScene(KxScene *value);

    QVector3D direction() const;
    Q_SLOT void setDirection(const QVector3D &direction);

    const QVector3D &position() const;
    Q_SLOT void setPosition(const QVector3D &position);

    KxSceneNode *rootNode() const;

    virtual int nodeType() const { return CameraNode; }

public slots:
    void sphereRotate(const QVector2D& delta);  //gulova rotacia, fps
    void lookAt(const QVector3D& eye, const QVector3D& center, const QVector3D& up = QVector3D(0, 1, 0));
    void translate(const QVector3D& value); //posunie eye a center

signals:
    void directionArroundYChanged(QVector3D directon); //for KxCharacterController
    void eyeChanged(const QVector3D& eye);
    void centerChanged(const QVector3D& center);
    void upChanged(const QVector3D& up);

protected:
    QList<KxLight *> lightsForNode(KxSceneNode *node) const;
    void addSortedNode(KxSceneNode *node);
    void computeProjectionMatrix(QMatrix4x4 &matrix, qreal aspectRation);
    virtual void computeModelViewMatrix(QMatrix4x4 &matrix);
    void drawScene();

    QMutex m_mutex;
    KxSceneNode *m_rootNode;    //priestor kamery
    QQueue<KxSceneNode *> m_sortedNodes;
    QVector3D m_center;
    QVector3D m_up;
    qreal m_nearPlane;
    qreal m_farPlane;
    qreal m_fieldOfView;
    KxLightPolicyInterface *m_currentLightPolicy;

    friend class KxScene;
    friend class KxDrawableSceneNode;
    friend class KxMaterial;
    friend class KxGLDrawer;
};

QML_DECLARE_TYPE(KxCamera);




#endif /* KX_CAMERA_H */
