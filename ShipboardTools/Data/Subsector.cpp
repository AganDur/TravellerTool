#include "Subsector.h"

Subsector::Subsector(std::string name, int index) {
    this->name = name;
    this->index = index;
}

int Subsector::getIndex(){
    return this->index;
}
