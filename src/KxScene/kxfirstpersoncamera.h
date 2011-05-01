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

#ifndef KXFIRSTPERSONCAMERA_H
#define KXFIRSTPERSONCAMERA_H

#include "kxcamera.h"

//TODO
class KxFirstPersonCamera : public KxCamera
{
    Q_OBJECT
public:
    explicit KxFirstPersonCamera(QWidget *parent = 0);

signals:

public slots:



};

#endif // KXFIRSTPERSONCAMERA_H
