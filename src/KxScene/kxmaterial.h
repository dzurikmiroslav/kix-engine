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

#ifndef KXMATERIAL_H
#define KXMATERIAL_H

#include <QtOpenGL/qglshaderprogram.h>
#include <QtDeclarative/qdeclarative.h>
#include <QtDeclarative/qdeclarativelist.h>
#include <QtCore/qmutex.h>
#include <QtGui/qcolor.h>

class KxScene;
class KxCamera;
class KxSceneNode;

#include "qdeclarativeproperty.h"

class KxMaterial : public QObject, public QDeclarativeParserStatus, public QDeclarativePropertyValueInterceptor
{
    Q_OBJECT
    Q_PROPERTY(bool sorting READ isSorting WRITE setSorting FINAL)
    Q_PROPERTY(int blendDstFactor READ blendDstFactor WRITE setBlendDstFactor FINAL)
    Q_PROPERTY(int blendSrcFactor READ blendSrcFactor WRITE setBlendSrcFactor FINAL)
    Q_PROPERTY(QString vertexShaderSource READ vertexShaderSource WRITE setVertexShaderSource FINAL)
    Q_PROPERTY(QString fragmentShaderSource READ fragmentShaderSource WRITE setFragmentShaderSource FINAL)
    Q_INTERFACES(QDeclarativePropertyValueInterceptor QDeclarativeParserStatus)

public:
    enum MaxLightsCounts {
        MaxLightsCount = 8
    };
    explicit KxMaterial(QObject *parent = 0);
    ~KxMaterial();

    bool init();    //need call before first bind
    void bind(KxCamera *camera, KxSceneNode *node);
    void release();

    inline bool isSorting() const;
    inline void setSorting(bool value);

    inline GLenum blendSrcFactor() const;
    inline void setBlendSrcFactor(GLenum value);

    inline GLenum blendDstFactor() const;
    inline void setBlendDstFactor(GLenum value);

    QString vertexShaderSource() const;
    void setVertexShaderSource(const QString& value);

    QString fragmentShaderSource() const;
    void setFragmentShaderSource(const QString& value);

    //TODO
    //QString geometryShaderSource() const;
    //void setGeometryShaderSource(const QString& value);

    virtual void classBegin();
    virtual void componentComplete();

    virtual void setTarget(const QDeclarativeProperty &property)
    {
        qDebug() << this << "setTarget  " << property.name() << property.read();
    }

    virtual void write(const QVariant &value)
    {
        qDebug() << this << "write  " << value;
    }

private:
    GLuint loadTexture(const QString& fileName);
    void deleteTexture(GLuint texture);

    mutable QMutex m_mutex;
    QGLShaderProgram *m_program;
    QMap<int, int> m_propertyUniforms;
    QMap<int, QImage*> m_textures;
    int m_numLightsLoc;
    int m_mvPrMatrixLoc;
    int m_mvMatrixLoc;
    int m_prMatrixLoc;
    int m_norMatrixLoc;
    GLenum m_blendSrc;
    GLenum m_blendDst;
    bool m_sorting : 1;
    bool m_hasLights : 1;

};

QML_DECLARE_TYPE(KxMaterial);


inline bool KxMaterial::isSorting() const
{
    return m_sorting;
}

inline GLenum KxMaterial::blendDstFactor() const
{
    return m_blendDst;
}

inline GLenum KxMaterial::blendSrcFactor() const
{
    return m_blendSrc;
}

inline void KxMaterial::setBlendDstFactor(GLenum value)
{
    m_blendDst = value;
}

inline void KxMaterial::setBlendSrcFactor(GLenum value)
{
    m_blendSrc = value;
}

inline void KxMaterial::setSorting(bool value)
{
    m_sorting = value;
}

#endif // KXMATERIAL_H
