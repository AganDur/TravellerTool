#include "GL_Planet.h"

#include "GL_Orbit.h"

#include <QOpenGLTexture>

static const char *vertexShaderSource =
    "attribute vec4 vertex;\n"
    "attribute vec3 normal;\n"
    "varying vec3 vert;\n"
    "varying vec3 vertNormal;\n"
    "uniform mat4 projMatrix;\n"
    "uniform mat4 mvMatrix;\n"
    "uniform mat3 normalMatrix;\n"
    "void main() {\n"
    "   vert = vertex.xyz;\n"
    "   vertNormal = normalMatrix * normal;\n"
    "   gl_Position = projMatrix * mvMatrix * vertex;\n"
    "}\n";

static const char *fragmentShaderSource =
    "varying highp vec3 vert;\n"
    "varying highp vec3 vertNormal;\n"
    "uniform highp vec3 lightPos;\n"
    "void main() {\n"
    "   highp vec3 L = normalize(lightPos - vert);\n"
    "   highp float NL = max(dot(normalize(vertNormal), L), 0.0);\n"
    "   highp vec3 color = vec3(0.39, 1.0, 0.0);\n"
    "   highp vec3 col = clamp(color * 0.2 + color * 0.8 * NL, 0.0, 1.0);\n"
    "   gl_FragColor = vec4(col, 1.0);\n"
    "}\n";

GL_Planet::GL_Planet(std::vector<GLfloat> vertices, std::vector<unsigned int> indices, float size, GL_Orbit orbit, std::string name, std::string uwp): GL_Unique{"planetShader", "planetShader", vertices, indices, QVector3D(1.0f, 1.0f, 1.0f)}, planetaryOrbit{orbit}{
    this->name = name;
    this->size = size;
    this->UWP = uwp;

    //compileShaders("planetShader", "planetShader");

    shaderProgram = new QOpenGLShaderProgram;
    shaderProgram->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    shaderProgram->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
    shaderProgram->bindAttributeLocation("vertex", 0);
    shaderProgram->bindAttributeLocation("normal", 1);
    shaderProgram->link();

    shaderProgram->bind();
    this->projectionViewMatrixUniform=shaderProgram->uniformLocation("projMatrix");
    this->modelMatrixUniform=shaderProgram->uniformLocation("mvMatrix");
    this->normalMatrixUniform=shaderProgram->uniformLocation("normalMatrix");
    this->lightPositionUniform=shaderProgram->uniformLocation("lightPos");

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
    f->glEnableVertexAttribArray(0);
    f->glEnableVertexAttribArray(1);
    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), (void*)0);
    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), reinterpret_cast<void*>(3*sizeof(GLfloat)));

    shaderProgram->setUniformValue(this->lightPositionUniform, QVector3D(0 , 0, 70));
    shaderProgram->release();
    VAO.release();
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
    /*
    // CALCULATE PLANET MODEL MATRIX
    QMatrix4x4 modelMatrix = QMatrix4x4(); //getModelMatrix();

    shaderProgram->setUniformValue(projectionViewMatrixUniform, proj*cam);
    shaderProgram->setUniformValue(modelMatrixUniform, modelMatrix);
    shaderProgram->setUniformValue(ambientLightUniform, ambientLight);
    shaderProgram->setUniformValue(diffuseLightUniform, diffuseLight);
    shaderProgram->setUniformValue(colorUniform, getColor());
    shaderProgram->setUniformValue(lightPositionUniform, QVector3D(0.0, 0.0, 0.0));

    // BIND TEXTURE FOR USE
    //texture->bind();

    // SET ATTRIBUTE BUFFERS
    glVertexAttribPointer(positionAttribute, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)0);
    glVertexAttribPointer(normalAttribute, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(3*sizeof(float)));
    glVertexAttribPointer(textureCoordinatesAttribute, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(6*sizeof(float)));

    //shaderProgram->enableAttributeArray(textureCoordinatesAttribute);
    shaderProgram->enableAttributeArray(positionAttribute);
    //shaderProgram->enableAttributeArray(normalAttribute);


    */
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();

    QMatrix4x4 model;
    model.setToIdentity();
    model.rotate(nb_frames * 10, 0, 1, 0);

    QMatrix4x4 proj;
    QMatrix4x4 cam;
    cam.setToIdentity();
    cam.translate(0,0,-1);

    VAO.bind();

    shaderProgram->bind();
    shaderProgram->setUniformValue(this->projectionViewMatrixUniform, projectionViewMatrix);
    shaderProgram->setUniformValue(this->modelMatrixUniform, model);
    QMatrix3x3 normalMatrix = model.normalMatrix();
    shaderProgram->setUniformValue(this->normalMatrixUniform, normalMatrix);

    f->glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    shaderProgram->release();

    VAO.release();

    nb_frames ++;

    // CALL ORBIT RENDER TOO
    //this->planetaryOrbit.render(projectionViewMatrix);
}

void GL_Planet::updateTime(double timeRatio){
    planetaryOrbit.increaseAngle(timeRatio);
}


