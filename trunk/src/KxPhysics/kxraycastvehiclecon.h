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

#ifndef KXRAYCASTVEHICLECON_H
#define KXRAYCASTVEHICLECON_H

#include "kxrigidbodycon.h"

class KxRaycastVehicle;

class KxWheelInfoCon : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVector3D connectionPoint READ connectionPoint WRITE setConnectionPoint NOTIFY wheelChanged FINAL);
    Q_PROPERTY(QVector3D direction READ direction WRITE setDirection NOTIFY wheelChanged FINAL);
    Q_PROPERTY(QVector3D axle READ axle WRITE setAxle NOTIFY wheelChanged FINAL);
    Q_PROPERTY(qreal suspensionRestLength READ suspensionRestLength WRITE setSuspensionRestLength NOTIFY wheelChanged FINAL);
    Q_PROPERTY(qreal radius READ radius WRITE setRadius NOTIFY wheelChanged FINAL);
    Q_PROPERTY(bool front READ isFront WRITE setFront NOTIFY wheelChanged FINAL);

public:
    explicit KxWheelInfoCon(QObject *parent = 0);

    void setConnectionPoint(const QVector3D& value);
    void setDirection(const QVector3D& value);
    void setAxle(const QVector3D& value);
    void setSuspensionRestLength(qreal value);
    void setRadius(qreal value);
    void setFront(bool enable);

    const QVector3D& connectionPoint() const;
    const QVector3D& direction() const;
    const QVector3D& axle() const;
    qreal suspensionRestLength() const;
    qreal radius() const;
    bool isFront() const;

signals:
    void wheelChanged();

private:
    QVector3D m_connectionPoint;
    QVector3D m_direction;
    QVector3D m_axle;
    qreal m_suspensionRestLength;
    qreal m_radius;
    bool m_front : 1;

};

QML_DECLARE_TYPE(KxWheelInfoCon);


class KxRaycastVehicleCon : public KxRigidBodyCon
{
    Q_OBJECT
    Q_PROPERTY(QDeclarativeListProperty<KxWheelInfoCon> wheels READ qmlWheels FINAL);

public:
    explicit KxRaycastVehicleCon(QObject *parent = 0);
    ~KxRaycastVehicleCon();
    QDeclarativeListProperty<KxWheelInfoCon> qmlWheels();
    Q_INVOKABLE KxRaycastVehicle *create(QObject *parent = 0) const;

private:
    QList<KxWheelInfoCon*> m_wheels;

};

QML_DECLARE_TYPE(KxRaycastVehicleCon);

#endif // KXRAYCASTVEHICLECON_H
