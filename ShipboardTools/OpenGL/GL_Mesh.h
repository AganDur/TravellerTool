#ifndef GL_MESH_H
#define GL_MESH_H

#include <vector>
#include <string>

#include <QOpenGLFunctions>


class GL_Mesh{
public:
    GL_Mesh(std::string name, std::vector<GLfloat> vert, std::vector<unsigned int> ind);

private:
    std::string meshName;
    std::vector<GLfloat> vertices;
    std::vector<unsigned int> indices;

public:
    std::string getName() { return meshName; }
    std::vector<GLfloat> getVertices() { return vertices; }
    std::vector<unsigned int> getIndices() { return indices; }
};

#endif // GL_MESH_H
