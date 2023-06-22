#include "GL_Unique.h"
#include "GL_Object.h"

GL_Unique::GL_Unique(std::string meshName, QVector3D color) : GL_Object{} {
    loadMesh(meshName);
    this->color = color;

    //VAO.create();
    VAO.bind();

    VBO = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    VBO->create();
    VBO->bind();
    VBO->allocate(this->vertices.data(), this->vertices.size()*sizeof(GLfloat));
    VBO->setUsagePattern(QOpenGLBuffer::StaticDraw);

    EBO = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    EBO->create();
    EBO->bind();
    EBO->allocate(this->indices.data(), this->indices.size()*sizeof(unsigned int));

    VAO.release();
}

GL_Unique::GL_Unique(std::vector<GLfloat> vertices, std::vector<unsigned int> indices, QVector3D color): GL_Object{}, color{color}{
    this->vertices = vertices;
    this->indices = indices;
    this->color = color;

    //VAO.create();
    VAO.bind();

    //VBO = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    //VBO->create();
    VBO->bind();
    VBO->setUsagePattern(QOpenGLBuffer::StaticDraw);
    VBO->allocate(this->vertices.data(), this->vertices.size()*sizeof(GLfloat));

    //EBO = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    //EBO->create();
    EBO->bind();
    EBO->allocate(this->indices.data(), this->indices.size()*sizeof(unsigned int));

    VAO.release();
}

GL_Unique::~GL_Unique(){

}

void GL_Unique::compileShaders(std::string vertexShaderName, std::string fragmentShaderName){
    GL_Object::compileShaders(vertexShaderName, fragmentShaderName);
}

QVector3D GL_Unique::getColor(){
    return color;
}

