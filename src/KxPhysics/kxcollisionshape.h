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

#ifndef KXCOLLISIONSHAPE_H
#define KXCOLLISIONSHAPE_H

#include <QtDeclarative/qdeclarative.h>

class btCollisionShape;
class KxPhysicsWorld;

class KxCollisionShape : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QObject *parent READ parent WRITE setParent FINAL)
    Q_PROPERTY(qreal margin READ margin WRITE setMargin FINAL)

public:
    explicit KxCollisionShape(QObject *parent = 0);
    ~KxCollisionShape();

    void setMargin(qreal margin);
    qreal margin() const;

protected:
    virtual btCollisionShape* internalBtShape() const = 0;

    friend class KxPhysicsWorld;
    friend class KxRigidBody;
};

QML_DECLARE_TYPE(KxCollisionShape);

#endif // KXCOLLISIONSHAPE_H
