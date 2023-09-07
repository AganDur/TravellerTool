#ifndef GL_SYSTEMVIEWERWIDGET_H
#define GL_SYSTEMVIEWERWIDGET_H

#include "Gl_Widget.h"

#include <QMatrix4x4>
#include <QElapsedTimer>
#include <QTimer>
#include <QOpenGLFunctions>

class ApplicationManager;
class GL_Camera;
class GL_Object;

class GL_SystemViewerWidget : public GL_Widget, protected QOpenGLFunctions {
/*------------------*
 *   CONSTRUCTORS   *
 *------------------*/
public:
    GL_SystemViewerWidget(QWidget *parent, std::string systemName);

/*----------------------*
 *   WIDGET VARIABLES   *
 *----------------------*/
private:
    ApplicationManager *application;

    int widgetWidth, widgetHeight;

    QPoint globalCenterCoordinates;
    bool attachMouse = false;
    QPointF lastMousePosition;
    bool firstMouse = true;

    std::string system;


/*----------------------*
 *   OPENGL VARIABLES   *
 *----------------------*/
private:
    const float speedValues[12] = {0.01, 0.05, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1};

    bool isInitialized = false;

    int m_frame = 0;

    QMatrix4x4 view;
    QMatrix4x4 projection;
    GL_Camera *camera;

    int orbitingSpeedIndex = 0;
    float orbitingSpeed = 0.01;

    std::vector<GL_Object*> models;

    QVector3D ambientLight = QVector3D(1.0f, 1.0f, 1.0f);
    float ambientIntensity = 0.3f;

    std::vector<GLfloat> planetVertices;
    std::vector<GLfloat> starVertices;
    std::vector<unsigned int> sphereIndices;

    qint64 currentFrame = 0;
    qint64 lastFrame = 0;
    QElapsedTimer elapsedTimer;
    QTimer timer, timer2;

/*-----------------------*
 *   CONTROL FUNCTIONS   *
 *-----------------------*/
public:
    void keyPress();
    void timeKeyPress();
    void mouseMoveEvent(QMouseEvent *e) override;
    void mousePressEvent(QMouseEvent *e) override;
    void leaveEvent(QEvent *e) override;

    void updateData(std::string file);
    void changeMousePosition() override ;

    bool isAttachMouse() override;

/*----------------------*
 *   OPENGL FUNCTIONS   *
 *----------------------*/
public:
    // FUNCTIONS FROM GL_WIDGET:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;

    // OWN FUNCTIONS
    void setApp(ApplicationManager *a);
    void initialize(); //
    void initSphere(); //

    void render();
};

#endif // GL_SYSTEMVIEWERWIDGET_H
