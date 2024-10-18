#ifndef SYSTEM_H
#define SYSTEM_H

#include <stdlib.h>
#include <string>
#include <vector>

class Sector;
class Hexagon;

class System{
public:
    System();
    System(std::string name, std::string hexLocation, std::vector<std::string> interests, std::string uwp="", std::string tradeCode="", std::string category="");

    void setSector(Sector *s);
    void setHexagon(Hexagon *hex);

    std::string getName();
    std::string getUWP();
    std::string getHex();
    std::string getTradeCode();
    std::string getCategory();
    std::vector<std::string> getInterests();
    int getNbInterests();
    std::string getInterest(int index);

    Sector* getSector();
    Hexagon* getHexagon();

private:
    std::string name;
    std::string uwp;
    std::string hexLocation;
    std::string tradeCode;
    std::string category;
    std::vector<std::string> interests;

    Hexagon *graphicsHexagon;

    Sector *sector;
};

#endif // SYSTEM_H
