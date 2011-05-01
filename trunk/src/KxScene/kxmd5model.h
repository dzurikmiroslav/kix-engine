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

#ifndef KXMD5MODEL_H
#define KXMD5MODEL_H

#include "kxmodel.h"
#include "kxmd5animation.h"
#include <QtCore/qmutex.h>
#include <QtCore/qvector.h>
#include <QtCore/qtimer.h>

class KxMd5ModelMesh;

class KxMd5Model : public KxModel
{
    Q_OBJECT
    Q_PROPERTY(bool useOriginTranslate READ isUseOriginTranslate WRITE setUseOriginTranstale FINAL)
    Q_PROPERTY(KxMd5Animation *animation READ animation WRITE setAnimation NOTIFY animationChanged FINAL)
    Q_PROPERTY(bool loopAnimating READ isLoopAnimating WRITE setLoopAnimating FINAL)
    Q_PROPERTY(bool animating READ isAnimating WRITE setAnimating FINAL)
    Q_PROPERTY(int frame READ frame NOTIFY frameChanged FINAL)

public:
    explicit KxMd5Model(QObject *parent = 0);
    ~KxMd5Model();

    int jointCount() const;

    virtual void update(int ms);

    virtual bool loadFromFile(const QString& fileName);

    bool isUseOriginTranslate() const;
    void setUseOriginTranstale(bool value);

    //first joint group
    KxMd5Animation *animation() const;
    void setAnimation(KxMd5Animation *value);

    bool isLoopAnimating() const;
    void setLoopAnimating(bool value);

    bool isAnimating() const;
    void setAnimating(bool value);

    int frame() const;

    virtual int nodeType() const { return DrawableNode; }

signals:
    void originDeltaChanged(const QVector3D& deltaPosition);    //HACK
    void originChanged(const QVector3D& position);

    void animationFinished(KxMd5Animation *animation);
    void animationChanged();

    void frameChanged(int newFrame);

private slots:
    void emitFrameChanged(int newFrame);
    void emitAnimationFinished(KxMd5Animation *animation);
    void emitAnimationChanged();

private:
    bool loadMd5File(const QString &fileName);

    QVector<int> m_jointParentIds;
    QStringList m_jointNames;
    QVector<KxTransform> m_joints;
    KxTransform *m_nextFrameJoints; //TODO QVector<KxTransform>
    KxTransform *m_prevFrameJoints; //TODO QVector<KxTransform>
    int m_frameTime;
    int m_currFrame;
    int m_nextFrame;
    qint8 m_deltaFrames;
    qreal m_frameFactor; // <0.0, 1.0>
    KxMd5Animation *m_animation;
    bool m_animating : 1;
    bool m_loopAnimating : 1;
    bool m_useOriginTranslate : 1;

    friend class KxMd5ModelMesh;
    friend class KxMd5JointGroup;
    friend class KxMd5Skeleton;
};

QML_DECLARE_TYPE(KxMd5Model);



#endif // KXMD5MODEL_H
