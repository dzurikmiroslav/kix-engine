#include <qapplication.h>
#include <QtGui/qsplashscreen.h>
#include "KxEngine/kxengine.h"

int main(int argc, char *argv[])
{   
    Q_INIT_RESOURCE(resources);
    QApplication application(argc, argv);

    QSplashScreen splash(QPixmap(":splash"));
    splash.show();
    splash.showMessage("Loading...", Qt::AlignLeft | Qt::AlignBottom);
    qApp->processEvents();
    KxEngine engine;
    engine.init();
    splash.finish(&engine);
    engine.startMainLoop();

    return application.exec();
}
