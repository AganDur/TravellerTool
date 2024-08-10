#ifndef GL_CAMERA_H
#define GL_CAMERA_H

#include <QOpenGLFunctions>
#include <QVector3D>

/*
 * @author Agan_Dur
 */

class GL_Camera: protected QOpenGLFunctions {
/*------------------*
 *   CONSTRUCTORS   *
 *------------------*/
public:
    GL_Camera();

/*---------------*
 *   VARIABLES   *
 *---------------*/
private:
    QVector3D originalPosition;
    QVector3D originalDirection;
    bool init = false;

    QVector3D position;
    QVector3D direction;
    constexpr static QVector3D worldUp{0.0f, 1.0f, 0.0f};

    float pitch = 0.0f, yaw = -90.0f, zoom=45.0f;
    QVector3D right;

/*----------------------*
 *   GETTER FUNCTIONS   *
 *----------------------*/
public:
    QVector3D getPosition();
    QVector3D getDirection();
    QMatrix4x4 getView();

    float getPitch();
    float getYaw();
    float getZoom();

/*----------------------*
 *   SETTER FUNCTIONS   *
 *----------------------*/
public:
    void setPosition(QVector3D pos);
    void setDirection(QVector3D dir);
    void setPitch(float p);
    void setYaw(float y);
    void setZoom(float z);
    void setInit(bool init);

/*-----------------------*
 *   CONTROL FUNCTIONS   *
 *-----------------------*/
public:
    void addPitch(float p);
    void addYaw(float y);
    void addZoom(float z);

    void moveRight(float speed);
    void moveForward(float speed);
    void moveUp(float speed);

    void reset();
    void calculateVectors();

};

#endif // GL_CAMERA_H
