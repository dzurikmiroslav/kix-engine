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

#include "kxflycamera.h"

KxFlyCamera::KxFlyCamera(QObject *parent) :
    KxCamera(parent)
{
}

void KxFlyCamera::update(int ms)
{
    m_mutex.lock();
    if (!m_speeds.isNull()) {
        QVector3D direction = m_center - m_position;
        QVector3D delta = m_speeds * (qreal)ms * (qreal)0.001;
        direction.normalize();
        if (m_speeds.z()) {
            m_position += direction * delta.z();
            m_center += direction * delta.z();
        }
        if (m_speeds.x()) {
            QVector3D hDirection = direction;
            hDirection.setY(0);
            hDirection.normalize();
            hDirection = QVector3D::crossProduct(hDirection, QVector3D(0, 1, 0));
            m_position += hDirection * delta.x();
            m_center += hDirection * delta.x();
        }
        if (m_speeds.y()) {
            m_position += m_up * delta.y();
            m_center += m_up * delta.y();
        }
    }
    m_mutex.unlock();
    m_rootNode->update(ms);
}

qreal KxFlyCamera::speed() const
{
    return m_speeds.z();
}

qreal KxFlyCamera::horizontalSpeed() const
{
    return m_speeds.x();
}

qreal KxFlyCamera::verticalSpeed() const
{
    return m_speeds.y();
}

void KxFlyCamera::setSpeed(qreal speed)
{
    m_speeds.setZ(speed);
}

void KxFlyCamera::setHorizontalSpeed(qreal speed)
{
    m_speeds.setX(speed);
}

void KxFlyCamera::setVerticalSpeed(qreal speed)
{
    m_speeds.setY(speed);
}
