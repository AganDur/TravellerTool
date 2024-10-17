#ifndef GLOBALDATA_H
#define GLOBALDATA_H

#include "Globals.h"

#include <iostream>
#include <string>
#include <vector>

class GlobalData {
public:
    static bool gmMode;
    static std::vector<std::string> paths;
    static std::string path;
};

bool GlobalData::gmMode = false;
std::vector<std::string> GlobalData::paths = std::vector<std::string>();
std::string GlobalData::path = global::path();

#endif // GLOBALDATA_H
