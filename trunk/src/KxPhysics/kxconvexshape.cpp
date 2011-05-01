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

#include "kxconvexshape.h"
#include "kxbulletutil.h"
#include <QtCore/qfile.h>
#include <QtCore/qregexp.h>

KxConvexShape::KxConvexShape(QObject *parent) :
    KxCollisionShape(parent)
{
}

/*box*/

KxBoxShape::KxBoxShape(const QVector3D &halfExteds, QObject *parent) :
    KxConvexShape(parent)
{
    m_shape = new btBoxShape(KxBulletUtil::convertScaled(halfExteds));
    m_shape->setUserPointer(this);
}

KxBoxShape::~KxBoxShape()
{
    delete m_shape;
}

QVector3D KxBoxShape::halfExtentsWithMargin() const
{
    return KxBulletUtil::convertScaled(m_shape->getHalfExtentsWithMargin());
}

QVector3D KxBoxShape::halfExtentsWithoutMargin() const
{
    return KxBulletUtil::convertScaled(m_shape->getHalfExtentsWithoutMargin());
}

btCollisionShape* KxBoxShape::internalBtShape() const
{
    return m_shape;
}

btConvexShape* KxBoxShape::internalConvexShape() const
{
    return m_shape;
}

/* sphere */

KxSphereShape::KxSphereShape(qreal radius, QObject *parent) :
    KxConvexShape(parent)
{
    m_shape = new btSphereShape(radius * KxBulletUtil::scale());
    m_shape->setUserPointer(this);
}

KxSphereShape::~KxSphereShape()
{
    delete m_shape;
}

qreal KxSphereShape::radius() const
{
    return m_shape->getRadius() * KxBulletUtil::oneOverScale();
}

btCollisionShape* KxSphereShape::internalBtShape() const
{
    return m_shape;
}

btConvexShape* KxSphereShape::internalConvexShape() const
{
    return m_shape;
}

/* capsule */

KxCapsuleShape::KxCapsuleShape(qreal radius, qreal height, int upAxis, QObject *parent) :
    KxConvexShape(parent)
{
    switch(upAxis) {
    case Kx::X:
        m_shape = new btCapsuleShapeX(radius * KxBulletUtil::scale(), height * KxBulletUtil::scale());
        break;
    case Kx::Z:
        m_shape = new btCapsuleShapeZ(radius * KxBulletUtil::scale(), height * KxBulletUtil::scale());
        break;
    default:
        m_shape = new btCapsuleShape(radius * KxBulletUtil::scale(), height * KxBulletUtil::scale());
    }
    m_shape->setUserPointer(this);
}

KxCapsuleShape::~KxCapsuleShape()
{
    delete m_shape;
}

qreal KxCapsuleShape::halfHeight() const
{
    return m_shape->getHalfHeight() * KxBulletUtil::oneOverScale();
}

qreal KxCapsuleShape::radius() const
{
    return m_shape->getRadius() * KxBulletUtil::oneOverScale();
}

btCollisionShape* KxCapsuleShape::internalBtShape() const
{
    return m_shape;
}

btConvexShape* KxCapsuleShape::internalConvexShape() const
{
    return m_shape;
}

/* cylinder */

KxCylinderShape::KxCylinderShape(const QVector3D &halfExtends, int upAxis, QObject *parent) :
    KxConvexShape(parent)
{
    switch(upAxis) {
    case Kx::X:
        m_shape = new btCylinderShapeX(KxBulletUtil::convertScaled(halfExtends));
        break;
    case Kx::Z:
        m_shape = new btCylinderShapeZ(KxBulletUtil::convertScaled(halfExtends));
        break;
    default:
        m_shape = new btCylinderShape(KxBulletUtil::convertScaled(halfExtends));
    }
    m_shape->setUserPointer(this);
}

KxCylinderShape::~KxCylinderShape()
{
    delete m_shape;
}

QVector3D KxCylinderShape::halfExtentsWithMargin() const
{
    return  KxBulletUtil::convertScaled(m_shape->getHalfExtentsWithMargin());
}

QVector3D KxCylinderShape::halfExtentsWithoutMargin() const
{
    return  KxBulletUtil::convertScaled(m_shape->getHalfExtentsWithoutMargin());
}

