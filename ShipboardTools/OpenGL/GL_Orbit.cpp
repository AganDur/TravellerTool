#include "GL_Orbit.h"

GL_Orbit::GL_Orbit(QVector3D center, float semiMajor, float semiMinor, int rotation): GL_Object{} {
    this->center=center;
    this->semiMajor = semiMajor;
    this->semiMinor = semiMinor;
    this->rotation = rotation;


    // When the orbit is a true circle
    if(semiMinor==semiMajor){
        eccentricity = 0;
        distanceToFocus = 0;
        focus1 = center;
        focus2 = center;
    }

    // When the orbit is an ellipsis
    else{
        eccentricity = sqrt(1 - (semiMajor*semiMajor - semiMinor*semiMinor));

        float c2 = (semiMajor*semiMajor) - (semiMinor*semiMinor);
        float c1 = sqrt(c2);
        distanceToFocus = c1;

        QVector3D f = center;
        f.setX(center.x() - c1);
        focus1 = f;

        f.setX(center.x() + c1);
        focus2 = f;
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
    initializeOpenGLFunctions();

}

GL_Orbit::GL_Orbit(GL_Orbit &o): GL_Object{}{
    this->semiMajor = o.semiMajor;
    this->semiMinor = o.semiMinor;
    this->center = o.center;
    this->eccentricity = o.eccentricity;
    this->distanceToFocus = o.distanceToFocus;
    this->rotation = o.rotation;
    this->focus1 = o.focus1;
    this->focus2 = o.focus2;

    this->vertices = o.vertices;

    this->color = o.color;
    this->completeSurface = o.completeSurface;
    this->lastAngle = o.lastAngle;
    this->orbitalPeriod = o.orbitalPeriod;

    initializeOpenGLFunctions();

    /*
    VAO.create();
    VAO.bind();

    // Prepare Shader
    shaderProgram = new QOpenGLShaderProgram();
    shaderProgram->create();
    QOpenGLShader vertexShader = QOpenGLShader(QOpenGLShader::Vertex);
    QOpenGLShader fragmentShader = QOpenGLShader(QOpenGLShader::Fragment);
    vertexShader.compileSourceCode(vertexSource);
    fragmentShader.compileSourceCode(fragmentSource);
    shader->addShader(&vertexShader);
    shader->addShader(&fragmentShader);
    shader->link();

    m_posAttr = shader->attributeLocation("posAttr");
    m_matrixUniform = shader->uniformLocation("matrix");
    m_colorUniform = shader->uniformLocation("color");

    VBO = new QOpenGLBuffer();
    VBO->create();
    VBO->bind();
    VBO->allocate(vertices.data(), vertices.size()*sizeof(float));
    VAO.release();
    */
}


float GL_Orbit::getX_NoAngle(){
    float xO = semiMajor;
    float yO = 0;
    float X = xO*cos(rotation*3.14/180) - yO*sin(rotation*3.14/180);
    return X;
}

float GL_Orbit::getY_NoAngle(){
    float xO = semiMajor;
    float yO = 0;
    float Y = yO*cos(rotation*3.14/180) + xO*sin(rotation*3.14/180);
    return Y;
}
float GL_Orbit::getX_Angle(float angle){
    float xO = semiMajor * cos(angle*3.14/180);
    float yO = semiMinor * sin(angle*3.14/180);
    float X = xO*cos(rotation*3.14/180) - yO*sin(rotation*3.14/180);
    return X;
}

float GL_Orbit::getY_Angle(float angle){
    float xO = semiMajor * cos(angle*3.14/180);
    float yO = semiMinor * sin(angle*3.14/180);
    float Y = yO*cos(rotation*3.14/180) + xO*sin(rotation*3.14/180);
    return Y;
}

float GL_Orbit::getY_CurrentAngle(){
    float xO = semiMajor * cos(lastAngle*3.14/180);
    float yO = semiMinor * sin(lastAngle*3.14/180);
    float Y = yO*cos(rotation*3.14/180) + xO*sin(rotation*3.14/180);
    return Y;
}

float GL_Orbit::getX_CurrentAngle(){
    float xO = semiMajor * cos(lastAngle*3.14/180);
    float yO = semiMinor * sin(lastAngle*3.14/180);
    float X = xO*cos(rotation*3.14/180) - yO*sin(rotation*3.14/180);
    return X;
}

void GL_Orbit::increaseAngle(double timeRatio){
    double A = completeSurface * timeRatio/orbitalPeriod;
    double angle = (360*A)/(3.14*semiMajor*semiMajor);
    this->lastAngle += angle;
    if(lastAngle >= 360) lastAngle -= 360;
}

void GL_Orbit::render(QMatrix4x4 matrix){
    if(!prepared){
        compileShaders("orbit", "orbit");
        prepared = true;
    }

    VAO.bind();
    VBO->bind();
    shaderProgram->bind();

    shaderProgram->setUniformValue(m_matrixUniform, matrix);
    shaderProgram->setUniformValue(m_colorUniform, this->color);

    glVertexAttribPointer(m_positionAttribute, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    shaderProgram->enableAttributeArray(m_positionAttribute);

    glDrawArrays(GL_QUADS, 0, vertices.size()/sizeof(float));
    VAO.release();
    shaderProgram->release();
}
