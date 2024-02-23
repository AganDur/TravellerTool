#ifndef SYSTEM_H
#define SYSTEM_H

#include <stdlib.h>
#include <string>

class Sector;
class Hexagon;

class System{
public:
    System();
    System(std::string name, std::string uwp, std::string hexLocation, std::string tradeCode);

    void setSector(Sector *s);
    void setHexagon(Hexagon *hex);

    std::string getName();
    std::string getUWP();
    std::string getHex();
    std::string getTradeCode();

    Sector* getSector();
    Hexagon* getHexagon();

private:
    std::string name;
    std::string uwp;
    std::string hexLocation;
    std::string tradeCode;

    Hexagon *graphicsHexagon;

    Sector *sector;
};

#endif // SYSTEM_H
