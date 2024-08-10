#ifndef DIALOG_SHIPSELECTION_H
#define DIALOG_SHIPSELECTION_H

#include <QDialog>

namespace Ui {
class Dialog_ShipSelection;
}

class ApplicationManager;
class QButtonGroup;

class Dialog_ShipSelection : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_ShipSelection(QWidget *parent = nullptr);
    ~Dialog_ShipSelection();
    void setApplication(ApplicationManager *a);

    std::string getShipNameFromFile(std::string file);

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::Dialog_ShipSelection *ui;
    QButtonGroup *group;
    ApplicationManager *app;
};

#endif // DIALOG_SHIPSELECTION_H
