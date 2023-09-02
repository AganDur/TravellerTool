#include <string>
#include <filesystem>
#include <iostream>
#include <windows.h>

#include <QJsonParseError>
#include <QJsonDocument>
#include <QFile>

#include "Globals.h"

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
        return subT;
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
            qDebug() << "Parse failed";
        }
        else {
            root = document.object();
        }
        return root;
    }

    std::vector<std::string> getAllJSONFiles(std::string path){
        fs::directory_iterator it = fs::directory_iterator{path};
        std::vector<std::string> filenames;

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
}
