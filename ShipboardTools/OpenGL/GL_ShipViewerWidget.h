#ifndef GL_SHIPVIEWERWIDGET_H
#define GL_SHIPVIEWERWIDGET_H

#include <Windows.h>
#include <WinUser.h>

#include "Gl_Widget.h"

#include <QMatrix4x4>
#include <QElapsedTimer>
#include <QTimer>
#include <QOpenGLFunctions>

class ApplicationManager;
class GL_Camera;
class GL_Ship;
class Window_ShipViewer;

class GL_ShipViewerWidget : public GL_Widget, protected QOpenGLFunctions {
public:
    GL_ShipViewerWidget(QWidget *parent, std::string shipName);

private:
    ApplicationManager *application;

    int widgetWidth, widgetHeight;

    QPoint globalCenterCoordinates;
    bool attachMouse = false;
    QPointF lastMousePosition;
    bool firstMouse = true;

    std::string shipFile, shipName;

private:
    bool isInitialized = false;

    QMatrix4x4 view, projection;
    GL_Camera *camera;

    std::vector<GL_Ship*> models;

    QVector3D ambientLight = QVector3D(1.0f, 1.0f, 1.0f);
    float ambientIntensity = 0.2f;
    QVector3D diffuseLight = QVector3D(.7f, .7f, .7f);
    QVector3D lightPosition = QVector3D(500, 0, 500);

    qint64 currentFrame = 0;
    qint64 lastFrame = 0;
    QElapsedTimer elapsedTimer;
    QTimer timer;

    Window_ShipViewer *window;

public:
    void setWindow(Window_ShipViewer *w);

    void keyPress();
    void mouseMoveEvent(QMouseEvent *e) override;
    void mousePressEvent(QMouseEvent *e) override;
    void leaveEvent(QEvent *e) override;

    std::vector<std::string> updateData(std::string file);
    void changeMousePosition() override ;

    bool isAttachMouse() override;

    void changeComponentActivation(std::string, bool selected);

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
    void initialize();
    void render();

    std::string getShipName() { return this->shipName; }

};

#endif // GL_SHIPVIEWERWIDGET_H
