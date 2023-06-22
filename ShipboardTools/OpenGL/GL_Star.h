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
    float size;
    float mass;

    GLint positionAttribute = -1, textureCoordinatesAttribute = -1;
    GLint projectionViewMatrixUniform = -1, modelMatrixUniform = -1, colorUniform=-1;

    QMatrix4x4 getModelMatrix();

/*------------------------*
 *   OPEN GL PARAMETERS   *
 *------------------------*/
public:
    void compileShaders(std::string vertexShaderName, std::string fragmentShaderName) override;

    void render(QMatrix4x4 projectionViewMatrix, QVector3D ambientLight, QVector3D diffuseLight);

};

#endif // GL_STAR_H
