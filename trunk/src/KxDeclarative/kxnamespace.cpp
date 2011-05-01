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

#include "kxnamespace.h"
#include "KxEntity/kxentity.h"
#include <QtCore/qdebug.h>
#include <QtCore/qfile.h>
#include <QtCore/qmath.h>
#include <QtDeclarative/qdeclarativecomponent.h>
#include <QtCore/qcoreapplication.h>
#include "kxdeclarative.h"

KxNamespace::KxNamespace(QObject *parent) :
    QObject(parent)
{
}

KxEngine *KxNamespace::engine()
{
    return KxEngine::instance();
}

KxMaterial *KxNamespace::loadMaterial(const QString &fileName, QObject *parent) const
{
    return kxDeclarative->loadMaterial(fileName, parent);
}

QVector3D KxNamespace::directionFromAE(qreal azimut, qreal elevation) const
{
    QVector3D direction;
    azimut *= M_PI / 180;
    elevation *= M_PI / 180;
    qreal cosAzimut = qCos(azimut);
    qreal sinAzimut = qSin(azimut);
    qreal cosElevat = qCos(elevation);
    qreal sinElevat = qSin(elevation);
    direction.setX(cosAzimut * cosElevat);
    direction.setY(sinElevat * qSqrt(qPow(cosAzimut, 2) + qPow(sinAzimut, 2)));
    direction.setZ(sinAzimut * cosElevat);
    return direction;
}

QString KxNamespace::readFile(const QString &fileLoc) const
{
    QString ret;
    QFile f(fileLoc);
    if(f.open(QIODevice::ReadOnly)) {
        ret = f.readAll();
        f.close();
    }
    return ret;
}

QUrl KxNamespace::dataPath() const
{
    return kxEngine->settings()["path"].toUrl();
}
