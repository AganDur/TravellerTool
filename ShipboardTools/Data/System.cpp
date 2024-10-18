#include "System.h"

System::System(){
    this->name = "";
    this->uwp = "";
    this->hexLocation = "";
    this->tradeCode = "";
    this->category = "";
}

System::System(std::string name, std::string hexLocation, std::vector<std::string> interests, std::string uwp, std::string tradeCode, std::string category){
    this->name = name;
    this->uwp = uwp;
    this->hexLocation = hexLocation;
    this->tradeCode = tradeCode;
    this->category = category;
    this->interests = interests;
}

void System::setSector(Sector *s){
    this->sector = s;
}

void System::setHexagon(Hexagon *hex){
    this->graphicsHexagon = hex;
}

std::string System::getName(){
    return this->name;
}

std::string System::getUWP(){
    return this->uwp;
}

std::string System::getHex(){
    return this->hexLocation;
}

std::string System::getTradeCode(){
    return this->tradeCode;
}

std::string System::getCategory(){
    return this->category;
}

std::vector<std::string> System::getInterests(){
    return this->interests;
}

int System::getNbInterests(){
    return this->interests.size();
}

std::string System::getInterest(int index){
    return this->interests.at(index);
}

Sector* System::getSector(){
    return this->sector;
}

Hexagon *System::getHexagon(){
    return this->graphicsHexagon;
}
