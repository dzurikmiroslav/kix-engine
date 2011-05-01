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

#include "kxcompoundshape.h"
#include "kxbulletutil.h"
#include "kxphysicsworld.h"
/*
KxCompoundShape::KxCompoundShape(KxPhysicsWorld *world) :
    KxCollisionShape(world)
{
}

KxCompoundShape::~KxCompoundShape()
{
}

void KxCompoundShape::addChildShape(const QMatrix4x4 &localTranform, KxCollisionShape *_shape)
{
   btCompoundShape* conpoutudShape(static_cast<btCompoundShape*>(shape));
   KxPhysicsWorld *world(static_cast<KxPhysicsWorld*>(parent()));
   conpoutudShape->addChildShape(KxBulletUtil::convert(localTranform, world->scale), _shape->shape);
}

void KxCompoundShape::removeChildShape(KxCollisionShape *_shape)
{
    btCompoundShape* conpoutudShape(static_cast<btCompoundShape*>(shape));
    conpoutudShape->removeChildShape(_shape->shape);
}

int KxCompoundShape::getNumChildShapes() const
{
    btCompoundShape* conpoutudShape(static_cast<btCompoundShape*>(shape));
    return conpoutudShape->getNumChildShapes();
}
*/
