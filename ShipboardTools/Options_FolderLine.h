#ifndef OPTIONS_FOLDERLINE_H
#define OPTIONS_FOLDERLINE_H

#include <QHBoxLayout>
#include <QPushButton>
#include <QRadioButton>
#include <QWidget>

class Window_Options;

class Options_FolderLine : public QWidget {
public:
    Options_FolderLine(std::string location, bool deletable, bool check);

    void setWindow(Window_Options *w);

    std::string getLocation();
    bool isDeletable();

    void setChecked(bool check);
    QRadioButton* getRadio();

private:
    std::string location;
    bool deletable;

    QRadioButton *radio;
    QPushButton *deleteButton;

    Window_Options *window;
};

#endif // OPTIONS_FOLDERLINE_H