btCollisionShape* KxCylinderShape::internalBtShape() const
{
    return m_shape;
}

btConvexShape* KxCylinderShape::internalConvexShape() const
{
    return m_shape;
}

/* cone */

KxConeShape::KxConeShape(qreal radius, qreal height, int upAxis, QObject *parent) :
    KxConvexShape(parent)
{
    switch(upAxis) {
    case Kx::X:
        m_shape = new btConeShapeX(radius * KxBulletUtil::scale(), height * KxBulletUtil::scale());
        break;
    case Kx::Z:
        m_shape = new btConeShapeZ(radius * KxBulletUtil::scale(), height * KxBulletUtil::scale());
        break;
    default:
        m_shape = new btConeShape(radius * KxBulletUtil::scale(), height * KxBulletUtil::scale());
    }
    m_shape->setUserPointer(this);
}

KxConeShape::~KxConeShape()
{
    delete m_shape;
}

qreal KxConeShape::height() const
{
    return m_shape->getHeight() * KxBulletUtil::oneOverScale();
}

qreal KxConeShape::radius() const
{
    return m_shape->getRadius() * KxBulletUtil::oneOverScale();
}

btCollisionShape* KxConeShape::internalBtShape() const
{
    return m_shape;
}

btConvexShape* KxConeShape::internalConvexShape() const
{
    return m_shape;
}

/*convex hull*/

KxConvexHullShape::KxConvexHullShape(const QString &fileName, QObject *parent) :
    KxConvexShape(parent)
{
    m_shape = NULL;
    qDebug() << "KxConvexHullShape::KxConvexHullShape" << fileName;
    if (fileName.endsWith(".obj", Qt::CaseInsensitive))
        loadObjFile(fileName);
    else
        qWarning() << "KxConvexHullShape::KxConvexHullShape uknow format addictive";
}

KxConvexHullShape::KxConvexHullShape(KxGeometryData *geometry, QObject *parent) :
    KxConvexShape(parent)
{
#ifdef BT_USE_DOUBLE_PRECISION
    QVector<btVector3> vertices;
    vertices.reserve(geometry->vertices().count());
    foreach (QVector3D v, geometry->vertices())
        vertices << KxBulletUtil::convert(v);
    m_shape = new btConvexHullShape((btScalar*) vertices,
                                    vertices.count(),
                                    sizeof(btVector3));
#else
    m_shape = new btConvexHullShape((btScalar*) geometry->vertices().constData(),
                                    geometry->vertices().count(),
                                    sizeof(QVector3D));
#endif
    m_shape->setLocalScaling(btVector3(KxBulletUtil::scale(), KxBulletUtil::scale(), KxBulletUtil::scale()));
}

void KxConvexHullShape::loadObjFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "KxTriangleMeshShape::loadObjFile cant read file" << fileName;
        return;
    }
    QTextStream stream(&file);
    QRegExp vReg("v\\s+(\\S+)\\s+(\\S+)\\s+(\\S+).*");
    QString line;
    QVector<btVector3> vertices;
    do {
        line = stream.readLine();
        if (vReg.indexIn(line) > -1)
#ifdef BT_USE_DOUBLE_PRECISION
            vertices << btVector3(vReg.cap(1).toDouble(), vReg.cap(2).toDouble(), vReg.cap(3).toDouble());
#else
            vertices << btVector3(vReg.cap(1).toFloat(), vReg.cap(2).toFloat(), vReg.cap(3).toFloat());
#endif
    } while (!line.isNull());
    file.close();
    m_shape = new btConvexHullShape((btScalar*) vertices.constData(), vertices.count(), sizeof(btVector3));
    m_shape->setLocalScaling(btVector3(KxBulletUtil::scale(), KxBulletUtil::scale(), KxBulletUtil::scale()));
}

KxConvexHullShape::~KxConvexHullShape()
{
    if(m_shape)
        delete m_shape;
}

btCollisionShape *KxConvexHullShape::internalBtShape() const
{
    return m_shape;
}

btConvexShape *KxConvexHullShape::internalConvexShape() const
{
    return m_shape;
}
