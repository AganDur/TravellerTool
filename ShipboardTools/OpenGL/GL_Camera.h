#ifndef GL_CAMERA_H
#define GL_CAMERA_H

#include <QOpenGLFunctions>
#include <QVector3D>

class GL_Camera: protected QOpenGLFunctions {
public:
    GL_Camera();

    void setPosition(QVector3D pos);
    void setDirection(QVector3D dir);
    void setPitch(float p);
    void setYaw(float y);
    void setZoom(float z);

    void addPitch(float p);
    void addYaw(float y);
    void addZoom(float z);

    void reset();

    void moveRight(float speed);
    void moveForward(float speed);
    void moveUp(float speed);

    void calculateVectors();

    QVector3D getPosition();
    QVector3D getDirection();

    float getPitch();
    float getYaw();
    float getZoom();

    QMatrix4x4 getView();

private:
    QVector3D position;
    QVector3D direction;
    constexpr static QVector3D worldUp{0.0f, 1.0f, 0.0f};

    float pitch = 0.0f, yaw = -90.0f, zoom=45.0f;
    QVector3D right;
};

#endif // GL_CAMERA_H
