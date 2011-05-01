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

#include "kxdeclarative.h"
#include "kxnamespace.h"
#include "KxEntity/kxentity.h"
#include "KxScene/kxmaterial.h"
#include "KxScene/kxmodel.h"
#include "KxScene/kxmd5model.h"
#include "KxScene/kxmodelcon.h"
#include "KxScene/kxthirdpersoncamera.h"
#include "KxScene/kxflycamera.h"
#include "KxScene/kxscene.h"
#include "KxEngine/kxengine.h"
#include "KxEngine/kxuserinputs.h"
#include "KxPhysics/kxphysicsworld.h"
#include "KxEngine/kxgraphicsscene.h"
//#include "kxvector2dclass.h"
//#include "kxvector3dclass.h"
//#include "kxvector4dclass.h"
//#include "kxquaternionclass.h"
#include "kxsound.h"

#include "QtDeclarative/QDeclarativePropertyValueSource"

KxDeclarative::KxDeclarative(QObject *parent) :
        QObject(parent)
{
    m_engine = new QDeclarativeEngine(this);
    registerTypes();
    qDebug() << "KxDeclarative::KxDeclarative offile storage path" << m_engine->offlineStoragePath();
}

KxDeclarative::~KxDeclarative()
{
}

KxDeclarative *KxDeclarative::instance()
{
    return kxEngine->declarative();
}

KxMaterial *KxDeclarative::loadMaterial(const QString &fileName, QObject *parent) const
{
    QDeclarativeComponent comp(m_engine, fileName, parent);
    if (!comp.isReady()) {
        qWarning() << "KxDeclarative::loadMaterial cant load/parse file" << fileName;
        return NULL;
    }
    QObject *obj = comp.create();
    KxMaterial *material = NULL;
    if (obj) {
        material = qobject_cast<KxMaterial*>(obj);
        if (!material) {
            qWarning() << "KxDeclarative::loadMaterial file is not material";
            delete obj;
        }
    } else {
        qWarning() << "KxDeclarative::loadMaterial cant crete object";
    }
    return material;
}

KxEntity *KxDeclarative::loadEntity(const QString &fileName, QObject *parent) const
{
    QDeclarativeComponent comp(m_engine, fileName, parent);
    if (!comp.isReady()) {
        qWarning() << "KxDeclarative::loadEntity cant load/parse file" << fileName;
        qWarning() << comp.errorString();
        return NULL;
    }
    QObject *obj = comp.create();
    KxEntity *entity = NULL;
    if (obj) {
        entity = qobject_cast<KxEntity*>(obj);
        if (!entity) {
            qWarning() << "KxDeclarative::loadEntity file is not entity";
            delete obj;
        }
    } else {
        qWarning() << "KxDeclarative::loadEntity cant crete object";
        qWarning() << comp.errorString();
    }
    return entity;
}

