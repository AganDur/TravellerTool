#ifndef GL_UNIQUE_H
#define GL_UNIQUE_H

#include "GL_Object.h"

class GL_Unique: public GL_Object {
/*------------------*
 *   CONSTRUCTORS   *
 *------------------*/
public:
    GL_Unique(std::string meshName, QVector3D color);
    GL_Unique(std::vector<GLfloat> vertices, std::vector<unsigned int> indices, QVector3D color);

    virtual ~GL_Unique();

/*------------------------*
 *   OPEN GL PARAMETERS   *
 *------------------------*/
protected:
    QVector3D translate, scale;
    QMatrix4x4 rotate;
    QVector3D color;

/*-----------------------*
 *   OPEN GL FUNCTIONS   *
 *-----------------------*/
public:
    void compileShaders(std::string vertexShaderName, std::string fragmentShaderName) override;
    QVector3D getColor() override;
    //virtual void render() override;
};

#endif // GL_UNIQUE_H
