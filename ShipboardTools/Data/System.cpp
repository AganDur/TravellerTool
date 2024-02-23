#include "System.h"

System::System(){
    this->name = "";
    this->uwp = "";
    this->hexLocation = "";
    this->tradeCode = "";
}

System::System(std::string name, std::string uwp, std::string hexLocation, std::string tradeCode){
    this->name = name;
    this->uwp = uwp;
    this->hexLocation = hexLocation;
    this->tradeCode = tradeCode;
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

Sector* System::getSector(){
    return this->sector;
}

Hexagon *System::getHexagon(){
    return this->graphicsHexagon;
}
