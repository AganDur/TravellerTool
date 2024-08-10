#include "GL_Planet.h"
#include "GL_Orbit.h"

#include <iostream>

#include <QOpenGLTexture>

/*------------------*
 *   CONSTRUCTORS   *
 *------------------*/
// Default Class Constructor
GL_Planet::GL_Planet(std::vector<GLfloat> vertices, std::vector<unsigned int> indices, float size, GL_Orbit orbit, std::string name, std::string uwp): GL_Unique{vertices, indices, QVector3D(1.0f, 1.0f, 1.0f), name}, planetaryOrbit{orbit}{
    this->name = name;
    this->size = size;
    this->UWP = uwp;

    this->scale= QVector3D(size, size, size);

    compileShaders("planetNew", "planetNew");

    shaderProgram->bind();

    // Prepare Object's buffers
    VAO.destroy();
    this->VAO.create();
    this->VAO.bind();
    this->VBO->create();
    this->VBO->bind();
    this->VBO->allocate(vertices.data(), vertices.size() * sizeof(GLfloat));
    this->EBO->create();
    this->EBO->bind();
    this->EBO->allocate(indices.data(), indices.size() * sizeof(GLfloat));

    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();

    // Prepare Object's data
    f->glEnableVertexAttribArray(0);
    f->glEnableVertexAttribArray(1);
    f->glEnableVertexAttribArray(2);
    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), (void*)0);
    f->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), reinterpret_cast<void*>(3*sizeof(GLfloat)));
    f->glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), reinterpret_cast<void*>(6*sizeof(GLfloat)));

    shaderProgram->setUniformValue(this->lightPositionUniform, QVector3D(0 , 0, 0));
    shaderProgram->release();
    VAO.release();
}

// Default class Destructor
GL_Planet::~GL_Planet(){

}

/*----------------------*
 *   GETTER FUNCTIONS   *
 *----------------------*/
QMatrix4x4 GL_Planet::getModelMatrix(){
    QMatrix4x4 model;

    // Handle orbit rotations
    model.rotate(planetaryOrbit.getArgumentOfPeriapsis(), QVector3D(0,0,1));
    model.rotate(planetaryOrbit.getInclination(), QVector3D(0,1,0));
    if(planetaryOrbit.getEccentricity()!=0) model.rotate(planetaryOrbit.getLongitudeOfAscendingNode(), QVector3D(0,0,1));

    // Find model place on orbit
    float positionX = planetaryOrbit.getX_CurrentAngle();
    float positionY = planetaryOrbit.getY_CurrentAngle();
    model.translate(QVector3D(positionX, positionY, 0.0f));

    // Place model depending on parents
    QVector3D parentsCenter = this->getParentsCenter();
    model.translate(parentsCenter);

    // Scale model
    model.scale(scale);

    this->position = parentsCenter + QVector3D(positionX, positionY, 0);
    return model;
}

QVector3D GL_Planet::getPosition(){
    return position;
}

/*----------------------*
 *   OPENGL FUNCTIONS   *
 *----------------------*/
void GL_Planet::compileShaders(std::string vertexShaderName, std::string fragmentShaderName){
    GL_Object::compileShaders(vertexShaderName, fragmentShaderName);

    if(shaderProgram->isLinked()){
        // GET ATTRIBUTE LOCATION VALUES
        positionAttribute = shaderProgram->attributeLocation("position");
        normalAttribute = shaderProgram->attributeLocation("normal");
        textureCoordinatesAttribute = shaderProgram->attributeLocation("textureCoordinates");

        // GET UNIFORM LOCATION VALUES
        this->projectionViewMatrixUniform=shaderProgram->uniformLocation("projMatrix");
        this->modelMatrixUniform=shaderProgram->uniformLocation("mvMatrix");
        this->normalMatrixUniform=shaderProgram->uniformLocation("normalMatrix");
        this->lightPositionUniform=shaderProgram->uniformLocation("lightPos");
        ambientLightUniform = shaderProgram->uniformLocation("ambientLight");
        diffuseLightUniform = shaderProgram->uniformLocation("diffuseLight");
        colorUniform = shaderProgram->uniformLocation("color");
    }
}

void GL_Planet::render(QMatrix4x4 projectionViewMatrix, QVector3D ambientLight, QVector3D diffuseLight, QVector3D lightPosition, QVector3D cameraPosition){

    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();

    QMatrix4x4 model = getModelMatrix();

    QMatrix3x3 normalMatrix = model.normalMatrix();

    VAO.bind();

    shaderProgram->bind();

    shaderProgram->setUniformValue(this->projectionViewMatrixUniform, projectionViewMatrix);
    shaderProgram->setUniformValue(this->modelMatrixUniform, model);
    shaderProgram->setUniformValue(this->normalMatrixUniform, normalMatrix);
    shaderProgram->setUniformValue(this->colorUniform, color);
    shaderProgram->setUniformValue(this->ambientLightUniform, ambientLight);
    shaderProgram->setUniformValue(this->diffuseLightUniform, diffuseLight);

    // BIND TEXTURE FOR USE
    texture->bind();

    f->glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    shaderProgram->release();
    VAO.release();
    nb_frames ++;

    // CALL ORBIT RENDER TOO
    model.setToIdentity();
    model.translate(this->getParentsCenter());
    this->planetaryOrbit.render(model, projectionViewMatrix);
}

void GL_Planet::updateTime(double timeRatio){
    //planetaryOrbit.increaseAngle(timeRatio);
    planetaryOrbit.calculateOrbit(timeRatio);
}


