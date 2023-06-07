#ifndef GL_STAR_H
#define GL_STAR_H

#include "GL_Unique.h"

#include <stdlib.h>
#include <vector>
#include <string>

class GL_Star: public GL_Unique {
/*------------------*
 *   CONSTRUCTORS   *
 *------------------*/
public:
    GL_Star(std::vector<GLfloat> vertices, std::vector<unsigned int> indices, std::string stellarClass, float radius, float mass, QVector3D color);
    ~GL_Star();

/*------------------------*
 *   OPEN GL PARAMETERS   *
 *------------------------*/
private:

/*------------------------*
 *   OPEN GL PARAMETERS   *
 *------------------------*/
public:
    void compileShaders(std::string vertexShaderName, std::string fragmentShaderName) override;

};

#endif // GL_STAR_H
