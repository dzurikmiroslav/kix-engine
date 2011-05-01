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

#ifndef KXGLDRAWER_H
#define KXGLDRAWER_H

#include <QtOpenGL/qgl.h>
#include <QtCore/qmutex.h>
#include <QtCore/qstack.h>
#include <QtGui/qmatrix4x4.h>

class KxCamera;

class KxGLDrawer : public QGLWidget
{
    // Q_OBJECT

public:
    void draw(KxCamera *camera);

    virtual void initializeGL();

    inline void makeCurrent();
    inline void doneCurrent();   

    inline const QMatrix4x4& modelViewMatrix() const;
    inline const QMatrix4x4& projectionMatrix() const;
    inline QMatrix4x4 modelViewProjectionMatrix() const;

    inline QMatrix4x4& modelViewMatrix();
    inline const QMatrix4x4& viewMatrix() const;

    inline void pushModelViewMatrix();
    inline void popModelViewMatrix();

    static KxGLDrawer *instance();

private:
    explicit KxGLDrawer();
    QMutex m_mutex;
    QColor m_clearColor;
    QMatrix4x4 m_modelViewMatrix;
    QMatrix4x4 m_projectionMatrix;
    QStack<QMatrix4x4> m_modelViewMatrixStack;

    friend class KxEngine;
};

#define kxGLDrawer KxGLDrawer::instance()

inline const QMatrix4x4& KxGLDrawer::projectionMatrix() const
{
    return m_projectionMatrix;
}

inline QMatrix4x4 KxGLDrawer::modelViewProjectionMatrix() const
{
    return m_projectionMatrix * m_modelViewMatrix;
}

inline const QMatrix4x4& KxGLDrawer::modelViewMatrix() const
{
    return m_modelViewMatrixStack.top();
}

inline QMatrix4x4& KxGLDrawer::modelViewMatrix()
{
    return m_modelViewMatrix;
}

inline const QMatrix4x4& KxGLDrawer::viewMatrix() const
{
    return m_modelViewMatrixStack.first();
}

void KxGLDrawer::pushModelViewMatrix()
{
    m_modelViewMatrixStack.push(m_modelViewMatrix);
}

void KxGLDrawer::popModelViewMatrix()
{
    m_modelViewMatrix = m_modelViewMatrixStack.pop();
}

inline void KxGLDrawer::makeCurrent()
{
    m_mutex.lock();
}

inline void KxGLDrawer::doneCurrent()
{
    m_mutex.unlock();
}

#endif // KXGLDRAWER_H
