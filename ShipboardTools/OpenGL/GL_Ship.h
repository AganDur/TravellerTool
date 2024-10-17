#ifndef GL_SHIP_H
#define GL_SHIP_H

#include "GL_Unique.h"

class GL_Ship : public GL_Unique {

public:
    GL_Ship(std::string file, std::string name, std::string texture, QVector3D position);

private:
    std::string name;

    bool active = false;

/*-----------------------*
 *   OPENGL PARAMETERS   *
 *-----------------------*/
private:
    GLint positionAttribute = -1, normalAttribute = -1 , textureCoordinatesAttribute = -1;
    GLint projectionViewMatrixUniform = -1, modelMatrixUniform = -1, ambientLightUniform = -1, diffuseLightUniform=-1, colorUniform=-1, lightPositionUniform=-1;
    GLint normalMatrixUniform = -1, cameraPositionUniform = -1;

    QVector3D position = QVector3D();

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

    void render(QMatrix4x4 projectionViewMatrix, QVector3D ambientLight, QVector3D diffuseLight,
                QVector3D lightPosition=QVector3D(0,0,0), QVector3D cameraPosition=QVector3D(0,0,0)) override;

    void setActivate(bool active);
};

#endif // GL_SHIP_H
