#include "GL_Mesh.h"

/*------------------*
 *   CONSTRUCTORS   *
 *------------------*/
GL_Mesh::GL_Mesh(std::string name, std::vector<GLfloat> vert, std::vector<unsigned int> ind){
    meshName = name;
    vertices = vert;
    indices = ind;
}

/*----------------------*
 *   GETTER FUNCTIONS   *
 *----------------------*/
std::string GL_Mesh::getName() {
    return meshName;
}
std::vector<GLfloat> GL_Mesh::getVertices() {
    return vertices;
}
std::vector<unsigned int> GL_Mesh::getIndices() {
    return indices;
}
