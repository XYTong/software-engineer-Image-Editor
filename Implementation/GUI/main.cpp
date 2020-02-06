#include <QApplication>
#include <QCommandLineParser>

#include "imageviewer.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QGuiApplication::setApplicationDisplayName(ImageViewer::tr("IntelliPhoto"));
    ImageViewer imageViewer;
    imageViewer.show();
    return app.exec();
}
