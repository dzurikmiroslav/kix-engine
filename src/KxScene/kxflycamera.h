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

#ifndef KXFLYCAMERA_H
#define KXFLYCAMERA_H

#include "kxcamera.h"

class KxFlyCamera : public KxCamera
{
    Q_OBJECT
    Q_PROPERTY(qreal speed READ speed WRITE setSpeed FINAL)
    Q_PROPERTY(qreal horizontalSpeed READ horizontalSpeed WRITE setHorizontalSpeed FINAL)
    Q_PROPERTY(qreal verticalSpeed READ verticalSpeed WRITE setVerticalSpeed FINAL)

public:
    explicit KxFlyCamera(QObject *parent = 0);

    virtual void update(int ms);

    qreal speed() const;
    void setSpeed(qreal value);

    qreal horizontalSpeed() const;
    void setHorizontalSpeed(qreal value);

    qreal verticalSpeed() const;
    void setVerticalSpeed(qreal value);

private:
    QVector3D m_speeds;

};

QML_DECLARE_TYPE(KxFlyCamera);


#endif // KXFLYCAMERA_H
