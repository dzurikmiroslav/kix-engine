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

#include "kxthirdpersoncamera.h"
#include "QtCore/qmath.h"

KxThirdPersonCamera::KxThirdPersonCamera(QObject *parent) :
    KxCamera(parent)
{
    m_collisionMask = 0;
}

void KxThirdPersonCamera::computeModelViewMatrix(QMatrix4x4 &matrix)
{
    if(m_preferDirection.isNull()) {
        if(m_maxDistance) {
            QVector3D dir = m_position - m_center;
            if(qAbs(dir.length()) > m_maxDistance) {
                dir.normalize();
                m_position = m_center + dir * m_maxDistance;
            }
        }
    } else {
        m_position = m_center - (m_preferDirection * m_maxDistance);
    }
    matrix.setToIdentity();
    matrix.lookAt(m_position + QVector3D(0, m_yEyeOffset, 0), m_center + QVector3D(0, m_yCenterOffset, 0), m_up);
}

void KxThirdPersonCamera::emitRotationAroundYChanged()
{
    QVector2D dir = QVector2D(-direction().z(), direction().x()).normalized();
    qreal angle;
    if ((dir.x() >= 0) && (dir.y() >= 0))
        angle = qAsin(dir.x());
    else if ((dir.x() >= 0) && (dir.y() <= 0))
        angle = qAcos(dir.y());
    else if ((dir.x() <= 0) && (dir.y() <= 0))
        angle = M_PI - qAsin(dir.x());
    else
        angle = 2 * M_PI - qAcos(dir.y());
    QQuaternion q = QQuaternion::fromAxisAndAngle(0, 1, 0, angle * 180 / M_PI);
    emit rotationAroundYChanged(q * m_rotationAroundYOffset);
}

void KxThirdPersonCamera::orbitRotate(const QVector2D &delta)
{
    m_mutex.lock();
    QVector3D outDirection = m_position - m_center;
    qreal distance = outDirection.length();
    outDirection.normalize();
    QMatrix4x4 rot;
    rot.rotate(delta.x(), 0, 1, 0);
    QVector3D  yPlaneDir = direction();
    yPlaneDir.setY(0);
    yPlaneDir.normalize();
    rot.rotate(delta.y(), -yPlaneDir.z(), 0, yPlaneDir.x());
    rot.optimize();
    outDirection = rot * outDirection;
    if(outDirection.y() > 0.999) {
        outDirection.setY(0.999);
        outDirection.normalize();
    } else if(outDirection.y() < -0.999) {
        outDirection.setY(-0.999);
        outDirection.normalize();
    }
    m_position = outDirection * distance + m_center;
    emit directionArroundYChanged(yPlaneDir);
    emitRotationAroundYChanged();
    m_mutex.unlock();
    emit eyeChanged(m_position);
    emit centerChanged(m_center);
}

qreal KxThirdPersonCamera::yCenterOffset() const
{
    return m_yCenterOffset;
}

qreal KxThirdPersonCamera::yEyeOffset() const
{
    return m_yEyeOffset;
}

const QQuaternion& KxThirdPersonCamera::rotationAroundYOffset() const
{
    return m_rotationAroundYOffset;
}

const QVector3D& KxThirdPersonCamera::preferDirection() const
{
    return m_preferDirection;
}

qreal KxThirdPersonCamera::maxDistance() const
{
    return m_maxDistance;
}

void KxThirdPersonCamera::setMaxDistance(qreal value)
{
    m_mutex.lock();
    m_maxDistance = value;
    if(!m_preferDirection.isNull()) {
        m_position = m_center - (m_preferDirection * m_maxDistance);
        m_mutex.unlock();
        emit eyeChanged(m_position);
    }
    else
        m_mutex.unlock();
}

void KxThirdPersonCamera::setRotationAroundYOffset(const QQuaternion &value)
{
    m_rotationAroundYOffset = value;
}

void KxThirdPersonCamera::setYEyeOffset(qreal value)
{
    m_yEyeOffset = value;
}

void KxThirdPersonCamera::setYCenterOffset(qreal value)
{
    m_yCenterOffset = value;
}

void KxThirdPersonCamera::setCenter(const QVector3D &value)
{
    m_mutex.lock();
    m_center = value;
    if(!m_preferDirection.isNull()) {
        m_position = m_center - (m_preferDirection * m_maxDistance);
        m_mutex.unlock();
        emit eyeChanged(m_position);
    }
    else
        m_mutex.unlock();
    emit centerChanged(m_center);
}

void KxThirdPersonCamera::setPreferDirection(const QVector3D &value)
{
    m_mutex.lock();
    m_preferDirection = value;
    m_position = m_center - (m_preferDirection * m_maxDistance);
    m_mutex.unlock();
    emit eyeChanged(m_position);
}
