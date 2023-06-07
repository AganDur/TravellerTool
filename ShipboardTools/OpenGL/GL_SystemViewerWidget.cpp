#include "GL_SystemViewerWidget.h"

#include "GL_Camera.h"
#include "GL_Object.h"
#include "../Globals.h"
#include "../ApplicationManager.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <QJsonArray>

GL_SystemViewerWidget::GL_SystemViewerWidget(std::string systemName){
    GL_Widget();
    system = systemName;
}

void GL_SystemViewerWidget::initialize(){
    camera = new GL_Camera();
    camera->setPosition(QVector3D(0.0f, 0.0f, 50.0f));
    camera->setDirection(QVector3D(0.0f, 0.0f, -1.0f));

    this->setCursor(Qt::BlankCursor);
    // this->cursor().setPos(400, 300);

    initSphere();

    //TODO: Read File;???

    this->updateData(system);

    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);

    connect(&timer, &QTimer::timeout, this, &GL_SystemViewerWidget::keyPress);
    timer.setInterval(10);
    timer.start();

    elapsedTimer.start();
    currentFrame = elapsedTimer.msecsSinceReference();
    elapsedTimer.restart();
}

void GL_SystemViewerWidget::initSphere(){
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(global::path() + "Assets/Meshes/star.obj", aiProcess_Triangulate | aiProcess_FlipUVs);

    if(!scene || (scene->mFlags && AI_SCENE_FLAGS_INCOMPLETE) || !scene->mRootNode){
        qDebug() << "ERROR::ASSIMP::" << importer.GetErrorString();
        return;
    }
    aiMesh* meshData;
    meshData = scene->mMeshes[0];

    std::vector<GLfloat> verticesPos;
    std::vector<GLfloat> verticesNormals;

    for(unsigned int i=0 ; i < meshData->mNumVertices ; i++){

        planetVertices.push_back(meshData->mVertices[i].x);
        planetVertices.push_back(meshData->mVertices[i].y);
        planetVertices.push_back(meshData->mVertices[i].z);
        planetVertices.push_back(meshData->mNormals[i].x);
        planetVertices.push_back(meshData->mNormals[i].y);
        planetVertices.push_back(meshData->mNormals[i].z);
        planetVertices.push_back(meshData->mTextureCoords[0][i].x);
        planetVertices.push_back(meshData->mTextureCoords[0][i].y);


        starVertices.push_back(meshData->mVertices[i].x);
        starVertices.push_back(meshData->mVertices[i].y);
        starVertices.push_back(meshData->mVertices[i].z);
        starVertices.push_back(meshData->mTextureCoords[0][i].x);
        starVertices.push_back(meshData->mTextureCoords[0][i].y);
    }

    for(unsigned int i=0 ; i< meshData->mNumFaces ; i++){
        aiFace f = meshData->mFaces[i];
        for(unsigned int j=0 ; j<f.mNumIndices ; j++) sphereIndices.push_back(f.mIndices[j]);
    }
}


// TODO
void GL_SystemViewerWidget::keyPress(){
    // Escape
    if(GetAsyncKeyState(0x1B) & 0x100000){
        //application->closeGL();
        return;
    }

    // Up Arrow
    if(GetAsyncKeyState(0x26) & 0x100000){
        this->orbitingSpeed *= 10;
        if(orbitingSpeed > 1) orbitingSpeed = 1;
    }
    // Down Arrow
    else if(GetAsyncKeyState(0x28) & 0x100000){
        this->orbitingSpeed /= 10;
        if(orbitingSpeed < 0.01) orbitingSpeed = 0.01;
    }

    // R Key
    if(GetAsyncKeyState(0x52) & 0x100000){
        camera->reset();
        return;
    }

    // Q Key
    if(GetAsyncKeyState(0x51) & 0x100000){
        camera->moveRight(2.5);
    }
    // D Key
    else if(GetAsyncKeyState(0x44) & 0x100000){
        camera->moveRight(-2.5);
    }

    // Z Key
    if(GetAsyncKeyState(0x5A) & 0x100000){
        camera->moveForward(2.5);
    }
    // S Key
    else if(GetAsyncKeyState(0x53) & 0x100000){
        camera->moveForward(-2.5);
    }

    // E Key
    if(GetAsyncKeyState(0x45) & 0x100000){
        camera->moveUp(2.5);
    }
    // A Key
    else if(GetAsyncKeyState(0x41) & 0x100000){
        camera->moveUp(-2.5);
    }
}


