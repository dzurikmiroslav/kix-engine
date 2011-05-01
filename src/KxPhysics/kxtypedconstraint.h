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

#ifndef KXTYPEDCONSTRAINT_H
#define KXTYPEDCONSTRAINT_H

#include <QtCore/qobject.h>
#include <QtDeclarative/qdeclarative.h>
#include "kxrigidbody.h"

class btTypedConstraint;

class KxTypedConstraint : public QObject
{
    Q_OBJECT
    Q_PROPERTY(KxRigidBody *aBody READ aBody FINAL)
    Q_PROPERTY(KxRigidBody *bBody READ bBody FINAL)

public:
    explicit KxTypedConstraint(QObject *parent = 0);

    virtual KxRigidBody *aBody() const = 0;
    virtual KxRigidBody *bBody() const = 0;

signals:
    void positionsChanged();    //TODO
    void beforeDestroy(KxTypedConstraint *constraint);

protected:
    virtual btTypedConstraint *internalBtConstraint() const = 0;
    virtual inline void emitPosotions();

    friend class KxPhysicsWorld;
};

QML_DECLARE_TYPE(KxTypedConstraint);

inline void KxTypedConstraint::emitPosotions()
{
    emit positionsChanged();
}


#endif // KXTYPEDCONSTRAINT_H
