#ifndef GLOBALS_H
#define GLOBALS_H

#include <iostream>
#include <string>
#include <QJsonObject>

namespace global {
    std::string path();

    QJsonObject openJSON(QString path);

    std::vector<std::string> getAllJSONFiles(std::string path);
}
#endif // GLOBALS_H
