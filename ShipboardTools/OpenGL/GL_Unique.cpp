#include "GL_Unique.h"
#include "GL_Object.h"

/*------------------*
 *   CONSTRUCTORS   *
 *------------------*/
// Constructor using mesh name
GL_Unique::GL_Unique(std::string meshName, QVector3D color, std::string name) : GL_Object{} {
    loadMesh(meshName);
    this->color = color;
    this->name = name;

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

// Constructor using preloaded mesh data (vertices and indices)
GL_Unique::GL_Unique(std::vector<GLfloat> vertices, std::vector<unsigned int> indices, QVector3D color, std::string name): GL_Object{}, color{color}{
    this->vertices = vertices;
    this->indices = indices;
    this->color = color;
    this->name = name;

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

// Default class Destructor
GL_Unique::~GL_Unique(){

}

/*-----------------------*
 *   OPEN GL FUNCTIONS   *
 *-----------------------*/
void GL_Unique::compileShaders(std::string vertexShaderName, std::string fragmentShaderName){
    GL_Object::compileShaders(vertexShaderName, fragmentShaderName);
}

QVector3D GL_Unique::getColor(){
    return color;
}

std::string GL_Unique::getName(){
    return name;
}

