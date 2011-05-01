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

#include "kxbulletdebugdrawer.h"
#include <QtOpenGL/qgl.h>
#include <QDebug>
#include "kxphysicsworld.h"
#include "KxScene/kxcamera.h"
#include <QtOpenGL/qglshaderprogram.h>
#include "KxEngine/kxengine.h"

#define VERTEX_SHADER \
"attribute highp vec4 v;\n" \
"uniform highp mat4 m;\n" \
"void main()\n" \
"{\n" \
"	gl_Position = m * v;\n" \
"}\n"

#define FRAGMENT_SHADER \
"uniform highp vec4 c;\n" \
"void main()\n" \
"{\n" \
"    gl_FragColor = c;\n" \
"}\n"

KxBulletDebugDrawer::KxBulletDebugDrawer(qreal scale)
{
    m_scale = scale;
    m_debugMode = DBG_DrawWireframe | DBG_DrawConstraints | DBG_DrawConstraintLimits;

    m_program = new QGLShaderProgram();
    KxEngine::instance()->glDrawer()->makeCurrent();
    m_program->addShaderFromSourceCode(QGLShader::Vertex, VERTEX_SHADER);
    m_program->addShaderFromSourceCode(QGLShader::Fragment, FRAGMENT_SHADER);
    m_program->link();
    KxEngine::instance()->glDrawer()->doneCurrent();
    m_indicesArray[0] = 0;
    m_indicesArray[1] = 1;
}

KxBulletDebugDrawer::~KxBulletDebugDrawer()
{
    delete m_program;
}

void KxBulletDebugDrawer::bind()
{
    m_program->bind();
    m_program->setUniformValue("m", kxGLDrawer->modelViewProjectionMatrix());
    m_program->enableAttributeArray("v");
    m_program->setAttributeArray("v", m_vertArray);
}

void KxBulletDebugDrawer::release()
{
     m_program->release();
}

void KxBulletDebugDrawer::drawLine(const btVector3& from,const btVector3& to,const btVector3& color)
{
    m_program->setUniformValue("c", QColor::fromRgbF(color.x(), color.y(), color.z()));
    m_vertArray[0] = KxBulletUtil::convert(m_scale * from);
    m_vertArray[1] = KxBulletUtil::convert(m_scale * to);
    glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, m_indicesArray);
}

void KxBulletDebugDrawer::drawContactPoint(const btVector3 &/*PointOnB*/, const btVector3 &/*normalOnB*/, btScalar /*distance*/, int /*lifeTime*/, const btVector3 &/*color*/)
{
}

void KxBulletDebugDrawer::reportErrorWarning(const char *warningString)
{
    qDebug() << "KxBulletDebugDrawer::reportErrorWarning" << warningString;
}

void KxBulletDebugDrawer::draw3dText (const btVector3 &/*location*/, const char */*textString*/)
{
  //  qDebug() << "draw3dText" << textString;
}

void KxBulletDebugDrawer::setDebugMode(int debugMode)
{
    m_debugMode = debugMode;
}

int KxBulletDebugDrawer::getDebugMode() const
{
    return m_debugMode;
}
