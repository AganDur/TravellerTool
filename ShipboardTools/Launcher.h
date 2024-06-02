#ifndef LAUNCHER_H
#define LAUNCHER_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Launcher; }
QT_END_NAMESPACE

class ApplicationManager;

class Launcher : public QMainWindow {
    Q_OBJECT

public:
    Launcher(QWidget *parent = nullptr);
    ~Launcher();

    void setApplicationManager(ApplicationManager *a);

private slots:
    void on_SectorMapButton_clicked();

    void on_optionButton_clicked();

private:
    Ui::Launcher *ui;

    ApplicationManager *app;
};
#endif // LAUNCHER_H
