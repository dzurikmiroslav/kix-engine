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

#ifndef KXCOMPOUNDSHAPE_H
#define KXCOMPOUNDSHAPE_H

#include "kxcollisionshape.h"
#include <QMatrix4x4>

//TODO

/*
class KxCompoundShape : public KxCollisionShape
{
    Q_OBJECT
    Q_PROPERTY(int numChildSpaces READ getNumChildShapes)

public:
    explicit KxCompoundShape(KxPhysicsWorld *world);
    ~KxCompoundShape();
    static QScriptValue toScriptValue(QScriptEngine *engine, KxCollisionShape* const &in);
    static void fromScriptValue(const QScriptValue &object, KxCollisionShape* &out);

public slots:
    void addChildShape(const QMatrix4x4& localTranform, KxCollisionShape *shape);
    void removeChildShape(KxCollisionShape *shape);
    int getNumChildShapes() const;

};
*/
#endif // KXCOMPOUNDSHAPE_H
