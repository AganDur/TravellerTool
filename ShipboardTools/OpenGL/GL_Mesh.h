#ifndef GL_MESH_H
#define GL_MESH_H

#include <vector>
#include <string>

#include <QOpenGLFunctions>


class GL_Mesh{
/*------------------*
 *   CONSTRUCTORS   *
 *------------------*/
public:
    GL_Mesh(std::string name, std::vector<GLfloat> vert, std::vector<unsigned int> ind);

/*-----------------------*
 *   OPENGL PARAMETERS   *
 *-----------------------*/
private:
    std::string meshName;
    std::vector<GLfloat> vertices;
    std::vector<unsigned int> indices;

/*----------------------*
 *   GETTER FUNCTIONS   *
 *----------------------*/
public:
    std::string getName();
    std::vector<GLfloat> getVertices();
    std::vector<unsigned int> getIndices();
};

#endif // GL_MESH_H
