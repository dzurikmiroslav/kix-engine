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

#include "kxengine.h"
#include "kxuserinputs.h"
#include "KxScene/kxcamera.h"
#include "KxScene/kxscene.h"
#include "KxEntity/kxentity.h"
#include "KxDeclarative/kxdeclarative.h"
#include "KxPhysics/kxphysicsworld.h"
#include "kxgraphicsscene.h"
#include "KxDeclarative/kxdeclarative.h"
#include <QtCore/qfile.h>
#include <QtCore/qdir.h>
#include <QtXml/qdom.h>
#include <QtGui/qgraphicsscene.h>
#include <QtOpenGL/qglpixelbuffer.h>
#include <QtGui/qwidget.h>
#include <QtGui/qstackedlayout.h>
#include <QtGui/qgraphicsview.h>
#include <QtGui/qdesktopwidget.h>
#include <QtDeclarative/qdeclarativeengine.h>
#include <QtDeclarative/qdeclarativecomponent.h>
#include <QtDeclarative/qdeclarativeexpression.h>
#include <qapplication.h>
#include "kxsimdutils.h"
#include "kxompsimdutils.h"

#ifdef Q_OS_WIN32
#include <GL/glext.h>
PFNGLACTIVETEXTUREPROC glActiveTexture;
#endif

KxEngine *KxEngine::m_instance;

KxEngine::KxEngine(QWidget *parent) :
    QMainWindow(parent)
{
    m_glDrawer = NULL;
    m_instance = this;  
    qApp->setApplicationName("kiX engine");
    qApp->setApplicationVersion("0.01b");
    qApp->setOrganizationName("kiX labs");
    setDefaultSettings();
    setSettingsFromArgs();
    m_userInputs = new KxUserInputs(this);
    m_graphicsScene = new KxGraphicsScene(this);
    setCentralWidget(m_graphicsScene->view());
    setMouseTracking(true);
    installEventFilter(m_userInputs);
}

void KxEngine::setSettingsFromArgs()
{
    qDebug() << "KxEngine::setSettingsFromArgs";
    //QRegExp regExp("((video)|(controls)|(path)).*");
    for(int i(1); i < qApp->argc(); i += 2) {
        if(qApp->argv()[i][0] == '-') {
            if(QString("-config") == qApp->argv()[i])
                loadConfig(qApp->argv()[i + 1]);
            else {
                m_settings[qApp->argv()[i]] = qApp->argv()[i + 1];
                qDebug() << "\tset" << qApp->argv()[i] << qApp->argv()[i + 1];
            }
        }
    }
    if (!qApp->arguments().contains("-config"))
        loadConfig("config.xml");
}

void KxEngine::setDefaultSettings()
{
    qDebug() << "KxEngine::setDefaultSettings";
    m_settings.clear();
#ifdef Q_WS_SIMULATOR
    m_settings["video.width"] = qApp->desktop()->screen()->width();
    m_settings["video.height"] = qApp->desktop()->screen()->width();
    m_settings["video.fullscreen"] = true;
#else
    m_settings["video.width"] = 800;
    m_settings["video.height"] = 600;
    m_settings["video.fullscreen"] = false;
#endif
    m_settings["video.samples"] = 0;
    m_settings["video.max_fps"] = 333;
    m_settings["controls.mouse_sensitivity.x"] = (qreal) 1;
    m_settings["controls.mouse_sensitivity.y"] = (qreal) 1;
    m_settings["path"] = QDir::currentPath();
    m_settings["physics.scaling"] = (qreal) 1;
    m_settings["physics.debug_draw"] = false;
    m_settings["entity.root"] = "Context.qml";
    emit settingsChanged();
}

bool KxEngine::loadRootEntity(const QString &fileName)
{
    qDebug() << "KxEngine::loadRootEntity" << fileName;
    KxEntity *e = m_declarative->loadEntity(fileName, this);
    if (e) {
        m_rootEntity = e;
        return true;
    } else
        return false;
}

void KxEngine::updateAll()
{
    m_mutex.lock();
    int eplased = m_time.restart();
    m_fps = eplased ? qRound((qreal)1000 / (qreal)eplased) : 0;
    //qDebug() << "fps=" << m_fps;
    QTime t;
    t.start();
    m_scene->update(eplased);
    m_sceneUpdateFactor = t.restart();
    m_physicsWorld->update(eplased);
    m_physicsUpdateFactor = t.restart();
    m_graphicsScene->update();
    m_drawingFactor = t.restart();
    qreal factorSum = m_sceneUpdateFactor + m_physicsUpdateFactor + m_drawingFactor;
    m_sceneUpdateFactor = m_sceneUpdateFactor / factorSum;
    m_physicsUpdateFactor = m_physicsUpdateFactor / factorSum;
    m_drawingFactor = m_drawingFactor / factorSum;
    //qDebug() << m_sceneUpdateFactor << m_physicsUpdateFactor << m_drawingFactor;
    m_mutex.unlock();
    QTimer::singleShot(0, this, SLOT(updateAll()));
}

KxPhysicsWorld* KxEngine::physicsWorld() const
{
    return m_physicsWorld;
}

KxGraphicsScene *KxEngine::graphicsScene() const
{
    return m_graphicsScene;
}

int KxEngine::fps() const
{
    return m_fps;
}

const QMap<QString, QVariant>& KxEngine::settings() const
{
    return m_settings;
}

