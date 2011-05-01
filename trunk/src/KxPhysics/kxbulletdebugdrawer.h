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

#ifndef KXBULLETDEBUGDRAWER_H
#define KXBULLETDEBUGDRAWER_H

#include "btBulletCollisionCommon.h"
#include <QtOpenGL/qglshaderprogram.h>

class KxPhysicsWorld;

class KxBulletDebugDrawer : public btIDebugDraw
{    
public:
    KxBulletDebugDrawer(qreal scale);
    ~KxBulletDebugDrawer();
    virtual void drawLine(const btVector3& from,const btVector3& to,const btVector3& color);
    virtual void drawContactPoint(const btVector3 &PointOnB, const btVector3 &normalOnB, btScalar distance, int lifeTime, const btVector3 &color);
    virtual void reportErrorWarning(const char *warningString);
    virtual void draw3dText(const btVector3 &location, const char *textString);
    virtual void setDebugMode(int debugMode);
    virtual int getDebugMode()const;
    void bind();
    void release();

private:
    int m_debugMode;
    qreal m_scale;
    QGLShaderProgram *m_program;
    QVector3D m_vertArray[2];
    GLuint m_indicesArray[2];

};

#endif // KXBULLETDEBUGDRAWER_H
