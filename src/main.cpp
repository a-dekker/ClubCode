#ifdef QT_QML_DEBUG
#include <QtQuick>
#endif

#include <sailfishapp.h>
#include <QtQml>
#include <QFontDatabase>
#include <QQuickView>
#include <QtGui>

#include "AddNewCodePageViewModel.h"
#include "MainViewModel.h"
#include "BarcodeImageProvider.h"
#include "EditCodePageViewModel.h"


int main(int argc, char *argv[])
{
    qmlRegisterType<MainViewModel>("harbour.clubcode", 0, 1, "MainViewModel");
    qmlRegisterType<AddNewCodePageViewModel>("harbour.clubcode", 0, 1, "AddNewCodePageViewModel");
    qmlRegisterType<EditCodePageViewModel>("harbour.clubcode", 0, 1, "EditCodePageViewModel");

    QGuiApplication *application = SailfishApp::application(argc, argv);
    QQuickView *view = SailfishApp::createView();

    QFontDatabase fontDatabase;
    fontDatabase.addApplicationFont(":/fonts/code128.ttf");
    fontDatabase.addApplicationFont(":/fonts/ean13.ttf");
    fontDatabase.addApplicationFont(":/fonts/code39.ttf");

    view->setSource(SailfishApp::pathTo("qml/harbour-clubcode.qml"));
    view->showFullScreen();

    return application->exec();
}
