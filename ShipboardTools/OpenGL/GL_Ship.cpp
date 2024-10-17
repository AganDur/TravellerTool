#include "GL_Ship.h"
#include "qopengltexture.h"

#include <iostream>

GL_Ship::GL_Ship(std::string file, std::string name, std::string texture, QVector3D position) : GL_Unique{file, QVector3D(1.0f, 1.0f, 1.0f), name} {

    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();

    this->name = name;
    this->scale = QVector3D(1, 1, 1);
    this->position = position;

    compileShaders("ship", "ship");
    shaderProgram->bind();

    VAO.bind();

    // Prepare Object's data
    f->glEnableVertexAttribArray(0);
    f->glEnableVertexAttribArray(1);
    f->glEnableVertexAttribArray(2);
    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), (void*)0);
    f->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), reinterpret_cast<void*>(3*sizeof(GLfloat)));
    f->glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), reinterpret_cast<void*>(6*sizeof(GLfloat)));

    //shaderProgram->setUniformValue(this->lightPositionUniform, QVector3D(0 , 0, 0));
    shaderProgram->release();
    VAO.release();

    loadTexture("Assets/Textures/"+texture);

}

QMatrix4x4 GL_Ship::getModelMatrix() {
    QMatrix4x4 model;
    //model.setToIdentity();
    //model.translate(this->position);

    return model;
}

void GL_Ship::compileShaders(std::string vertexShaderName, std::string fragmentShaderName){
    GL_Object::compileShaders(vertexShaderName, fragmentShaderName);

    if(shaderProgram->isLinked()){
        // GET ATTRIBUTE LOCATION VALUES
        positionAttribute = shaderProgram->attributeLocation("position");
        //normalAttribute = shaderProgram->attributeLocation("normal");
        textureCoordinatesAttribute = shaderProgram->attributeLocation("textureCoordinates");

        // GET UNIFORM LOCATION VALUES
        this->projectionViewMatrixUniform=shaderProgram->uniformLocation("projMatrix");
        this->modelMatrixUniform=shaderProgram->uniformLocation("mvMatrix");
        this->normalMatrixUniform=shaderProgram->uniformLocation("normalMatrix");
        this->cameraPositionUniform=shaderProgram->uniformLocation("cameraPos");
        this->lightPositionUniform=shaderProgram->uniformLocation("lightPos");
        ambientLightUniform = shaderProgram->uniformLocation("ambientLight");
        diffuseLightUniform = shaderProgram->uniformLocation("diffuseLight");
        colorUniform = shaderProgram->uniformLocation("color");
    }

}

void GL_Ship::render(QMatrix4x4 projectionViewMatrix, QVector3D ambientLight, QVector3D diffuseLight, QVector3D lightPosition, QVector3D cameraPosition) {
    if(!active) return;

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
    shaderProgram->setUniformValue(this->lightPositionUniform, lightPosition);
    shaderProgram->setUniformValue(this->cameraPositionUniform, cameraPosition);

    // BIND TEXTURE FOR USE
    texture->bind();

    f->glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    shaderProgram->release();
    VAO.release();
}

void GL_Ship::setActivate(bool active){
    this->active = active;
}
