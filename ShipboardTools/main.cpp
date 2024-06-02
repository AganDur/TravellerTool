#include <QApplication>
#include "ApplicationManager.h"
#include "Globals.h"

#include <QLocale>
#include <QTranslator>
#include <QSurfaceFormat>

int main(int argc, char *argv[])
{
    //QApplication a(argc, argv);
    ApplicationManager app(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "ShipboardTools_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            app.installTranslator(&translator);
            break;
        }
    }

    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setSamples(8);
    QSurfaceFormat::setDefaultFormat(format);

    global::readSettings();

    app.showLauncher();

    //Window_SystemViewer glWin;
    //glWin.show();

    //Launcher w;
    //w.show();
    return app.exec();
}
