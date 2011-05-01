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

#include <QtCore/qfile.h>
#include "kxmaterial.h"
#include "kxcamera.h"
#include "kxlight.h"
#include "kxscenenode.h"
#include "KxEngine/kxengine.h"
#include <QtCore/qmath.h>
#include "KxDeclarative/kxdeclarative.h"

#ifdef Q_OS_WIN32
#include <GL/glext.h>
extern PFNGLACTIVETEXTUREPROC glActiveTexture;
#endif
/*
#define VERTEX_SHADER_HEADER \
    "struct kix_LightSourceParameters {\n"\
    "   mediump vec4 ambient;\n"\
    "   mediump vec4 diffuse;\n"\
    "   mediump vec4 specular;\n"\
    "   mediump vec3 position;\n"\
    "   mediump vec3 spotDirection;\n"\
    "   mediump float spotExponent;\n"\
    "   mediump float spotCutoff;\n"\
    "   mediump float spotCosCutoff;\n"\
    "   mediump float constantAttenuation;\n"\
    "   mediump float linearAttenuation;\n"\
    "   mediump float quadraticAttenuation;\n"\
    "   bool directional;\n"\
    "};\n"\
    "const int kix_MaxLights = 8;\n"\
    "uniform kix_LightSourceParameters kix_LightSource[kix_MaxLights];\n"\
    "uniform int kix_NumLights;\n"\
    "uniform highp mat4 kix_ModelViewProjectionMatrix;\n"\
    "uniform highp mat4 kix_ModelViewMatrix;\n"\
    "uniform highp mat3 kix_NormalMatrix;\n"\
    "attribute highp vec4 kix_Vertex;\n"\
    "attribute highp vec3 kix_Normal;\n"\
    "attribute highp vec3 kix_Tangent;\n"\
    "attribute highp vec2 kix_TexCoord;\n"

#define FRAGMENT_SHADER_HEADER \
    "struct kix_LightSourceParameters {\n"\
    "   mediump vec4 ambient;\n"\
    "   mediump vec4 diffuse;\n"\
    "   mediump vec4 specular;\n"\
    "   mediump vec3 position;\n"\
    "   mediump vec3 spotDirection;\n"\
    "   mediump float spotExponent;\n"\
    "   mediump float spotCutoff;\n"\
    "   mediump float spotCosCutoff;\n"\
    "   mediump float constantAttenuation;\n"\
    "   mediump float linearAttenuation;\n"\
    "   mediump float quadraticAttenuation;\n"\
    "   bool directional;\n"\
    "};\n"\
    "const int kix_MaxLights = 8;\n"\
    "uniform kix_LightSourceParameters kix_LightSource[kix_MaxLights];\n"\
    "uniform int kix_NumLights;\n"\
    "uniform highp mat4 kix_ModelViewProjectionMatrix;\n"\
    "uniform highp mat4 kix_ModelViewMatrix;\n"\
    "uniform highp mat3 kix_NormalMatrix;\n"\
    "attribute highp vec4 kix_Vertex;\n"\
    "attribute highp vec3 kix_Normal;\n"\
    "attribute highp vec3 kix_Tangent;\n"\
    "attribute highp vec2 kix_TexCoord;\n"
*/

GLuint KxMaterial::loadTexture(const QString &fileName)
{
    qDebug() << "KxMaterial::loadTexture" << fileName;
    GLuint texture = kxEngine->glDrawer()->bindTexture(fileName);
    if (!texture)
        qWarning() << "KxMaterial::loadTexture cant load texture" << fileName;
    return texture;
}

void KxMaterial::deleteTexture(GLuint texture)
{
    KxEngine::instance()->glDrawer()->deleteTexture(texture);
}

KxMaterial::KxMaterial(QObject *parent) :
    QObject (parent)
{
    m_blendDst = -1;
    m_blendSrc = -1;
    m_sorting = false;
    m_program = new QGLShaderProgram(this);
}

