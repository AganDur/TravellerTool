#include <QApplication>
#include "Launcher.h"
#include "Window_SystemViewer.h"
#include "ApplicationManager.h"

#include <QLocale>
#include <QTranslator>
#include <QSurfaceFormat>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "ShipboardTools_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setSamples(8);
    QSurfaceFormat::setDefaultFormat(format);

    ApplicationManager app;
    app.showSystemViewer();

    //Window_SystemViewer glWin;
    //glWin.show();

    //Launcher w;
    //w.show();
    return a.exec();
}
