#ifndef GL_INSTANCED_H
#define GL_INSTANCED_H

#include "GL_Object.h"

class GL_Instanced : public GL_Object {
/*------------------*
 *   CONSTRUCTORS   *
 *------------------*/
public:
    GL_Instanced();

/*------------------------*
 *   OPEN GL PARAMETERS   *
 *------------------------*/
protected:
    std::vector<QVector3D> translate, scale;
    std::vector<QMatrix4x4> rotate;
    std::vector<QVector4D> color;

    int numberOfInstances;

/*-----------------------*
 *   OPEN GL FUNCTIONS   *
 *-----------------------*/
public:
    //void render() override;
};

#endif // GL_INSTANCED_H
