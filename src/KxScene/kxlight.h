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

#ifndef KXLIGHT_H
#define KXLIGHT_H

#include <QtDeclarative/qdeclarative.h>
#include <QtGui/qcolor.h>
#include "kxscenenode.h"

class KxLight : public KxSceneNode
{
    Q_OBJECT
    Q_PROPERTY(QColor ambient READ ambient WRITE setAmbient NOTIFY lightChanged FINAL)
    Q_PROPERTY(QColor diffuse READ diffuse WRITE setDiffuse NOTIFY lightChanged FINAL)
    Q_PROPERTY(QColor specular READ specular WRITE setSpecular NOTIFY lightChanged FINAL)
    Q_PROPERTY(QVector3D spotDirection READ spotDirection WRITE setSpotDirection NOTIFY lightChanged FINAL)
    Q_PROPERTY(qreal spotExponent READ spotExponent WRITE setSpotExponent NOTIFY lightChanged FINAL)
    Q_PROPERTY(qreal spotCutoff READ spotCutoff WRITE setSpotCutoff NOTIFY lightChanged FINAL)
    Q_PROPERTY(qreal constantAttenuation READ constantAttenuation WRITE setConstantAttenuation NOTIFY lightChanged FINAL)
    Q_PROPERTY(qreal linearAttenuation READ linearAttenuation WRITE setLinearAttenuation NOTIFY lightChanged FINAL)
    Q_PROPERTY(qreal quadraticAttenuation READ quadraticAttenuation WRITE setQuadraticAttenuation NOTIFY lightChanged FINAL)
    Q_PROPERTY(bool directional READ isDirectional WRITE setDirectional NOTIFY lightChanged FINAL)

public:
    explicit KxLight(QObject *parent = 0);
    ~KxLight();

    inline const QColor& ambient() const;
    inline void setAmbient(const QColor& value);

    inline const QColor& diffuse() const;
    inline void setDiffuse(const QColor& value);

    inline const QColor& specular() const;
    inline void setSpecular(const QColor& value);

    inline const QVector3D& spotDirection() const;
    Q_SLOT inline void setSpotDirection(const QVector3D& value);

    QVector3D absoluteSpotDirection() const;

    inline qreal spotExponent() const;
    inline void setSpotExponent(qreal value);

    inline qreal spotCutoff() const;
    inline void setSpotCutoff(qreal value);

    inline qreal constantAttenuation() const;
    inline void setConstantAttenuation(qreal value);

    inline qreal linearAttenuation() const;
    inline void setLinearAttenuation(qreal value);

    inline qreal quadraticAttenuation() const;
    inline void setQuadraticAttenuation(qreal value);

    inline bool isDirectional() const;
    inline void setDirectional(bool enable);

    virtual int nodeType() const { return LightNode; }

signals:
    void lightChanged();
    void sceneChanged();

private:
    QColor m_ambient;
    QColor m_diffuse;
    QColor m_specular;
    QVector3D m_spotDirection;
    bool m_directional : 1;
    float m_spotExponent;
    float m_spotCutoff;
    float m_constantAttenuation;
    float m_linearAttenuation;
    float m_quadraticAttenuation;

};

QML_DECLARE_TYPE(KxLight);


inline bool KxLight::isDirectional() const
{
    return m_directional;
}

inline void KxLight::setDirectional(bool enable)
{
    m_directional = enable;
}

inline const QColor& KxLight::ambient() const
{
    return m_ambient;
}

inline const QColor& KxLight::diffuse() const
{
    return m_diffuse;
}

inline const QColor& KxLight::specular() const
{
    return m_specular;
}

inline const QVector3D& KxLight::spotDirection() const
{
    return m_spotDirection;
}

inline qreal KxLight::spotExponent() const
{
    return m_spotExponent;
}

inline qreal KxLight::spotCutoff() const
{
    return m_spotCutoff;
}

inline qreal KxLight::constantAttenuation() const
{
    return m_constantAttenuation;
}

inline qreal KxLight::linearAttenuation() const
{
    return m_linearAttenuation;
}

inline qreal KxLight::quadraticAttenuation() const
{
    return m_quadraticAttenuation;
}

inline void KxLight::setAmbient(const QColor& value)
{
    m_ambient = value;
    emit lightChanged();
}

inline void KxLight::setDiffuse(const QColor& value)
{
    m_diffuse = value;
    emit lightChanged();
}

inline void KxLight::setSpecular(const QColor& value)
{
    m_specular = value;
    emit lightChanged();
}

inline void KxLight::setSpotDirection(const QVector3D& value)
{
    m_spotDirection = value;
    emit lightChanged();
}

inline void KxLight::setSpotExponent(qreal value)
{
    m_spotExponent = value;
    emit lightChanged();
}

inline void KxLight::setSpotCutoff(qreal value)
{
    m_spotCutoff = value;
    emit lightChanged();
}

inline void KxLight::setConstantAttenuation(qreal value)
{
    m_constantAttenuation = value;
    emit lightChanged();
}

inline void KxLight::setLinearAttenuation(qreal value)
{
    m_linearAttenuation = value;
    emit lightChanged();
}

inline void KxLight::setQuadraticAttenuation(qreal value)
{
    m_quadraticAttenuation = value;
    emit lightChanged();
}


#endif // KXLIGHT_H
