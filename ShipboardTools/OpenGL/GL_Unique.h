#ifndef GL_UNIQUE_H
#define GL_UNIQUE_H

#include "GL_Object.h"

class GL_Unique: public GL_Object {
/*------------------*
 *   CONSTRUCTORS   *
 *------------------*/
public:
    GL_Unique();
    virtual ~GL_Unique();

/*------------------------*
 *   OPEN GL PARAMETERS   *
 *------------------------*/
protected:
    QVector3D translate, scale;
    QMatrix4x4 rotate;
    QVector4D color;

/*-----------------------*
 *   OPEN GL FUNCTIONS   *
 *-----------------------*/
public:
    //virtual void render() override;
};

#endif // GL_UNIQUE_H