QMap<QString, QVariant>& KxEngine::settings()
{
    return m_settings;
}

KxGLDrawer *KxEngine::glDrawer() const
{
    return m_glDrawer;
}

KxEngine *KxEngine::instance()
{
    return m_instance;
}

KxDeclarative *KxEngine::declarative() const
{
    return m_declarative;
}

KxEntity *KxEngine::rootEntity() const
{
    return m_rootEntity;
}

void KxEngine::setRootEntity(KxEntity *value)
{
    m_rootEntity = value;
}

KxUserInputs* KxEngine::userInputs() const
{
    return m_userInputs;
}

KxScene* KxEngine::scene() const
{
    return m_scene;
}

void KxEngine::exit()
{
    close();
}

bool KxEngine::init()
{
    qDebug() << "KxEngine::init";

#ifdef KX_OPEN_MP
    KxSIMDUtils::m_instance = new KxOMPSIMDUtils();
    qDebug() << "KxEngine::init using OpenMP utils";
#else
    KxSIMDUtils::m_instance = new KxSIMDUtils();
    qDebug() << "KxEngine::init using no SIMD utils";
#endif // KX_OPEN_MP

    if (!QDir::setCurrent(m_settings["path"].toString()))
        qCritical() << "KxEngine::init cant set application path" << m_settings["path"].toString();

    //setFixedSize(m_settings["video.width"].toInt(), m_settings["video.height"].toInt());

    QGLFormat format;
    /*format.setDoubleBuffer(true);
    format.setDepthBufferSize(24);
    format.setRedBufferSize(32);
    format.setGreenBufferSize(32);
    format.setBlueBufferSize(32);
    format.setAlphaBufferSize(32);*/
    format.setSamples(m_settings["video.samples"].toInt());
    QGLFormat::setDefaultFormat(format);

    m_glDrawer = new KxGLDrawer();
    //  m_glDrawer->installEventFilter(m_userInputs);
    qDebug() << "KxEngine::init OpenGL" << QGLFormat::hasOpenGL();
    qDebug() << "KxEngine::init OpenGL overlays" << QGLFormat::hasOpenGLOverlays();
    qDebug() << "KxEngine::init OpenGL GLSL" << QGLShaderProgram::hasOpenGLShaderPrograms(m_glDrawer->context());
    qDebug() << "KxEngine::init OpenGL pixel buffer" << QGLPixelBuffer::hasOpenGLPbuffers();
#ifdef Q_OS_WIN32
    glActiveTexture = (PFNGLACTIVETEXTUREPROC)m_glDrawer->context()->getProcAddress("glActiveTexture");
#endif
    m_scene = new KxScene(this);

    qDebug() << "KxEngine::init created scene";

    m_physicsWorld = new KxPhysicsWorld(this);
    qDebug() << "KxEngine::init created physics world";

    m_declarative = new KxDeclarative(this);
    qDebug() << "KxEngine::init created declarative engine";

    if ((m_settings["entity.root"].type() == QVariant::String) ||
            (m_settings["entity.root"].type() == QVariant::Url))
        loadRootEntity(m_settings["entity.root"].toString());

    return true;
}

void KxEngine::startMainLoop()
{
    qDebug() << "KxEngine::startMainLoop";
#ifdef Q_WS_SIMULATOR
    showFullScreen();
#else
    if(m_settings["video.fullscreen"].toBool())
        showFullScreen();
    else {
        setFixedSize(m_settings["video.width"].toInt(), m_settings["video.height"].toInt());
        show();
    }
#endif // Q_WS_SIMULATOR
    m_time.restart();
    updateAll();
}

bool KxEngine::loadConfig(const QString & fileName)
{
    qDebug() << "KxEngine::loadConfig" << fileName;
    QFile file(fileName);
    if (!file.exists()) {
        qWarning() << "KxEngine::loadConfig file not exist" << fileName;
        return false;
    }
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "KxEngine::loadConfig cant read file" << fileName;
        return false;
    }
    QDomDocument document;
    int errorLine,errorColumn;
    QString errorMsg;
    if(!document.setContent(&file, &errorMsg, &errorLine, &errorColumn)) {
        qWarning() << "KxEngine::loadConfig cant parse file" << fileName;
        qWarning() << "line:" << errorLine << "column:" << errorColumn;
        file.close();
        return false;
    }
    QDomElement root = document.documentElement();
    if(root.nodeName() != "config") {
        file.close();
        return false;
    }
    QDomNodeList list = root.childNodes();
    for(uint i(0); i < list.length(); i++) {
        if(!list.item(i).isElement())
            continue;
        QDomElement propElem = list.item(i).toElement();
        if(propElem.nodeName() != "property")
            continue;
        QString key = propElem.attribute("key");
        QString value = propElem.attribute("value");
        m_settings[key.toLocal8Bit()] = value;
        qDebug() << "KxEngine::loadConfig set" << key << value;
    }
    if(m_settings["video.fullscreen"].toBool()) {
        m_settings["video.width"] = qApp->desktop()->width();
        m_settings["video.height"] = qApp->desktop()->height();
    }
    emit settingsChanged();
    return true;
}

KxEngine::~KxEngine()
{
    qDebug() << "KxEngine::~KxEngine";
    delete m_glDrawer;
    delete KxSIMDUtils::m_instance;
    //delete scene;
    //delete userInputs;
}

