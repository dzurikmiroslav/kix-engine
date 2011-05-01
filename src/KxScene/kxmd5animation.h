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

#ifndef KXMD5ANIMATION_H
#define KXMD5ANIMATION_H

#include <QtDeclarative/qdeclarative.h>
#include <QtGui/qquaternion.h>
#include <QtCore/qvector.h>
#include "kxmath.h"

class KxMd5Animation : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int framesCount READ framesCount CONSTANT FINAL)
    Q_PROPERTY(int frameRate READ frameRate WRITE setFrameRate FINAL)
    Q_PROPERTY(QString source READ source WRITE setSource FINAL)

public:
    KxMd5Animation(QObject *parent = 0);
    KxMd5Animation(const QString& fileName, QObject *parent = 0);
    ~KxMd5Animation();

    inline int framesCount() const;
    inline int frameRate() const;//frames per second
    inline int frameTime() const; //frame length (ms)
    inline void setFrameRate(int rate);
    inline const QString& source() const;
    void setSource(const QString& value);
    bool loadFromFile(const QString& fileName);

private:
    struct Frame
    {
        QVector<KxTransform> m_joints;
        KxAABB m_aabb;
    };
    bool loadMd5File(const QString& fileName);
    static void computeQuatScallar(QQuaternion &quat);
    int m_frameRate;
    int m_jointCount;
    QVector<Frame> m_frames;
    QString m_source;

    friend class KxMd5Model;
    friend class KxMd5Skeleton;
    friend class KxMd5JointGroup;
};

QML_DECLARE_TYPE(KxMd5Animation);


inline const QString& KxMd5Animation::source() const
{
    return m_source;
}

inline int KxMd5Animation::framesCount() const
{
    return m_frames.count();
}

inline int KxMd5Animation::frameTime() const
{
    return 1000.0f / m_frameRate ;
}

inline int KxMd5Animation::frameRate() const
{
    return m_frameRate;
}

inline void KxMd5Animation::setFrameRate(int rate)
{
    m_frameRate = rate;
}

#endif // KXMD5ANIMATION_H
