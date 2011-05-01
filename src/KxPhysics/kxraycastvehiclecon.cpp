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

#include "kxraycastvehiclecon.h"
#include "kxphysicsworld.h"

KxWheelInfoCon::KxWheelInfoCon(QObject *parent) :
        QObject(parent)
{
}

void KxWheelInfoCon::setConnectionPoint(const QVector3D& value)
{
    m_connectionPoint = value;
}

void KxWheelInfoCon::setDirection(const QVector3D& value)
{
    m_direction = value;
}

void KxWheelInfoCon::setAxle(const QVector3D& value)
{
    m_axle = value;
}

void KxWheelInfoCon::setSuspensionRestLength(qreal value)
{
    m_suspensionRestLength = value;
}

void KxWheelInfoCon::setRadius(qreal value)
{
    m_radius = value;
}

void KxWheelInfoCon::setFront(bool enable)
{
    m_front = enable;
}

const QVector3D& KxWheelInfoCon::connectionPoint() const
{
    return m_connectionPoint;
}

const QVector3D& KxWheelInfoCon::direction() const
{
    return m_direction;
}

const QVector3D& KxWheelInfoCon::axle() const
{
    return m_axle;
}

qreal KxWheelInfoCon::suspensionRestLength() const
{
    return m_suspensionRestLength;
}

qreal KxWheelInfoCon::radius() const
{
    return m_radius;
}

bool KxWheelInfoCon::isFront() const
{
    return m_front;
}




KxRaycastVehicleCon::KxRaycastVehicleCon(QObject *parent) :
        KxRigidBodyCon(parent)
{
}

KxRaycastVehicleCon::~KxRaycastVehicleCon()
{
    foreach(KxWheelInfoCon *w, m_wheels)
        delete w;
}

QDeclarativeListProperty<KxWheelInfoCon> KxRaycastVehicleCon::qmlWheels()
{
    return QDeclarativeListProperty<KxWheelInfoCon>(this, m_wheels);
}

KxRaycastVehicle *KxRaycastVehicleCon::create(QObject *parent) const
{
    if(!m_collisionShape) {
        qWarning() << "KxRaycastVehicleCon::create collisionShape is NULL";
        return NULL;
    }
    KxRaycastVehicle *vechile = new KxRaycastVehicle(m_collisionShape, m_mass, parent);
    vechile->setPosition(m_position);
    vechile->setRotation(m_rotation);
    foreach(KxWheelInfoCon *w, m_wheels)
        vechile->addWheel(w->connectionPoint(), w->direction(), w->axle(),
                          w->suspensionRestLength(), w->radius(), w->isFront());
    return vechile;
}
