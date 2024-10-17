#ifndef WINDOW_OPTIONS_H
#define WINDOW_OPTIONS_H

#include <QButtonGroup>
#include <QHBoxLayout>
#include <QMainWindow>
#include <QPushButton>

namespace Ui {
class Window_Options;
}

class Options_FolderLine;

class Window_Options : public QMainWindow {
    Q_OBJECT

public:
    explicit Window_Options(QWidget *parent = nullptr);
    ~Window_Options();

    void deleteFolder(Options_FolderLine *folder);

private slots:
    void on_saveButton_clicked();

    void on_cancelButton_clicked();

    void on_newFolderButton_clicked();

private:
    Ui::Window_Options *ui;
    std::vector<std::string> dataLocations;

    QButtonGroup buttonGroup;

};

#endif // WINDOW_OPTIONS_H
