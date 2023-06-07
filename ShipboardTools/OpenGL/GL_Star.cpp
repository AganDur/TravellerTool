#include "GL_Star.h"

GL_Star::GL_Star(std::vector<GLfloat> vertices, std::vector<unsigned int> indices, std::string stellarClass, float radius, float mass, QVector3D color) : GL_Unique{"vert", "frag", vertices, indices, color}{

}

GL_Star::~GL_Star(){

}

void GL_Star::compileShaders(std::string vertexShaderName, std::string fragmentShaderName){
    GL_Unique::compileShaders(vertexShaderName, fragmentShaderName);
}
