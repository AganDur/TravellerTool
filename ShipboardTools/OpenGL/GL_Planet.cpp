#include "GL_Planet.h"

#include "GL_Orbit.h"

#include <QOpenGLTexture>

GL_Planet::GL_Planet(std::vector<GLfloat> vertices, std::vector<unsigned int> indices, float size, GL_Orbit orbit, std::string name, std::string uwp): GL_Unique{"planetShader", "planetShader", vertices, indices, QVector3D(1.0f, 1.0f, 1.0f)}, planetaryOrbit{orbit}{
    this->name = name;
    this->size = size;
    this->UWP = uwp;

    compileShaders("planetShader", "planetShader");
}

GL_Planet::~GL_Planet(){

}

QMatrix4x4 GL_Planet::getModelMatrix(){
    QMatrix4x4 model;

    float positionX = planetaryOrbit.getX_CurrentAngle();
    float positionY = planetaryOrbit.getY_CurrentAngle();

    model.translate(QVector3D(positionX, positionY, 0.0f));
    model.rotate(pitchAngle, QVector3D(0.0f, 1.0f, 0.0f));
    model.scale(scale);

    return model;
}

void GL_Planet::compileShaders(std::string vertexShaderName, std::string fragmentShaderName){
    GL_Object::compileShaders(vertexShaderName, fragmentShaderName);


    if(shaderProgram->isLinked()){
        // GET ATTRIBUTE LOCATION VALUES
        positionAttribute = shaderProgram->attributeLocation("position");
        normalAttribute = shaderProgram->attributeLocation("normal");
        textureCoordinatesAttribute = shaderProgram->attributeLocation("textureCoordinates");

        // GET UNIFORM LOCATION VALUES
        projectionViewMatrixUniform = shaderProgram->uniformLocation("projectionViewMatrix");
        modelMatrixUniform = shaderProgram->uniformLocation("modelMatrix");
        ambientLightUniform = shaderProgram->uniformLocation("ambientLight");
        diffuseLightUniform = shaderProgram->uniformLocation("diffuseLight");
        colorUniform = shaderProgram->uniformLocation("color");
        lightPositionUniform = shaderProgram->uniformLocation("lightUniform");
    }
}

void GL_Planet::render(QMatrix4x4 projectionViewMatrix, QVector3D ambientLight, QVector3D diffuseLight){
    VAO.bind();
    //VBO->bind();
    shaderProgram->bind();

    // CALCULATE PLANET MODEL MATRIX
    QMatrix4x4 modelMatrix = getModelMatrix();

    // SET UNIFORM VALUES
    QMatrix4x4 proj ;
    shaderProgram->setUniformValue(projectionViewMatrixUniform, proj);//ectionViewMatrix);
    shaderProgram->setUniformValue(modelMatrixUniform, modelMatrix);
    shaderProgram->setUniformValue(ambientLightUniform, ambientLight);
    shaderProgram->setUniformValue(diffuseLightUniform, diffuseLight);
    shaderProgram->setUniformValue(colorUniform, getColor());
    shaderProgram->setUniformValue(lightPositionUniform, QVector3D(0.0, 0.0, 0.0));

    // BIND TEXTURE FOR USE
    texture->bind();

    // SET ATTRIBUTE BUFFERS
    glVertexAttribPointer(positionAttribute, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)0);
    glVertexAttribPointer(normalAttribute, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(3*sizeof(float)));
    glVertexAttribPointer(textureCoordinatesAttribute, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(6*sizeof(float)));

    shaderProgram->enableAttributeArray(textureCoordinatesAttribute);
    shaderProgram->enableAttributeArray(positionAttribute);
    shaderProgram->enableAttributeArray(normalAttribute);


    // RENDER CALL
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    // CLEANUP
    VAO.release();
    shaderProgram->release();

    // CALL ORBIT RENDER TOO
    //this->planetaryOrbit.render(projectionViewMatrix);
}

void GL_Planet::updateTime(double timeRatio){
    planetaryOrbit.increaseAngle(timeRatio);
}


