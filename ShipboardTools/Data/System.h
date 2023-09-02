#ifndef SYSTEM_H
#define SYSTEM_H

#include <stdlib.h>
#include <string>

class Sector;

class System{
public:
    System();
    System(std::string name, std::string uwp, std::string hexLocation);

    void setSector(Sector *s);

    std::string getName();
    std::string getUWP();
    std::string getHex();

    Sector* getSector();

private:
    std::string name;
    std::string uwp;
    std::string hexLocation;

    Sector *sector;
};

#endif // SYSTEM_H
