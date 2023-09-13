#include "GL_Orbit.h"

/*------------------------*
 *   SHADER SOURCE DATA   *
 *------------------------*/
const char* vertexSource =
        "#version 450 core\n"
        "layout (location=0) in vec3 posAttr;\n"
        "uniform mat4 model;\n"
        "uniform mat4 matrix;\n"
        "void main() {\n"
        "gl_Position = matrix * model * vec4(posAttr, 1.0);\n"
        "}";

const char* fragmentSource =
        "#version 450 core\n"
        "uniform vec3 color;\n"
        "out vec4 outColor;"
        "void main() {\n"
        "outColor = vec4(color, 1.0);\n"
        "}";

/*------------------*
 *   CONSTRUCTORS   *
 *------------------*/
// Default Class Constructor
GL_Orbit::GL_Orbit(QVector3D center, float semiMajor, float semiMinor, int rotation){
    this->center=center;
    this->semiMajor = semiMajor;
    this->semiMinor = semiMinor;
    this->rotation = rotation;

    // When the orbit is a true circle
    if(semiMinor==semiMajor){
        eccentricity = 0;
        distanceToFocus = 0;
    }

    // When the orbit is an ellipsis
    else{
        eccentricity = sqrt(1 - ((semiMinor*semiMinor) / (semiMajor*semiMajor)));
        float c2 = (semiMajor*semiMajor) - (semiMinor*semiMinor);
        float c1 = sqrt(c2);
        distanceToFocus = c1;
    }

    completeSurface = 3.14 * semiMajor * semiMinor;
    lastAngle = 0;

    // Orbital Period in Years
    orbitalPeriod = 2 * 3.14 * sqrt(semiMajor * semiMajor * semiMajor);

    // Setup vertices
    float angle = 3.6;
    for(int i=0 ; i<100 ; i++){
        float x0 = getX_Angle(2*i*angle);
        float x1 = getX_Angle(((2*i)+1)*angle);
        float y0 = getY_Angle(2*i*angle);
        float y1 = getY_Angle(((2*i)+1)*angle);

        // V1
        vertices.push_back(x0*0.999);
        vertices.push_back(y0*0.999);
        vertices.push_back(0.0);

        // V2
        vertices.push_back(x1*0.999);
        vertices.push_back(y1*0.999);
        vertices.push_back(0.0);

        // V3
        vertices.push_back(x1*1.001);
        vertices.push_back(y1*1.001);
        vertices.push_back(0.0);

        // V4
        vertices.push_back(x0*1.001);
        vertices.push_back(y0*1.001);
        vertices.push_back(0.0);
    }

    color = QVector3D(0.5, 0.5, 0.5);

    G = 1;
    M = 1;
    m = 1;
    float r = semiMajor + distanceToFocus;

    originalVelocity = G*M*((2/r) - (1/semiMajor));
    originalVelocity = sqrt(originalVelocity);
    this->pos = QVector3D(semiMajor + distanceToFocus, 0, 0);
    this->p = QVector3D(0, m*originalVelocity, 0);
}

// Copy Constructor
GL_Orbit::GL_Orbit(GL_Orbit &o){
    this->semiMajor = o.semiMajor;
    this->semiMinor = o.semiMinor;
    this->center = o.center;
    this->eccentricity = o.eccentricity;
    this->distanceToFocus = o.distanceToFocus;
    this->rotation = o.rotation;

    this->vertices = o.vertices;

    this->color = o.color;
    this->completeSurface = o.completeSurface;
    this->lastAngle = o.lastAngle;
    this->orbitalPeriod = o.orbitalPeriod;

    this->originalVelocity = o.originalVelocity;
    this->G = o.G;
    this->M = o.M;
    this->m = o.m;

    this->pos = QVector3D(semiMajor + distanceToFocus, 0, 0);
    this->p = QVector3D(0, m*originalVelocity, 0);

    prepare();
}


/*----------------------*
 *   GETTER FUNCTIONS   *
 *----------------------*/

float GL_Orbit::getSemiMinor() {
    return this->semiMinor;
}
float GL_Orbit::getSemiMajor() {
    return this->semiMajor;
}

/*
 * Position On Orbit Functions:
 * Allow to get X/Y coordinates of any point on the orbit.
 * NoAngle gives the x/y coordinates at the starting point of the orbit.
 * Angle gives the x/y coordinates at the specified angle.
 * CurrentAngle gives the x/y coordinates based on the render-time-based angle.
 */