void KxDeclarative::registerTypes()
{
    QDeclarativeContext *rootContext = m_engine->rootContext();

    rootContext->setContextProperty("Kix", new KxNamespace(this));
    rootContext->setContextProperty("GL_ZERO", GL_ZERO);
    rootContext->setContextProperty("GL_ONE", GL_ONE);
    rootContext->setContextProperty("GL_SRC_COLOR", GL_SRC_COLOR);
    rootContext->setContextProperty("GL_ONE_MINUS_SRC_COLOR", GL_ONE_MINUS_SRC_COLOR);
    rootContext->setContextProperty("GL_SRC_ALPHA", GL_SRC_ALPHA);
    rootContext->setContextProperty("GL_ONE_MINUS_SRC_ALPHA", GL_ONE_MINUS_SRC_ALPHA);
    rootContext->setContextProperty("GL_DST_ALPHA", GL_DST_ALPHA);
    rootContext->setContextProperty("GL_ONE_MINUS_DST_ALPHA", GL_ONE_MINUS_DST_ALPHA);
    rootContext->setContextProperty("GL_DST_COLOR", GL_DST_COLOR);
    rootContext->setContextProperty("GL_ONE_MINUS_DST_COLOR", GL_ONE_MINUS_DST_COLOR);
    rootContext->setContextProperty("GL_SRC_ALPHA_SATURATE", GL_SRC_ALPHA_SATURATE);

    int vMajor = 1;
    int vMinor = 0;
    QString reason = "Cant create this class, use constructor class or Kix namespace...";
    const char *uri;

    uri = "Kix.scene3d";
    qmlRegisterUncreatableType<KxScene>(uri, vMajor, vMinor, "Scene", reason);
    qmlRegisterType<KxGeometryData>(uri, vMajor, vMinor, "GeometryData");
    qmlRegisterType<KxDrawableSceneNodeCon>(uri, vMajor, vMinor, "SceneNodeCon");
    qmlRegisterType<KxSceneNode>(uri, vMajor, vMinor, "SceneNode");
    qmlRegisterType<KxModelCon>(uri, vMajor, vMinor, "ModelCon");
    qmlRegisterType<KxModel>(uri, vMajor, vMinor, "Model");
    qmlRegisterType<KxMd5Model>(uri, vMajor, vMinor, "Md5Model");
    qmlRegisterType<KxMd5Animation>(uri, vMajor, vMinor, "Md5Animation");
    qmlRegisterType<KxCamera>(uri, vMajor, vMinor, "Camera");
    qmlRegisterType<KxThirdPersonCamera>(uri, vMajor, vMinor, "ThirdPersonCamera");
    qmlRegisterType<KxFlyCamera>(uri, vMajor, vMinor, "FlyCamera");
    qmlRegisterType<KxLight>(uri, vMajor, vMinor, "Light");

    uri = "Kix.material";
    qmlRegisterType<KxMaterial>(uri, vMajor, vMinor, "Material");

    uri = "Kix.entity";
    qmlRegisterType<KxEntity>(uri, vMajor, vMinor, "Entity");

#ifdef KIX_PHONON_SOUND
    uri = "Kix.sound";
    qmlRegisterType<KxSound>(uri, vMajor, vMinor, "Sound");
#endif // KIX_PHONON_SOUND

    uri = "Kix.physics";
    qmlRegisterType<KxRaycastVehicleCon>(uri, vMajor, vMinor, "RaycastVehicleCon");
    qmlRegisterType<KxWheelInfoCon>(uri, vMajor, vMinor, "WheelInfoCon");
    qmlRegisterType<KxGeneric6DofConstraintCon>(uri, vMajor, vMinor, "Gen6DofConstraintCon");
    qmlRegisterType<KxGeneric6DofSpringConstraintCon>(uri, vMajor, vMinor, "Gen6DofSpringConstraintCon");
    qmlRegisterType<KxRigidBodyCon>(uri, vMajor, vMinor, "RigidBodyCon");
    qmlRegisterType<KxCharacterControllerCon>(uri, vMajor, vMinor, "CharacterControllerCon");
    qmlRegisterType<KxRayResultCallback>(uri, vMajor, vMinor, "RayResultCallback");
    qmlRegisterUncreatableType<KxPhysicsWorld>(uri, vMajor, vMinor, "PhysicsWorld", reason);
    qmlRegisterUncreatableType<KxCollisionShape>(uri, vMajor, vMinor, "CollisionShape", reason);
    qmlRegisterUncreatableType<KxConvexShape>(uri, vMajor, vMinor, "ConvexShape", reason);
    qmlRegisterUncreatableType<KxConcaveShape>(uri, vMajor, vMinor, "ConcaveShape", reason);
    qmlRegisterUncreatableType<KxCollisionObject>(uri, vMajor, vMinor, "CollisionObject", reason);
    qmlRegisterUncreatableType<KxRigidBody>(uri, vMajor, vMinor, "RigidBody", reason);
    qmlRegisterUncreatableType<KxCharacterController>(uri, vMajor, vMinor, "CharacterController", reason);
    qmlRegisterUncreatableType<KxRaycastVehicle>(uri, vMajor, vMinor, "RaycastVehicle", reason);
    qmlRegisterUncreatableType<KxWheelInfo>(uri, vMajor, vMinor, "WheelInfo", reason);
    qmlRegisterUncreatableType<KxBoxShape>(uri, vMajor, vMinor, "BoxShape", reason);
    qmlRegisterUncreatableType<KxSphereShape>(uri, vMajor, vMinor, "SphereShape", reason);
    qmlRegisterUncreatableType<KxCapsuleShape>(uri, vMajor, vMinor, "CapsuleShape", reason);
    qmlRegisterUncreatableType<KxCylinderShape>(uri, vMajor, vMinor, "CylinderShape", reason);
    qmlRegisterUncreatableType<KxConeShape>(uri, vMajor, vMinor, "ConeShape", reason);
    qmlRegisterUncreatableType<KxStaticPlaneShape>(uri, vMajor, vMinor, "StaticPlaneShape", reason);
    qmlRegisterUncreatableType<KxGeneric6DofConstraint>(uri, vMajor, vMinor, "Gen6DofConstraint", reason);
    qmlRegisterUncreatableType<KxGeneric6DofSpringConstraint>(uri, vMajor, vMinor, "Gen6DofSpringConstraint", reason);
    qmlRegisterUncreatableType<KxTriangleMeshShape>(uri, vMajor, vMinor, "TriangleMeshShape", reason);
    qmlRegisterUncreatableType<KxConvexHullShape>(uri, vMajor, vMinor, "ConvexHullShape", reason);

    uri = "Kix";
    qmlRegisterUncreatableType<KxEngine>(uri, vMajor, vMinor, "Engine", reason);
    qmlRegisterUncreatableType<KxGraphicsScene>(uri, vMajor, vMinor, "GraphicsScene", reason);
    qmlRegisterUncreatableType<KxUserInputs>(uri, vMajor, vMinor, "UserInputs", reason);

}
