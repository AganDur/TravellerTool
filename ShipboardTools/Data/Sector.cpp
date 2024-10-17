#include "Sector.h"
#include "System.h"
#include "Subsector.h"

#include "Graphics/Hexagon.h"

#include <array>

Sector::Sector(std::string filename, std::string name, int x, int y){
    this->fileName = filename;
    this->name = name;
    this->x = x;
    this->y = y;

}

std::string Sector::getName(){
    return this->name;
}

std::string Sector::getFileName(){
    return this->fileName;
}

int Sector::getX() {
    return this->x;
}

int Sector::getY() {
    return this->y;
}

System *Sector::getSystem(int systemX, int systemY){
    std::array<int, 2> k = {systemX, systemY};
    auto sysIterator = this->systems.find(k);

    System *sys = nullptr;
    if(sysIterator != this->systems.end()){
        //name = sysIterator->second->getName();
        sys = sysIterator->second;
    }

    return sys;
}

bool Sector::getLoaded(){
    return this->loaded;
}

bool Sector::getHidden(){
    return this->hidden;
}

void Sector::setSystems(std::map<std::array<int, 2>, System *> systems){
    this->systems = systems;
}

void Sector::setSubsector(Subsector *sub){
    if(this->subsectors.size() < 16){
        this->subsectors.push_back(sub);
    }
    else {
        this->subsectors.at(sub->getIndex()) = sub;
    }
}

void Sector::setLoaded(bool load){
    this->loaded = load;
}

void Sector::setHidden(bool hide){
    this->hidden = hide;

    // Go through all Systems and hide/show them
    for(auto it = systems.begin() ; it!=systems.end() ; ++it){
        it->second->getHexagon()->setVisible(!hide);
    }
}

/*
std::vector<int[2]> Sector::getSystemsAtDistance(int start[], int distance){
    std::vector<int[2]> hexPositions;

    int currentPosition[2];
    currentPosition[0] = start[0];
    currentPosition[1] = start[1];

    hexPositions.push_back(currentPosition);

    for(int i=0;i<6;i++){
        int xIncrement = 0;
        if(i==0 || i==5) xIncrement = 1;
        else if(i==2 || i==3) xIncrement = -1;

        for(int j=0 ; j<distance ; j++){
            switch(i){
                case 0:
                    if(currentPosition[0]%2!=0) currentPosition[1] -= 1;
                    break;
                case 1:
                    currentPosition[1]-=1;
                    break;
                case 2:
                    if(currentPosition[0]%2!=0) currentPosition[1] -= 1;
                    break;
                case 3:
                    if(currentPosition[0]%2 == 0) currentPosition[1] += 1;
                    break;
                case 4:
                    currentPosition[1] += 1;
                    break;
                case 5:
                    if(currentPosition[0]%2 == 0) currentPosition[1] += 1;
                    break;
            }

            currentPosition[0] += xIncrement;
            hexPositions.push_back(currentPosition);
        }
    }

    return hexPositions;
}
*/

