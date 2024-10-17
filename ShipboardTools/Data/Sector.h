#ifndef SECTOR_H
#define SECTOR_H

#include <stdlib.h>
#include <string>
#include <map>
#include <vector>


class System;
class Subsector;

class Sector {
public:
    Sector(std::string filename, std::string name, int x, int y);

    std::string getName();
    std::string getFileName();
    int getX();
    int getY();
    System* getSystem(int systemX, int systemY);
    bool getLoaded();
    bool getHidden();


    void setSystems(std::map<std::array<int,2>, System*> systems);
    void setSubsector(Subsector *sub);
    void setLoaded(bool load);
    void setHidden(bool hide);

    std::vector<Subsector*> getSubsectors() { return subsectors; }

    //std::vector<int[2]> getSystemsAtDistance(int start[], int distance);

private:
    std::string name;
    std::string fileName;
    std::vector<Subsector*> subsectors;
    std::map<std::array<int,2>, System*> systems;
    int x, y;

    bool loaded = false;
    bool hidden = false;

    Sector *trailingSector, *spinwardSector, *rimwardSector, *corewardSector;
};

#endif // SECTOR_H
