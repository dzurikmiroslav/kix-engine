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

#ifndef KXDECLARATIVE_H
#define KXDECLARATIVE_H

#include <QtDeclarative/qdeclarative.h>
#include <QtDeclarative/qdeclarativecontext.h>
#include <QtDeclarative/qdeclarativeengine.h>
#include <QtDeclarative/qdeclarativecomponent.h>

class KxMaterial;
class KxEntity;

class KxDeclarative : public QObject
{

public:
    explicit KxDeclarative(QObject *parent = 0);
    ~KxDeclarative();

    inline QDeclarativeEngine *declarativeEngine() const;

    KxMaterial *loadMaterial(const QString &fileName, QObject *parent = 0) const;

    KxEntity *loadEntity(const QString &fileName, QObject *parent = 0) const;

    static KxDeclarative *instance();

private:
    void registerTypes();

    QDeclarativeEngine *m_engine;

};

#define kxDeclarative KxDeclarative::instance()

inline QDeclarativeEngine *KxDeclarative::declarativeEngine() const
{
    return m_engine;
}

#endif // KXDECLARATIVE_H
