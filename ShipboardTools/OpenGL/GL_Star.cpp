#include "GL_Star.h"

#include <QOpenGLTexture>

/*------------------*
 *   CONSTRUCTORS   *
 *------------------*/
// Default Class Constructor
GL_Star::GL_Star(std::vector<GLfloat> vertices, std::vector<unsigned int> indices, std::string stellarClass, float radius, float mass, QVector3D color, GL_Orbit orbit) : GL_Unique{vertices, indices, color}, stellarOrbit{orbit}{
    this->size = radius;
    this->mass = mass;

    this->scale = QVector3D(size, size, size);

    compileShaders("starNew", "starNew");

    shaderProgram->bind();

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

    f->glEnableVertexAttribArray(this->positionAttribute);
    f->glEnableVertexAttribArray(this->textureCoordinatesAttribute);
    f->glVertexAttribPointer(this->positionAttribute, 3, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), (void*)0);
    f->glVertexAttribPointer(this->textureCoordinatesAttribute, 2, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), reinterpret_cast<void*>(3*sizeof(GLfloat)));

    shaderProgram->release();
    VAO.release();
}

// Default Class Destructor
GL_Star::~GL_Star(){

}

/*------------------------*
 *   OPEN GL PARAMETERS   *
 *------------------------*/
void GL_Star::compileShaders(std::string vertexShaderName, std::string fragmentShaderName){
    GL_Object::compileShaders(vertexShaderName, fragmentShaderName);

    if(shaderProgram->isLinked()){
        // GET ATTRIBUTE LOCATION VALUES
        positionAttribute = shaderProgram->attributeLocation("vertex");
        textureCoordinatesAttribute = shaderProgram->attributeLocation("textureCoordinates");

        // GET UNIFORM LOCATION VALUES
        this->projectionViewMatrixUniform=shaderProgram->uniformLocation("projMatrix");
        this->modelMatrixUniform=shaderProgram->uniformLocation("mvMatrix");
        colorUniform = shaderProgram->uniformLocation("color");
    }
}

void GL_Star::render(QMatrix4x4 projectionViewMatrix, QVector3D ambientLight, QVector3D diffuseLight){
    QMatrix4x4 parentTransform;
    if(this->parent!=nullptr) parentTransform.translate(parent->getPosition());

    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();

    QMatrix4x4 model;
    model.setToIdentity();
    this->position = QVector3D(this->stellarOrbit.getX_CurrentAngle(), this->stellarOrbit.getY_CurrentAngle(), 0);
    if(this->stellarOrbit.getSemiMajor()<=0) position = QVector3D(0,0,0);
    model.translate(position);
    model.scale(scale);

    VAO.bind();

    shaderProgram->bind();

    shaderProgram->setUniformValue(this->projectionViewMatrixUniform, projectionViewMatrix);
    shaderProgram->setUniformValue(this->modelMatrixUniform, model);
    shaderProgram->setUniformValue(this->colorUniform, color);

    // BIND TEXTURE FOR USE
    texture->bind();

    f->glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    shaderProgram->release();
    VAO.release();

    if(this->stellarOrbit.getSemiMajor()>0) {
        model.setToIdentity();
        if(this->parent!=nullptr) model.translate(parent->getPosition());
        this->stellarOrbit.render(model, projectionViewMatrix);
    }
}

void GL_Star::updateTime(double timeRatio){
    //stellarOrbit.increaseAngle(timeRatio);
    stellarOrbit.calculateOrbit(timeRatio);
}

QVector3D GL_Star::getPosition(){
    return this->position;
}
