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

#include "kxentity.h"
#include <qdebug.h>

KxEntity::KxEntity(QObject *parent) :
    QObject(parent)
{
}

KxEntity::~KxEntity()
{
    //qDebug() << "KxEntity::~KxEntity";
}

const QObjectList &KxEntity::elements() const
{
    return m_elements;
}

void KxEntity::addElement(QObject *element)
{
    if (!m_elements.contains(element)) {
        element->setParent(this);
        m_elements << element;
    } else {
        qWarning() << "KxEntity::addElement element alredy added";
    }
}

void KxEntity::removeElement(QObject *element)
{
    if (m_elements.contains(element)) {
        m_elements.removeOne(element);
        element->setParent(NULL);
    } else {
        qWarning() << "KxEntity::removeElement try remove not contaned element";
    }
}

QDeclarativeListProperty<QObject> KxEntity::qmlElements()
{
    return QDeclarativeListProperty<QObject>(this, m_elements);
}
