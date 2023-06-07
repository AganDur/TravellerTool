#ifndef GL_ORBIT_H
#define GL_ORBIT_H

#include "GL_Object.h"

class GL_Orbit : public GL_Object
{
public:
    GL_Orbit(QVector3D center, float semiMajor, float semiMinor, int rotation);
    GL_Orbit(GL_Orbit &o);

    void setColor(QVector3D c){
        this->color = c;
    }

private:
    QVector3D center;
    float semiMajor;
    float semiMinor;
    float eccentricity;
    float distanceToFocus;
    float rotation;

    QVector3D focus1;
    QVector3D focus2;

    QVector3D color;

    float completeSurface;
    float lastAngle = 0;
    float orbitalPeriod;
    float prepared = false;

public:
    float getX_NoAngle();
    float getX_Angle(float angle);
    float getY_NoAngle();
    float getY_Angle(float angle);
    float getX_CurrentAngle();
    float getY_CurrentAngle();

    void increaseAngle(double timeRatio);

private:
    GLint m_positionAttribute=0, m_matrixUniform=0, m_colorUniform=0;

public:
    void render(QMatrix4x4 matrix);

};

#endif // GL_ORBIT_H
