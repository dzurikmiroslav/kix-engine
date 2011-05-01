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

#ifndef KXSCENENODECON_H
#define KXSCENENODECON_H

#include <QtCore/qobject.h>
#include <QtGui/qquaternion.h>
#include <QtGui/qvector3d.h>
#include <QtDeclarative/qdeclarative.h>
#include <QtDeclarative/qdeclarativelist.h>

class KxSceneNode;

class KxSceneNodeCon : public QObject
{
    Q_OBJECT
    Q_PROPERTY(KxSceneNode *parentNode READ parentNode WRITE setParentNode FINAL);
    Q_PROPERTY(QDeclarativeListProperty<KxSceneNodeCon> childrenNodes READ qmlChildrenNodes NOTIFY childrenNodesChanged FINAL);
    Q_PROPERTY(bool visible READ isVisible WRITE setVisible FINAL);
    Q_PROPERTY(QVector3D position READ position WRITE setPosition FINAL);
    Q_PROPERTY(QQuaternion rotation READ rotation WRITE setRotation FINAL);
    Q_PROPERTY(QVector3D localPosition READ localPosition WRITE setLocalPosition FINAL);
    Q_PROPERTY(QQuaternion localRotation READ localRotation WRITE setLocalRotation FINAL);
    Q_PROPERTY(QVector3D scale READ scale WRITE setScale FINAL);

public:
    explicit KxSceneNodeCon(QObject *parent = 0);

    inline KxSceneNode *parentNode() const;

    inline const QVector3D& position() const;
    inline const QQuaternion& rotation() const;
    inline const QVector3D& localPosition() const;
    inline const QQuaternion& localRotation() const;
    inline const QVector3D& scale();
    inline bool isVisible() const;

    inline void setParentNode(KxSceneNode *value);
    inline void setScale(const QVector3D& value);

    inline void setVisible(bool value);
    inline void setPosition(const QVector3D& value);
    inline void setRotation(const QQuaternion& value);
    inline void setLocalPosition(const QVector3D& value);
    inline void setLocalRotation(const QQuaternion& value);

    virtual KxSceneNode *create(QObject *parent = 0) const;

    Q_INVOKABLE QVariant create(const QVariant& parent) const;

signals:
    void childrenNodesChanged();

protected:
    inline QDeclarativeListProperty<KxSceneNodeCon> qmlChildrenNodes();

    bool m_visible : 1;
    KxSceneNode *m_parentNode;
    QVector3D m_position;
    QQuaternion m_rotation;
    QVector3D m_localPosition;
    QQuaternion m_localRotation;
    QVector3D m_scale;
    QList<KxSceneNodeCon *> m_childrenNodes;

};

QML_DECLARE_TYPE(KxSceneNodeCon);

inline QDeclarativeListProperty<KxSceneNodeCon> KxSceneNodeCon::qmlChildrenNodes()
{
    return QDeclarativeListProperty<KxSceneNodeCon>(this, m_childrenNodes);
}

inline KxSceneNode *KxSceneNodeCon::parentNode() const
{
    return m_parentNode;
}

inline void KxSceneNodeCon::setParentNode(KxSceneNode *value)
{
    m_parentNode = value;
}

inline bool KxSceneNodeCon::isVisible() const
{
    return m_visible;
}

inline void KxSceneNodeCon::setVisible(bool hide)
{
    m_visible = hide;
}

inline const QVector3D& KxSceneNodeCon::position() const
{
    return m_position;
}

inline const QQuaternion& KxSceneNodeCon::rotation() const
{
    return m_rotation;
}

inline const QQuaternion& KxSceneNodeCon::localRotation() const
{
    return m_localRotation;
}

inline const QVector3D& KxSceneNodeCon::localPosition() const
{
    return m_localPosition;
}

inline const QVector3D& KxSceneNodeCon::scale()
{
    return m_scale;
}

inline void KxSceneNodeCon::setPosition(const QVector3D& position)
{
    m_position = position;
}

inline void KxSceneNodeCon::setRotation(const QQuaternion &rotation)
{
    m_rotation = rotation;
}

inline void KxSceneNodeCon::setLocalPosition(const QVector3D &value)
{
    m_localPosition = value;
}

inline void KxSceneNodeCon::setLocalRotation(const QQuaternion &value)
{
    m_localRotation = value;
}

inline void KxSceneNodeCon::setScale(const QVector3D& scale)
{
    m_scale = scale;
}



#endif // KXSCENENODECON_H
