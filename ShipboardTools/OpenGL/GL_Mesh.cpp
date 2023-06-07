#include "GL_Mesh.h"

GL_Mesh::GL_Mesh(std::string name, std::vector<GLfloat> vert, std::vector<unsigned int> ind){
    meshName = name;
    vertices = vert;
    indices = ind;
}
