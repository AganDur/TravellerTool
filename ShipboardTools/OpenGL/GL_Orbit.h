#ifndef GL_ORBIT_H
#define GL_ORBIT_H

#include "GL_Object.h"

class GL_Orbit{

/*------------------*
 *   CONSTRUCTORS   *
 *------------------*/
public:
    GL_Orbit(QVector3D center, float semiMajor, float semiMinor, int rotation);
    GL_Orbit(GL_Orbit &o);


/*----------------------*
 *   ORBIT PARAMETERS   *
 *----------------------*/
private:
    QVector3D center;
    float semiMajor;
    float semiMinor;
    float eccentricity;
    float distanceToFocus;
    float rotation;

    QVector3D focus1;
    QVector3D focus2;    

    float completeSurface;
    float lastAngle = 0;
    float orbitalPeriod;

/*-----------------------*
 *   OPENGL PARAMETERS   *
 *-----------------------*/
private:
    std::vector<float> vertices;
    QVector3D color;

    QOpenGLShaderProgram *shaderProgram = nullptr;
    QOpenGLVertexArrayObject VAO;
    QOpenGLBuffer *VBO = nullptr;

    GLint m_positionAttribute=0, m_projectionMatrixUniform=0, m_colorUniform=0;

/*----------------------*
 *   GETTER FUNCTIONS   *
 *----------------------*/
public:
    float getSemiMinor();
    float getSemiMajor();

    float getX_NoAngle();
    float getX_Angle(float angle);
    float getX_CurrentAngle();

    float getY_NoAngle();
    float getY_Angle(float angle);
    float getY_CurrentAngle();


/*----------------------*
 *   SETTER FUNCTIONS   *
 *----------------------*/
private:
    void prepare();

public:
    void setColor(QVector3D c){
        this->color = c;
    }
    void increaseAngle(double timeRatio);

/*----------------------*
 *   OPENGL FUNCTIONS   *
 *----------------------*/
public:
    void render(QMatrix4x4 projectionViewMatrix);

};

#endif // GL_ORBIT_H