bool KxMaterial::init()
{
    KxEngine::instance()->glDrawer()->makeCurrent();
    m_program->bindAttributeLocation("kix_Vertex", 0);
    m_program->bindAttributeLocation("kix_Normal", 1);
    m_program->bindAttributeLocation("kix_TexCoord", 2);
    m_program->bindAttributeLocation("kix_Tangent", 3);
    if (!m_program->link()) {
        qDebug() << "KxMaterial::init cant link shader";
        KxEngine::instance()->glDrawer()->doneCurrent();
        return false;
    }
    m_mvPrMatrixLoc = m_program->uniformLocation("kix_ModelViewProjectionMatrix");
    m_mvMatrixLoc = m_program->uniformLocation("kix_ModelViewMatrix");
    m_prMatrixLoc = m_program->uniformLocation("kix_ProjectionMatrix");
    m_norMatrixLoc = m_program->uniformLocation("kix_NormalMatrix");
    m_numLightsLoc = m_program->uniformLocation("kix_NumLights");
    m_hasLights = m_program->uniformLocation("kix_LightSource[0].ambient") != -1;

    if (metaObject()->className() != KxMaterial::staticMetaObject.className()) {
        for (int i = metaObject()->propertyOffset(); i < metaObject()->propertyCount() ; ++i) {
            QString propName = metaObject()->property(i).name();
            if (metaObject()->property(i).type() == QVariant::String) {
                int loc = m_program->uniformLocation(propName);
                if (loc != -1)
                    m_textures[loc] = new QImage(metaObject()->property(i).read(this).toString());
            } else {
                int loc = m_program->uniformLocation(propName);
                if (loc != -1)
                    m_propertyUniforms.insert(loc, i);
            }
        }
    }
    KxEngine::instance()->glDrawer()->doneCurrent();
    return true;
}

void KxMaterial::componentComplete()
{   
    init();
}

void KxMaterial::classBegin()
{
}

KxMaterial::~KxMaterial()
{
    foreach (QImage *tex, m_textures.values())
        delete tex;
    //KxEngine::instance()->shareGLWidget()->deleteTexture(texId);
}

void KxMaterial::setVertexShaderSource(const QString &value)
{
    KxEngine::instance()->glDrawer()->makeCurrent();
    if (!m_program->addShaderFromSourceCode(QGLShader::Vertex, value)) {
        qWarning() << "KxMaterial::setVertexShaderSource cant compile shader source";
        qWarning() << m_program->log();
    }
    KxEngine::instance()->glDrawer()->doneCurrent();
}

void KxMaterial::setFragmentShaderSource(const QString &value)
{
    KxEngine::instance()->glDrawer()->makeCurrent();
    if (!m_program->addShaderFromSourceCode(QGLShader::Fragment, value)) {
        qWarning() << "KxMaterial::setFragmentShaderSource cant compile shader source";
        qWarning() << m_program->log();
    }
    KxEngine::instance()->glDrawer()->doneCurrent();
}

QString KxMaterial::vertexShaderSource() const
{
    foreach (QGLShader *shader, m_program->shaders())
        if (shader->shaderType() == QGLShader::Vertex)
            return shader->sourceCode();
    return "";
}

QString KxMaterial::fragmentShaderSource() const
{
    foreach (QGLShader *shader, m_program->shaders())
        if (shader->shaderType() == QGLShader::Fragment)
            return shader->sourceCode();
    return "";
}

void KxMaterial::release()
{
    m_mutex.lock();
    for (int i = 0; i < 4; i++)
        m_program->disableAttributeArray(i);
    m_program->release();
    if (m_blendSrc != -1)
        glDisable(GL_BLEND);
    if (m_sorting)
        glEnable(GL_CULL_FACE);
    m_mutex.unlock();
}

