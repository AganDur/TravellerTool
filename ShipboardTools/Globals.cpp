#include <string>
#include <filesystem>
#include <iostream>
#include <windows.h>

#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>
#include <QDir>

#include "Globals.h"
#include "GlobalData.h"

namespace fs = std::filesystem;

namespace global {
    std::string path(){
        /*--------------------------*
         *   GET APPLICATION PATH   *
         *--------------------------*/
        TCHAR szEXEPath[2048];
        std::string actualPath="";
        GetModuleFileName ( NULL, szEXEPath, 2048 );
        /* Prints the full path */
        for(int j=0; szEXEPath[j]!=0; j++)
        {
            actualPath+=szEXEPath[j];
        }
        size_t sub = actualPath.find_last_of("\\");
        std::string subT = actualPath.substr(0, sub+1);

        QString path = QString::fromStdString(subT);
        path.replace("\\","/");
        path.replace("//","/");

        return path.toStdString();
    }

    QJsonObject openJSON(QString path){
        QJsonObject root;

        // READ JSON FILE OF CURRENT SYSTEM
        QFile in(path);
        in.open(QIODevice::ReadOnly|QIODevice::Text);
        QByteArray data = in.readAll();

        QJsonParseError errorPtr;
        QJsonDocument document = QJsonDocument::fromJson(data, &errorPtr);
        if(document.isNull()){
            qDebug() << "Parse failed: ";
            qDebug() << errorPtr.errorString();
        }
        else {
            root = document.object();
        }
        return root;
    }

    std::vector<std::string> getAllJSONFiles(std::string path){
        std::vector<std::string> filenames;
        if(!folderExists(path)) return filenames;

        fs::directory_iterator it = fs::directory_iterator{path};

        for(const auto & entry : it){
            std::string fileName = entry.path().filename().string();
            std::string ext = fileName.substr(fileName.size()-5);
            if(ext == ".json"){
                std::string file= fileName.substr(0, fileName.size()-5);
                filenames.push_back(file);
            }
        }
        return filenames;
    }

    std::string dataPath() {
        GlobalData data;
        if(data.path.empty()) return path();
        return data.path;
    }

    std::vector<std::string> dataPaths() {
        GlobalData data;
        return data.paths;
    }

    void readSettings() {
        GlobalData data;

        QJsonObject root = openJSON(QString::fromStdString(path() + "settings.json"));

        if(root.empty()){
            data.paths.push_back(path());
            saveSettingsFile();
            return;
        }

        data.gmMode = root.value("gmMode").toBool(false);
        data.path = root.value("selectedLocation").toString().toStdString();

        qDebug() << root.value("dataLocations").toArray().size();
        qDebug() << data.path;

        for(auto location: root.value("dataLocations").toArray()){
            data.paths.push_back(location.toString("").toStdString());
        }
    }

    void saveSettingsFile() {
        GlobalData data;

        std::string filepath = path() + "settings.json";

        QJsonObject root;
        root.insert("gmMode", data.gmMode);
        root.insert("selectedLocation", QString::fromStdString(data.path));

        QJsonArray locs;
        for(std::string p : data.paths){
            locs.insert(0, QString::fromStdString(p));
        }
        root.insert("dataLocations", locs);

        QJsonDocument doc;
        doc.setObject(root);
        QByteArray bytes = doc.toJson(QJsonDocument::Indented);
        QFile f(QString::fromStdString(filepath));
        if(f.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Truncate)){
            QTextStream iStream(&f);
            iStream.setEncoding(QStringConverter::Utf8);
            iStream << bytes;
            f.close();
        }
        else {
            qDebug() << "Failed to open file";
        }
    }

    bool isGM() {
        GlobalData data;
        return data.gmMode;
    }

    void setPath(std::string path) {
        GlobalData data;
        data.path = path;
    }

    void setPaths(std::vector<std::string> paths){
        GlobalData data;
        data.paths = paths;
    }

    void setGM(bool gm){
        GlobalData data;
        data.gmMode = gm;
    }

    void addPath(std::string path){
        GlobalData data;
        data.paths.push_back(path);
    }

    void removePath(std::string path) {
        GlobalData data;

        auto iterator = std::find(data.paths.begin(), data.paths.end(), path);
        if(iterator!=data.paths.end()) data.paths.erase(iterator);
    }

    bool folderExists(std::string path){
        QDir folder = QDir(QString::fromStdString(path));
        return folder.exists();
    }

    bool getDarkMode(){
        GlobalData data;
        return data.darkMode;
    }
    void setDarkMode(bool mode){
        GlobalData data;
        data.darkMode=mode;
    }

}