float GL_Orbit::getX_NoAngle(){
    float X;
    if(eccentricity == 0){
        float x0 = semiMajor;
        X = x0;
    }
    else {
        float x0 = semiMajor;
        X = x0 + distanceToFocus;
    }

    return X;
}
float GL_Orbit::getX_Angle(float angle){
    float xO = semiMajor * cos(angle*3.14/180);
    float yO = semiMinor * sin(angle*3.14/180);
    float X = xO + distanceToFocus;
    return X;
}
float GL_Orbit::getX_CurrentAngle(){
    //float xO = semiMajor * cos(lastAngle*3.14/180);
    //float yO = semiMinor * sin(lastAngle*3.14/180);
    //float X = xO + distanceToFocus;
    return pos.x();
}

float GL_Orbit::getY_NoAngle(){
    float xO = semiMajor;
    float yO = 0;
    float Y = 0;//y0*cos(rotation*3.14/180) + xO*sin(rotation*3.14/180);
    return Y;
}
float GL_Orbit::getY_Angle(float angle){
    float xO = semiMajor * cos(angle*3.14/180);
    float yO = semiMinor * sin(angle*3.14/180);
    float Y = yO;//yO*cos(rotation*3.14/180) + xO*sin(rotation*3.14/180);
    return Y;
}
float GL_Orbit::getY_CurrentAngle(){
    //float xO = semiMajor * cos(lastAngle*3.14/180);
    //float yO = semiMinor * sin(lastAngle*3.14/180);
    //float Y = yO;//*cos(rotation*3.14/180) + xO*sin(rotation*3.14/180);
    return pos.y();
}


/*----------------------*
 *   SETTER FUNCTIONS   *
 *----------------------*/
/*
 * Initialization function that prepares the orbit object for render.
 */
void GL_Orbit::prepare(){
    shaderProgram = new QOpenGLShaderProgram();
    shaderProgram->create();
    shaderProgram->addShaderFromSourceCode(QOpenGLShader::Vertex,vertexSource);
    shaderProgram->addShaderFromSourceCode(QOpenGLShader::Fragment,fragmentSource);
    shaderProgram->link();

    m_positionAttribute = shaderProgram->attributeLocation("posAttr");
    m_colorUniform = shaderProgram->uniformLocation("color");
    m_projectionMatrixUniform = shaderProgram->uniformLocation("matrix");
    m_modelMatrixUniform = shaderProgram->uniformLocation("model");

    VAO.destroy();
    VAO.create();
    VAO.bind();

    VBO = new QOpenGLBuffer();
    VBO->create();
    VBO->bind();
    VBO->allocate(vertices.data(), vertices.size() * sizeof(GLfloat));

    VAO.release();
}

/*
 * Increases the current orbit angle based on render time.
 */
void GL_Orbit::increaseAngle(double timeRatio){
    double A = completeSurface * timeRatio/orbitalPeriod;
    double angle = (360*A)/(3.14*semiMajor*semiMajor);
    this->lastAngle += angle;
    if(lastAngle >= 360) lastAngle -= 360;
}

void GL_Orbit::calculateOrbit(double timeStep){
    double step = fmin(0.001, timeStep);

    if(this->semiMajor > 0 ){
        for(double i=0 ; i<timeStep ; i+=step){
            // Get normalize Position vector (R)
            QVector3D normPos = pos;
            normPos.normalize();

            // Get Force vector (F)
            QVector3D F = -G*M*m*(normPos/(pos.length()*pos.length())) ;

            // Get new Momentum vector (P)
            QVector3D vec = this->p + F*step;

            // Get new Position vector (R)
            QVector3D position = pos + vec*step/m;

            p = vec;
            pos = position;
        }
    }
}

/*----------------------*
 *   OPENGL FUNCTIONS   *
 *----------------------*/
void GL_Orbit::render(QMatrix4x4 modelMatrix, QMatrix4x4 projectionViewMatrix){
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();

    f->glEnable(GL_LINE_SMOOTH);
    f->glDisable(GL_CULL_FACE);
    f->glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

    f->glEnable(GL_MULTISAMPLE);
    VAO.bind();
    VBO->bind();
    shaderProgram->bind();

    f->glEnableVertexAttribArray(0);
    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (void*)0);

    shaderProgram->setUniformValue(m_modelMatrixUniform, modelMatrix);
    shaderProgram->setUniformValue(m_projectionMatrixUniform, projectionViewMatrix);
    shaderProgram->setUniformValue(m_colorUniform, QVector3D(1,1,1));

    f->glDrawArrays(GL_QUADS, 0, vertices.size()/sizeof(float));

    shaderProgram->release();
    VAO.release();

    f->glEnable(GL_CULL_FACE);
    f->glDisable(GL_LINE_SMOOTH);
    f->glDisable(GL_MULTISAMPLE);
}
