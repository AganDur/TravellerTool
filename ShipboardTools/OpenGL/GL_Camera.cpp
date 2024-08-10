#include "GL_Camera.h"

#include <QMatrix4x4>

/*
 * @author Agan_Dur
 */

/*--------------------*
 *   TOOL FUNCTIONS   *
 *--------------------*/
float DegToRad(float d){
    return d*(3.14/180);
}

/*------------------*
 *   CONSTRUCTORS   *
 *------------------*/
GL_Camera::GL_Camera(): position(), direction(), pitch(0.0f), yaw(-90.0f), zoom(45.0f), right() {
}

/*----------------------*
 *   GETTER FUNCTIONS   *
 *----------------------*/
QVector3D GL_Camera::getPosition(){
    return position;
}
QVector3D GL_Camera::getDirection(){
    return direction;
}
float GL_Camera::getPitch(){
    return pitch;
}
float GL_Camera::getYaw(){
    return yaw;
}
float GL_Camera::getZoom(){
    return zoom;
}

/**
 * Returns the View matrix linked to the camera,
 * based on the current position and direction vectors.
 */
QMatrix4x4 GL_Camera::getView(){
    QMatrix4x4 v;
    v.lookAt(position, position+direction, worldUp);
    return v;
}

/*----------------------*
 *   SETTER FUNCTIONS   *
 *----------------------*/
void GL_Camera::setPosition(QVector3D pos) {
    position = pos;
    if(!init) originalPosition = pos;
}
void GL_Camera::setDirection(QVector3D dir){
    direction = dir;
    if(!init) originalDirection = dir;
    calculateVectors();
}
void GL_Camera::setPitch(float p){
    pitch = p;
    if(pitch < -89) pitch = -89;
    if(pitch > 89) pitch = 89;
    calculateVectors();
}
void GL_Camera::setYaw(float y){
    yaw = y;
    calculateVectors();
}
void GL_Camera::setZoom(float z){
    zoom = z;
    if(zoom < 1) zoom = 1;
    if(zoom > 45) zoom = 45;
}

void GL_Camera::setInit(bool init){
    this->init = init;
}

/*-----------------------*
 *   CONTROL FUNCTIONS   *
 *-----------------------*/
void GL_Camera::addPitch(float p){
    pitch += p;
    if(pitch < -89) pitch = -89;
    if(pitch > 89) pitch = 89;
    calculateVectors();
}
void GL_Camera::addYaw(float y){
    yaw += y;
    calculateVectors();
}
void GL_Camera::addZoom(float z){
    zoom += z;
    if(zoom < 1) zoom = 1;
    if(zoom > 45) zoom = 45;
}

void GL_Camera::moveRight(float speed){
    position += speed * right;
}
void GL_Camera::moveForward(float speed){
    position += speed * direction;
}
void GL_Camera::moveUp(float speed){
    position += speed * worldUp;
}

/**
 * Function handling hard reset of all camera variables,
 * incluuding position, direction, zoom, pitch and yaw.
 */
void GL_Camera::reset(){
    setPosition(originalPosition);
    setDirection(originalDirection);
    zoom = 45.0f;
    pitch = 0.0f;
    yaw=-90.0f;
}

/**
 * Function handling calculating the vectors used by the camera,
 * based on the current pitch and yaw values and world up direction.
 */
void GL_Camera::calculateVectors(){
    QVector3D dir;

    dir.setX(cos(DegToRad(yaw)) * cos(DegToRad(pitch)));
    dir.setY(sin(DegToRad(pitch)));
    dir.setZ(sin(DegToRad(yaw)) * cos(DegToRad(pitch)));
    direction = dir;
    direction.normalize();

    right = QVector3D::crossProduct(worldUp, direction);
    right.normalize();
}
