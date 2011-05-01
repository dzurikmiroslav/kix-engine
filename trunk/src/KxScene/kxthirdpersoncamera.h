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

#ifndef KXTHIRDPERSONCAMERA_H
#define KXTHIRDPERSONCAMERA_H

#include "kxcamera.h"

class KxThirdPersonCamera : public KxCamera
{
    Q_OBJECT
    Q_PROPERTY(qreal maxDistance READ maxDistance WRITE setMaxDistance FINAL)
    Q_PROPERTY(QQuaternion rotationAroundYOffset READ rotationAroundYOffset WRITE setRotationAroundYOffset FINAL)
    Q_PROPERTY(qreal yCenterOffset READ yCenterOffset WRITE setYCenterOffset FINAL)
    Q_PROPERTY(qreal yEyeOffset READ yEyeOffset WRITE setYEyeOffset FINAL)
    Q_PROPERTY(QVector3D preferDirection READ preferDirection WRITE setPreferDirection FINAL)

public:
    explicit KxThirdPersonCamera(QObject *parent = 0);

    qreal maxDistance() const;
    const QQuaternion& rotationAroundYOffset() const;
    qreal yCenterOffset() const;
    qreal yEyeOffset() const;
    const QVector3D& preferDirection() const;

    void setMaxDistance(qreal value);
    void setRotationAroundYOffset(const QQuaternion &value);
    void setYCenterOffset(qreal value);
    void setYEyeOffset(qreal value);
    void setPreferDirection(const QVector3D& value);

signals:
    void rotationAroundYChanged(const QQuaternion &rotation);

public slots:
    void orbitRotate(const QVector2D &delta);   //3rd person
    virtual void setCenter(const QVector3D& center);

protected:
    void emitRotationAroundYChanged();
    virtual void computeModelViewMatrix(QMatrix4x4 &matrix);

    QVector3D m_preferDirection;
    qreal m_maxDistance;
    bool m_collision : 1;
    short m_collisionMask;  //ak koliduje s fyz. obj.
    QQuaternion m_rotationAroundYOffset;
    qreal m_yCenterOffset;
    qreal m_yEyeOffset;

};

QML_DECLARE_TYPE(KxThirdPersonCamera);


#endif // KXTHIRDPERSONCAMERA_H
