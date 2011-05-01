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

#ifndef KXENTITY_H
#define KXENTITY_H

#include <QtCore/qobject.h>
#include <QtDeclarative/qdeclarative.h>
#include <QtDeclarative/qdeclarativelist.h>

class KxEntity : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QObject *parent READ parent WRITE setParent FINAL)
    Q_PROPERTY(QDeclarativeListProperty<QObject> elements READ qmlElements FINAL)
    Q_CLASSINFO("DefaultProperty", "elements")

public:
    explicit KxEntity(QObject *parent = 0);
    ~KxEntity();

    const QObjectList &elements() const;
    void addElement(QObject *element);
    void removeElement(QObject *element);

private:
    QDeclarativeListProperty<QObject> qmlElements();

    QList<QObject *> m_elements;

};

QML_DECLARE_TYPE(KxEntity);


#endif // KXENTITY_H
