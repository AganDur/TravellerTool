#include "Options_FolderLine.h"
#include "Window_Options.h"

Options_FolderLine::Options_FolderLine(std::string location, bool deletable, bool check){
    this->setLayout(new QHBoxLayout());

    this->location=location;
    this->deletable=deletable;

    this->radio = new QRadioButton(QString::fromStdString(location));
    this->layout()->addWidget(radio);

    if(deletable){
        this->deleteButton = new QPushButton("Delete");
        connect(deleteButton, &QPushButton::clicked, [this]{
            this->window->deleteFolder(this);
            delete this;
        });
        this->layout()->addWidget(deleteButton);
    }

    radio->setChecked(check);
}

void Options_FolderLine::setWindow(Window_Options *w){
    this->window = w;
}

std::string Options_FolderLine::getLocation(){
    return this->location;
}

bool Options_FolderLine::isDeletable(){
    return deletable;
}

void Options_FolderLine::setChecked(bool check){
    this->radio->setChecked(check);
}

QRadioButton *Options_FolderLine::getRadio(){
    return radio;
}


