TEMPLATE = app
TARGET = kix_engine
QT += core gui xml opengl declarative
#QT += phonon
INCLUDEPATH += src
RESOURCES += resources.qrc
INCLUDEPATH += (BULLET include path)
LIBS += (BULLET libs)

HEADERS += \
    src/KxEngine/kxengine.h \
    src/KxEngine/kxuserinputs.h \
    src/KxEngine/kxgraphicsscene.h \
    src/KxPhysics/kxcollisionobject.h \
    src/KxPhysics/kxrigidbody.h \
    src/KxPhysics/kxbulletutil.h \
    src/KxPhysics/kxphysicsworld.h \
    src/KxPhysics/kxcollisionshape.h \
    src/KxPhysics/kxcompoundshape.h \
    src/KxEngine/kxglobal.h \
    src/KxPhysics/kxcharactercontroller.h \
    src/KxPhysics/kxbulletdebugdrawer.h \
    src/KxPhysics/kxconvexshape.h \
    src/KxPhysics/kxconcaveshape.h \
    src/KxPhysics/kxghostobject.h \
    src/KxEntity/kxentity.h \
    src/KxPhysics/kxrayresultcallback.h \
    src/KxDeclarative/kxnamespace.h \
    src/KxDeclarative/kxdeclarative.h \
    src/KxPhysics/kxrigidbodycon.h \
    src/KxPhysics/kxcharactercontrollercon.h \
    src/KxScene/kxthirdpersoncamera.h \
    src/KxScene/kxscenenode.h \
    src/KxScene/kxscene.h \
    src/KxScene/kxmodelcon.h \
    src/KxScene/kxmodel.h \
    src/KxScene/kxmd5model.h \
    src/KxScene/kxmd5animation.h \
    src/KxScene/kxmath.h \
    src/KxScene/kxmaterial.h \
    src/KxScene/kxlight.h \
    src/KxScene/kxflycamera.h \
    src/KxScene/kxfirstpersoncamera.h \
    src/KxScene/kxcamera.h \
    src/KxPhysics/kxraycastvehicle.h \
    src/KxPhysics/kxraycastvehiclecon.h \
    src/KxPhysics/kxtypedconstraint.h \
    src/KxPhysics/kxgeneric6dofconstraint.h \
    src/KxPhysics/kxgeneric6dofspringconstraint.h \
    src/KxDeclarative/kxsound.h \
    src/KxPhysics/kxgeneric6dofconstraintcon.h \
    src/KxPhysics/kxgeneric6dofspringconstraintcon.h \
    src/KxScene/kxindexedgeometrydata.h \
    src/KxScene/kxgeometrydata.h \
    src/KxEngine/kxgldrawer.h \
    src/KxScene/kxmd5modelmesh.h \
    src/KxEngine/kxsimdutils.h \
    src/KxEngine/kxompsimdutils.h \
    src/KxScene/kxdrawablescenenode.h \
    src/KxScene/kxdrawablescenenodecon.h \
    src/KxScene/kxscenenodecon.h

SOURCES += src/main.cpp \
    src/KxScene/kxthirdpersoncamera.cpp \
    src/KxScene/kxscenenode.cpp \
    src/KxScene/kxscene.cpp \
    src/KxScene/kxmodelcon.cpp \
    src/KxScene/kxmodel.cpp \
    src/KxScene/kxmd5model.cpp \
    src/KxScene/kxmd5animation.cpp \
    src/KxScene/kxmath.cpp \
    src/KxScene/kxmaterial.cpp \
    src/KxScene/kxlight.cpp \
    src/KxScene/kxgeometrydata.cpp \
    src/KxScene/kxflycamera.cpp \
    src/KxScene/kxfirstpersoncamera.cpp \
    src/KxScene/kxcamera.cpp \
    src/KxEngine/kxengine.cpp \
    src/KxEngine/kxuserinputs.cpp \
    src/KxEngine/kxgraphicsscene.cpp \
    src/KxPhysics/kxcollisionobject.cpp \
    src/KxPhysics/kxrigidbody.cpp \
    src/KxPhysics/kxbulletutil.cpp \
    src/KxPhysics/kxphysicsworld.cpp \
    src/KxPhysics/kxcollisionshape.cpp \
    src/KxPhysics/kxcompoundshape.cpp \
    src/KxPhysics/kxcharactercontroller.cpp \
    src/KxPhysics/kxbulletdebugdrawer.cpp \
    src/KxPhysics/kxconvexshape.cpp \
    src/KxPhysics/kxconcaveshape.cpp \
    src/KxPhysics/kxghostobject.cpp \
    src/KxPhysics/kxcharactercontrollercon.cpp \
    src/KxEntity/kxentity.cpp \
    src/KxPhysics/kxrayresultcallback.cpp \
    src/KxDeclarative/kxnamespace.cpp \
    src/KxDeclarative/kxdeclarative.cpp \
    src/KxPhysics/kxrigidbodycon.cpp \
    src/KxPhysics/kxraycastvehicle.cpp \
    src/KxPhysics/kxraycastvehiclecon.cpp \
    src/KxPhysics/kxtypedconstraint.cpp \
    src/KxPhysics/kxgeneric6dofconstraint.cpp \
    src/KxPhysics/kxgeneric6dofspringconstraint.cpp \
    src/KxDeclarative/kxsound.cpp \
    src/KxPhysics/kxgeneric6dofconstraintcon.cpp \
    src/KxPhysics/kxgeneric6dofspringconstraintcon.cpp \
    src/KxScene/kxindexedgeometrydata.cpp \
    src/KxEngine/kxgldrawer.cpp \
    src/KxScene/kxmd5modelmesh.cpp \
    src/KxEngine/kxsimdutils.cpp \
    src/KxEngine/kxompsimdutils.cpp \
    src/KxScene/kxdrawablescenenode.cpp \
    src/KxScene/kxdrawablescenenodecon.cpp \
    src/KxScene/kxscenenodecon.cpp

