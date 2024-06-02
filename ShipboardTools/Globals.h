#ifndef GLOBALS_H
#define GLOBALS_H

#include <iostream>
#include <string>
#include <QJsonObject>


namespace global {
    std::string path();
    std::string dataPath();
    void setPath(std::string path);

    std::vector<std::string> dataPaths();
    void setPaths(std::vector<std::string> paths);
    void addPath(std::string path);
    void removePath(std::string path);

    bool isGM();
    void setGM(bool gm);

    bool folderExists(std::string path);

    QJsonObject openJSON(QString path);

    void readSettings();

    std::vector<std::string> getAllJSONFiles(std::string path);

    void saveSettingsFile();
}

#endif // GLOBALS_H