// TODO
void GL_SystemViewerWidget::mouseMoveEvent(QMouseEvent *e){
    /*
    float cameraSensitivity = 0.1f;

    // Handle mouse movement and calculate new camera rotation values
    QPointF newPos = e->scenePosition();
    if(!firstMouse){
        float distX = newPos.x() - 400;
        float distY = newPos.y() - 300;

        //qDebug() << "Move X = "<< distX <<"\n Move Y = " << distY;

        distX *= cameraSensitivity;
        distY *= cameraSensitivity;

        camera->addPitch(-distY);
        camera->addYaw(distX);
    }
    else firstMouse=false;

    this->cursor().setPos(400,300);
    */
}


// TODO
void GL_SystemViewerWidget::updateData(std::string file){
    QJsonObject rootObj = global::openJSON(QString::fromStdString(global::path()+"Systems/"+file+".json"));

    // If file is not present
    if(rootObj.isEmpty()){
        std::cout << "Opening file for GL failed \n" << std::endl;
    }
    // If file present
    else {
        //qDebug("Opening file for GL succeeded");

        /*------------------------*
         *     READ STAR DATA     *
         *------------------------*/
        QJsonValue starEntry = rootObj.value("star");
        if(!starEntry.isNull()){
            auto starObject = starEntry.toObject();
            std::string starClass = starObject.value("class").toString().toStdString();
            //std::cout << "Main star: " << starClass << std::endl;

            // Setup star data
            auto colorObject = starObject.value("color").toObject();
            float r, g, b;
            r = colorObject.value("red").toDouble();
            b = colorObject.value("blue").toDouble();
            g = colorObject.value("green").toDouble();
            float rad = starObject.value("radius").toDouble();

            // Add star to models
            //models.push_back(new GL_Star(starVertices, sphereIndices, starClass, rad, 0.0, r, g,b));
        }

        /*---------------------------*
         *     READ ORBITAL DATA     *
         *---------------------------*/
        QJsonArray orb = rootObj.value("orbiting").toArray();
        //std::cout << "Orbiting: " << orb.size() << std::endl;
        for(auto orbiting: orb){
            //std::cout << "Object"<<std::endl;
            /*----------------------------*
             *     FORMING THE ORBITS     *
             *----------------------------*/
            auto orbitObject = orbiting.toObject().value("orbit").toObject();
            float SemiMajor, SemiMinor;
            if(orbitObject.value("type")=="circle"){
               float r = orbitObject.value("radius").toDouble();
               SemiMajor = r;
               SemiMinor = r;
            }
            else {
                SemiMajor = orbitObject.value("semi-major").toDouble();
                SemiMinor = orbitObject.value("semi-minor").toDouble();
            }

            /*Orbit* o = new Orbit(QVector3D(0,0,0), SemiMajor, SemiMinor, 0);
            if(orbitObject.contains("color")){
                QJsonObject colorObject = orbitObject.value("color").toObject();
                qDebug() << "Found color orbit" ;
                float r, g, b;
                r = colorObject.value("r").toDouble();
                g = colorObject.value("g").toDouble();
                b = colorObject.value("b").toDouble();
                o->setColor(QVector3D(r, g, b));
            }*/

            /*--------------------------*
             *     FORMING THE BODY     *
             *--------------------------*/
            std::string name, uwp;
            float size;
            auto world = orbiting.toObject().value("world").toObject();
            name = world.value("name").toString().toStdString();
            uwp = world.value("uwp").toString().toStdString();
            size = world.value("size").toDouble();

            std::string textureName = world.value("texture").toString().toStdString();
            if(textureName.empty()) textureName="venus.jpg";

            /*Planet* p = new Planet(planetVertices, sphereIndices, size, *o, name, uwp);
            p->setTexture(textureName);
            models.push_back(p);*/
        }
    }
}


// TODO
//void GL_SystemViewerWidget::paintEvent(QPaintEvent *event){
void GL_SystemViewerWidget::render(){
    glDepthMask(GL_TRUE);

    lastFrame = currentFrame;
    currentFrame = elapsedTimer.msecsSinceReference();

    double timeRatio = currentFrame - lastFrame;
    timeRatio *= orbitingSpeed;

    const qreal retinaScale = devicePixelRatio();

    float w = width() * retinaScale;
    float h = height() * retinaScale;

    glViewport(0, 0, w, h);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    projection = QMatrix4x4();
    projection.perspective(camera->getZoom(), (float)w/(float)h, 0.1f, 500.0f);

    camera->calculateVectors();
    view = camera->getView();

    QMatrix4x4 mat = projection * view;

    QVector3D diffuseLight = models.at(0)->getColor();

    for(GL_Object *m: models){
        m->updateTime(timeRatio);
        m->render(mat, ambientLight*ambientIntensity, diffuseLight);
    }

    elapsedTimer.restart();
}


