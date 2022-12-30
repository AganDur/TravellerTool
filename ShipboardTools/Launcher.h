#ifndef LAUNCHER_H
#define LAUNCHER_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Launcher; }
QT_END_NAMESPACE

class Launcher : public QMainWindow
{
    Q_OBJECT

public:
    Launcher(QWidget *parent = nullptr);
    ~Launcher();

private:
    Ui::Launcher *ui;
};
#endif // LAUNCHER_H
