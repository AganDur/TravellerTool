#ifndef GL_PLANET_H
#define GL_PLANET_H

#include "GL_Unique.h"
#include "GL_Orbit.h"

#include <string>
#include <vector>

class GL_Planet: public GL_Unique {
/*------------------*
 *   CONSTRUCTORS   *
 *------------------*/
public:
    GL_Planet(std::vector<GLfloat> vertices, std::vector<unsigned int> indices, float size, GL_Orbit orbit, std::string name, std::string uwp);
    ~GL_Planet();

/*-----------------------*
 *   PLANET PARAMETERS   *
 *-----------------------*/
private:
    GL_Orbit planetaryOrbit;
    float distanceFromSun;
    float pitchAngle=0;

    float size;
    std::string name;
    std::string UWP;

/*-----------------------*
 *   OPENGL PARAMETERS   *
 *-----------------------*/
private:
    GLint positionAttribute = -1, normalAttribute = -1 , textureCoordinatesAttribute = -1;
    GLint projectionViewMatrixUniform = -1, modelMatrixUniform = -1, ambientLightUniform = -1, diffuseLightUniform=-1, colorUniform=-1, lightPositionUniform=-1;
    GLint normalMatrixUniform = -1;

    int nb_frames;

/*----------------------*
 *   GETTER FUNCTIONS   *
 *----------------------*/
private:
    QMatrix4x4 getModelMatrix();

/*----------------------*
 *   OPENGL FUNCTIONS   *
 *----------------------*/
public:
    void compileShaders(std::string vertexShaderName, std::string fragmentShaderName) override;
    void render(QMatrix4x4 projectionViewMatrix, QVector3D ambientLight, QVector3D diffuseLight) override;
    void updateTime(double timeRatio) override;
};

#endif // GL_PLANET_H
