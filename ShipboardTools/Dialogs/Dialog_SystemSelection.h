#ifndef DIALOG_SYSTEMSELECTION_H
#define DIALOG_SYSTEMSELECTION_H

#include <QDialog>

namespace Ui {
class Dialog_SystemSelection;
}

class ApplicationManager;

class Dialog_SystemSelection : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_SystemSelection(QWidget *parent = nullptr);
    ~Dialog_SystemSelection();

    void setApplication(ApplicationManager *a);

private:
    void loadSystems();

private slots:
    void on_selectorBox_currentIndexChanged(int index);

    void on_acceptButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::Dialog_SystemSelection *ui;
    ApplicationManager *app;
};

#endif // DIALOG_SYSTEMSELECTION_H
