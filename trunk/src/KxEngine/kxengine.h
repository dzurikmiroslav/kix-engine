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

#ifndef KX_ENGINE_H
#define KX_ENGINE_H

#include <QtCore/qtimer.h>
#include <QtCore/qdatetime.h>
#include <QtCore/qmutex.h>
#include <QtGui/qmainwindow.h>
#include <QtOpenGL/qgl.h>
#include "KxScene/kxscene.h"
#include "kxgldrawer.h"

class KxCamera;
class KxPhysicsWorld;
class KxEntity;
class KxUserInputs;
class KxGraphicsScene;
class KxDeclarative;

class KxEngine: public QMainWindow
{
    Q_OBJECT
    Q_PROPERTY(KxUserInputs *userInputs READ userInputs CONSTANT FINAL)
    Q_PROPERTY(KxScene *scene READ scene CONSTANT FINAL)
    Q_PROPERTY(KxPhysicsWorld *physicsWorld READ physicsWorld CONSTANT FINAL)
    Q_PROPERTY(KxEntity *rootEntity READ rootEntity WRITE setRootEntity FINAL)
    Q_PROPERTY(KxGraphicsScene *graphicsScene READ graphicsScene CONSTANT FINAL)
    Q_PROPERTY(QVariantMap settings READ settings NOTIFY settingsChanged FINAL)

public:
    explicit KxEngine(QWidget *parent = 0);
    ~KxEngine();

    static KxEngine *instance();

    bool loadConfig(const QString &fileName);

    bool init();

    Q_INVOKABLE void exit();

    void setDefaultSettings();  //nastavi def. hodnoty
    void setSettingsFromArgs();    //nastavi hodnoty ktore su v argumentoch

    KxEntity *rootEntity() const;
    void setRootEntity(KxEntity *value);
    bool loadRootEntity(const QString &fileName);   //nacita v podsate celu hru ?

    KxDeclarative *declarative() const;

    KxPhysicsWorld *physicsWorld() const;

    KxGraphicsScene *graphicsScene() const;

    KxUserInputs *userInputs() const;

    KxScene *scene() const;

    KxGLDrawer *glDrawer() const;
    const QMap<QString, QVariant>& settings() const;
    QMap<QString, QVariant>& settings();

    void startMainLoop();
    int fps() const;

    QMutex m_mutex;
    QList<KxSceneNode*> tm_toRemove;

signals:
    void settingsChanged();
    void frameChanged();

private slots:
    void updateAll();

private:
    QMap<QString, QVariant> m_settings;
    QTime m_time;
    int m_fps;
    qreal m_sceneUpdateFactor;
    qreal m_physicsUpdateFactor;
    qreal m_drawingFactor;
    KxGLDrawer *m_glDrawer;
    KxUserInputs *m_userInputs;
    KxScene *m_scene;
    KxPhysicsWorld *m_physicsWorld;
    KxDeclarative *m_declarative;
    KxGraphicsScene *m_graphicsScene;
    KxEntity *m_rootEntity;
    static KxEngine *m_instance;

};

#define kxEngine KxEngine::instance()

Q_DECLARE_METATYPE(KxEngine*);

#endif /* KX_ENGINE_H */
