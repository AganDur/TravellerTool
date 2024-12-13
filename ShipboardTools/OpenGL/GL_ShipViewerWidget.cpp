#include "GL_ShipViewerWidget.h"

#include "GL_Camera.h"
#include "GL_Ship.h"
#include "../Globals.h"
#include "../ApplicationManager.h"
#include "Window_ShipViewer.h"

#include <QJsonArray>
#include <QMouseEvent>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

GL_ShipViewerWidget::GL_ShipViewerWidget(QWidget *parent, std::string shipName) : GL_Widget(parent){
    shipFile = shipName;
}

void GL_ShipViewerWidget::setWindow(Window_ShipViewer *w){
    this->window = w;
}

void GL_ShipViewerWidget::keyPress(){
    // Escape
    if(GetAsyncKeyState(0x1B) & 0x100000){
        //application->closeGL();
        attachMouse = false;
        this->setMouseTracking(false);
        this->releaseMouse();
        this->setCursor(Qt::ArrowCursor);
        return;
    }

    // R Key
    if(GetAsyncKeyState(0x52) & 0x100000){
        camera->reset();
        return;
    }

    // Q Key
    if(GetAsyncKeyState(0x51) & 0x100000){
        camera->moveRight(1);
    }
    // D Key
    else if(GetAsyncKeyState(0x44) & 0x100000){
        camera->moveRight(-1);
    }

    // Z Key
    if(GetAsyncKeyState(0x5A) & 0x100000){
        camera->moveForward(1);
    }
    // S Key
    else if(GetAsyncKeyState(0x53) & 0x100000){
        camera->moveForward(-1);
    }

    // E Key
    if(GetAsyncKeyState(0x45) & 0x100000){
        camera->moveUp(1);
    }
    // A Key
    else if(GetAsyncKeyState(0x41) & 0x100000){
        camera->moveUp(-1);
    }
}

// If the widget is currently tracking the mouse, this event is called on mouse movement
// It is used to calculate the new mouse position and revert the mouse to the center of the Widget
// allowing the control of the camera based on mouse movements in the openGL context.
void GL_ShipViewerWidget::mouseMoveEvent(QMouseEvent *e){
    float cameraSensitivity = 0.1f;

    // Handle mouse movement and calculate new camera rotation values
    QPointF newPos = e->globalPosition();

    if(!firstMouse){
        QPointF distance = newPos - this->globalCenterCoordinates;
        float distX = distance.x();
        float distY = distance.y();

        //qDebug() << "Move X = "<< distX <<"\n Move Y = " << distY;

        distX *= cameraSensitivity;
        distY *= cameraSensitivity;

        camera->addPitch(-distY);
        camera->addYaw(distX);
    }
    else firstMouse=false;

    changeMousePosition();
}

void GL_ShipViewerWidget::mousePressEvent(QMouseEvent *e){
    if(!attachMouse){
        attachMouse = true;
        this->setMouseTracking(true);
        this->grabMouse();
        this->setCursor(Qt::BlankCursor);
        this->changeMousePosition();
    }
}

void GL_ShipViewerWidget::leaveEvent(QEvent *e){
    if(attachMouse){
        changeMousePosition();
    }
}

void GL_ShipViewerWidget::changeMousePosition(){
    if(attachMouse) this->cursor().setPos(globalCenterCoordinates);
}

bool GL_ShipViewerWidget::isAttachMouse() {
    return attachMouse;
}

void GL_ShipViewerWidget::changeComponentActivation(std::string ship, bool selected){
    for(GL_Ship *shipModel : this->models){
        if(shipModel->getName().compare(ship)==0) {
            shipModel->setActivate(selected);
            return;
        }
    }
}

/*----------------------*
 *   OPENGL FUNCTIONS   *
 *----------------------*/
void GL_ShipViewerWidget::initializeGL(){
    initializeOpenGLFunctions();

    this->initialize();

    glClearColor(0,0,0,1);
}

void GL_ShipViewerWidget::paintGL(){
    if(this->attachMouse){
        changeMousePosition();
    }

    if(isValid()) render();

}
void GL_ShipViewerWidget::resizeGL(int w, int h){

    widgetWidth = w;
    widgetHeight = h;

    QPoint localCenter(widgetWidth/2, widgetHeight/2);
    globalCenterCoordinates = this->mapToGlobal(localCenter);
    changeMousePosition();

}

void GL_ShipViewerWidget::setApp(ApplicationManager *a){
    this->application = a;
}

void GL_ShipViewerWidget::initialize(){

    camera = new GL_Camera();
    camera->setPosition(QVector3D(5.0f, 5.0f, 0.0f));
    camera->setDirection(QVector3D(0.0f, -1.0f, -1.0f));
    camera->calculateVectors();
    camera->setInit(true);

    QPoint localCenter(this->width()/2, this->height()/2);
    globalCenterCoordinates = this->mapToGlobal(localCenter);
    changeMousePosition();

    std::vector<std::string> components = updateData(shipFile);
    window->changeWindowData(components, getShipName());

    isInitialized = true;

    elapsedTimer.start();
    currentFrame = elapsedTimer.msecsSinceReference();
    elapsedTimer.restart();

    connect(&timer, &QTimer::timeout, this, &GL_ShipViewerWidget::keyPress);
    timer.setInterval(10);
    timer.start();

}

std::vector<std::string> GL_ShipViewerWidget::updateData(std::string file){
    std::vector<std::string> names;

    QJsonObject rootObj = global::openJSON(QString::fromStdString(global::dataPath()+"Ships/"+file+".json"));

    // If file is not present
    if(rootObj.isEmpty()){
        std::cout << "Opening file for GL failed \n" << std::endl;
    }
    // If file present
    else {
        std::string shipName = rootObj.value("shipName").toString().toStdString();
        this->shipName = shipName;

        std::string shipPrefix = rootObj.value("shipPrefix").toString().toStdString();

        auto shipComponentsArray = rootObj.value("components").toArray();
        for(auto componentEntry: shipComponentsArray){
            auto component = componentEntry.toObject();

            std::string name = component.value("name").toString().toStdString();
            std::string file = component.value("file").toString().toStdString();

            std::string texture = "";
            if(!component.value("texture").isUndefined()) texture = shipPrefix + "/" + component.value("texture").toString().toStdString() + ".png";
            else texture = "white.png";

            auto componentPositionArray = component.value("position").toArray();
            float x = componentPositionArray.at(0).toDouble();
            float y = componentPositionArray.at(1).toDouble();
            float z = componentPositionArray.at(2).toDouble();

            GL_Ship *newShip = new GL_Ship(shipPrefix+"/"+file+".obj", name, texture, QVector3D(x,y,z));
            this->models.push_back(newShip);

            names.push_back(name);
        }
    }

    return names;
}

void GL_ShipViewerWidget::render(){
    const qreal retinaScale = devicePixelRatio();

    float w = width() * retinaScale;
    float h = height() * retinaScale;

    glViewport(0, 0, w, h);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glEnable(GL_CULL_FACE);
    glDisable(GL_CULL_FACE);

    lastFrame = currentFrame;
    currentFrame = elapsedTimer.msecsSinceReference();

    projection = QMatrix4x4();
    projection.setToIdentity();
    projection.perspective(45, (float)w/(float)h, 0.1f, 1000.0f);

    camera->calculateVectors();
    view = camera->getView();

    QMatrix4x4 projectionViewMatrix = projection * view;

    for(GL_Object *m: models){
        m->render(projectionViewMatrix, ambientLight*ambientIntensity, diffuseLight, lightPosition, camera->getPosition());
    }

    elapsedTimer.restart();

}
