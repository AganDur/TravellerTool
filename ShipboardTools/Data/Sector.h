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
    Sector(std::string name, int x, int y);

    std::string getName();
    int getX();
    int getY();
    System* getSystem(int systemX, int systemY);

    void setSystems(std::map<std::array<int,2>, System*> systems);
    void setSubsector(Subsector *sub);

    //std::vector<int[2]> getSystemsAtDistance(int start[], int distance);

private:
    std::string name;
    std::vector<Subsector*> subsectors;
    std::map<std::array<int,2>, System*> systems;
    int x, y;

    Sector *trailingSector, *spinwardSector, *rimwardSector, *corewardSector;
};

#endif // SECTOR_H
