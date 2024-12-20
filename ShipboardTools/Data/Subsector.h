#ifndef SUBSECTOR_H
#define SUBSECTOR_H

#include <stdlib.h>
#include <string>

class Subsector {
public:
    Subsector(std::string name, int index);

    int getIndex();
    std::string getName(){ return name; }

private:
    int index;
    std::string name;
};

#endif // SUBSECTOR_H