void KxMaterial::bind(KxCamera *camera, KxSceneNode *node)
{
    m_mutex.lock();
    if (m_sorting)
        glDisable(GL_CULL_FACE);
    if (m_blendSrc != -1) {
        glEnable(GL_BLEND);
        glBlendFunc(m_blendSrc, m_blendDst);
    }

    m_program->bind();
    //property uniformy
    QMap<int, int>::Iterator uniIter = m_propertyUniforms.begin();
    while(uniIter != m_propertyUniforms.end()) {
        QVariant var = metaObject()->property(uniIter.value()).read(this);
        switch(var.type()) {
        case QMetaType::Float:
            m_program->setUniformValue(uniIter.key(), var.toFloat());
            break;
        case QVariant::Int:
            m_program->setUniformValue(uniIter.key(), var.toInt());
            break;
        case QVariant::UInt:
            m_program->setUniformValue(uniIter.key(), var.toUInt());
            break;
        case QVariant::Bool:
            m_program->setUniformValue(uniIter.key(), var.toBool());
            break;
        case QVariant::Color:
            m_program->setUniformValue(uniIter.key(), var.value<QColor>());
            break;
        case QMetaType::QVector2D:
            m_program->setUniformValue(uniIter.key(), var.value<QVector2D>());
            break;
        case QMetaType::QVector3D:
            m_program->setUniformValue(uniIter.key(), var.value<QVector3D>());
            break;
        case QMetaType::QVector4D:
            m_program->setUniformValue(uniIter.key(), var.value<QVector4D>());
            break;
        case QMetaType::QMatrix4x4:
            m_program->setUniformValue(uniIter.key(), var.value<QMatrix4x4>());
            break;
        default:
            break;
        }
        ++uniIter;
    }

    //textury
    QMap<int, QImage*>::Iterator texIter = m_textures.begin();
    uint id = 0;
    while(texIter != m_textures.end()) {
        m_program->setUniformValue(texIter.key(), id);
        glActiveTexture(GL_TEXTURE0 + id);
        kxEngine->glDrawer()->bindTexture(*texIter.value());
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
        id++;
        texIter++;
    }
    glActiveTexture(GL_TEXTURE0);

    //glob uniforms, matice
    if (m_mvMatrixLoc != -1)
        m_program->setUniformValue(m_mvMatrixLoc, kxGLDrawer->modelViewMatrix());
    if (m_prMatrixLoc != -1)
        m_program->setUniformValue(m_prMatrixLoc, kxGLDrawer->projectionMatrix());
    if (m_mvPrMatrixLoc != -1)
        m_program->setUniformValue(m_mvPrMatrixLoc, kxGLDrawer->modelViewProjectionMatrix());
    if (m_norMatrixLoc != -1)
        m_program->setUniformValue(m_norMatrixLoc, kxGLDrawer->modelViewMatrix().normalMatrix());

    //light
    if (m_hasLights) {
        QList<KxLight *> lights = camera->lightsForNode(node);
        if (m_numLightsLoc != -1)
            m_program->setUniformValue(m_numLightsLoc, lights.size());
        int i = 0;
        foreach (KxLight *light, lights) {
            char str[64];
            qsnprintf(str, sizeof(str), "kix_LightSource[%d].ambient", i);
            m_program->setUniformValue(str, light->ambient());
            qsnprintf(str, sizeof(str), "kix_LightSource[%d].diffuse", i);
            m_program->setUniformValue(str, light->diffuse());
            qsnprintf(str, sizeof(str), "kix_LightSource[%d].specular", i);
            m_program->setUniformValue(str, light->specular());
            qsnprintf(str, sizeof(str), "kix_LightSource[%d].position", i);
            m_program->setUniformValue(str, kxGLDrawer->viewMatrix().map(light->absolutePosition()));
            qsnprintf(str, sizeof(str), "kix_LightSource[%d].spotDirection", i);          
            m_program->setUniformValue(str, kxGLDrawer->viewMatrix().mapVector(light->absoluteSpotDirection()));
            qsnprintf(str, sizeof(str), "kix_LightSource[%d].spotExponent", i);
            m_program->setUniformValue(str, (GLfloat)light->spotExponent());
            qsnprintf(str, sizeof(str), "kix_LightSource[%d].spotCutoff", i);
            m_program->setUniformValue(str, (GLfloat)light->spotCutoff());
            qsnprintf(str, sizeof(str), "kix_LightSource[%d].spotCosCutoff", i);
            m_program->setUniformValue(str, (GLfloat)qCos(light->spotCutoff()));
            qsnprintf(str, sizeof(str), "kix_LightSource[%d].constantAttenuation", i);
            m_program->setUniformValue(str, (GLfloat)light->constantAttenuation());
            qsnprintf(str, sizeof(str), "kix_LightSource[%d].linearAttenuation", i);
            m_program->setUniformValue(str, (GLfloat)light->linearAttenuation());
            qsnprintf(str, sizeof(str), "kix_LightSource[%d].quadraticAttenuation", i);
            m_program->setUniformValue(str, (GLfloat)light->quadraticAttenuation());
            qsnprintf(str, sizeof(str), "kix_LightSource[%d].directional", i);
            m_program->setUniformValue(str, light->isDirectional());
            i++;
        }
    }

    //geometria
    KxDrawableSceneNode *drawableNode = qobject_cast<KxDrawableSceneNode *>(node);
    if (drawableNode) {
        m_program->enableAttributeArray(0);
        m_program->setAttributeArray(0, drawableNode->geometryData()->vertices().constData());
        if (drawableNode->geometryData()->hasNormals()) {
            m_program->enableAttributeArray(1);
            m_program->setAttributeArray(1, drawableNode->geometryData()->normals().constData());
        }
        if (drawableNode->geometryData()->hasTexCoords()) {
            m_program->enableAttributeArray(2);
            m_program->setAttributeArray(2, drawableNode->geometryData()->texCoords().constData());
        }
        if (drawableNode->geometryData()->hasTangents()) {
            m_program->enableAttributeArray(3);
            m_program->setAttributeArray(3, drawableNode->geometryData()->tangents().constData());
        }
    }
    m_mutex.unlock();
}
