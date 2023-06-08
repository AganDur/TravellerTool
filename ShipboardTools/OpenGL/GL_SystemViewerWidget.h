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

public:
    GL_SystemViewerWidget(QWidget *parent, std::string systemName);

    // FUNCTIONS FROM GL_WIDGET:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;

    // OWN FUNCTIONS
    void setApp(ApplicationManager *a){ this->application = a;} //
    void initialize(); //
    void initSphere(); //

    void render();

    void keyPress();
    void mouseMoveEvent(QMouseEvent *e) override;
    void mousePressEvent(QMouseEvent *e) override;

    void updateData(std::string file);

private:
    bool isInitialized = false;

    QPoint globalCenterCoordinates;
    bool attachMouse = false;

    void changeMousePosition();

    int m_frame = 0;
    std::string system;

    QMatrix4x4 view;
    QMatrix4x4 projection;

    GL_Camera *camera;
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
    QTimer timer;

    ApplicationManager *application;

    QPointF lastMousePosition;
    bool firstMouse = true;

    int widgetWidth, widgetHeight;
};

#endif // GL_SYSTEMVIEWERWIDGET_H
