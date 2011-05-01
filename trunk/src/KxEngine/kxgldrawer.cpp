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

#include "kxgldrawer.h"
#include "KxScene/kxcamera.h"
#include "kxengine.h"
#include "KxPhysics/kxphysicsworld.h"

KxGLDrawer::KxGLDrawer() :
    QGLWidget()
{
    QGLWidget::makeCurrent();
    m_clearColor = QColor(100, 100, 100);
}

KxGLDrawer *KxGLDrawer::instance()
{
    return kxEngine->glDrawer();
}

void KxGLDrawer::initializeGL()
{
    glCullFace(GL_FRONT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glDepthMask(GL_TRUE);
}

void KxGLDrawer::draw(KxCamera *camera)
{
    m_mutex.lock();
    int width = kxEngine->width();
    int height = kxEngine->height();

    qglClearColor(m_clearColor);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glFrontFace(GL_CW);
    glCullFace(GL_BACK);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, width, height);

    camera->computeProjectionMatrix(m_projectionMatrix, (qreal) width / (qreal) height);
    camera->computeModelViewMatrix(m_modelViewMatrix);
    //debug draw
    if (kxEngine->settings()["physics.debug_draw"].toBool())
        kxEngine->physicsWorld()->debugDraw();
    //scene space
    camera->drawScene();

    glFlush();
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    m_mutex.unlock();
}
