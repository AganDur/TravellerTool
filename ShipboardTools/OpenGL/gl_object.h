#ifndef GL_OBJECT_H
#define GL_OBJECT_H

#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QImage>

#include <vector>
#include <string>

class QOpenGLTexture;

class GL_Object: protected QOpenGLFunctions {
/*------------------*
 *   CONSTRUCTORS   *
 *------------------*/
public:
    GL_Object(std::string vertexShaderName, std::string fragmentShaderName);
    virtual ~GL_Object();

/*------------------------*
 *   OPEN GL PARAMETERS   *
 *------------------------*/
protected:
    //static std::vector<std::string> texturesLoaded_Names;
    //static std::vector<QImage> texturesLoaded;

    std::vector<GLfloat> vertices;
    std::vector<unsigned int> indices;

    QOpenGLTexture *texture;

    QOpenGLShaderProgram *shaderProgram;

    QOpenGLVertexArrayObject VAO;
    QOpenGLBuffer *VBO;
    QOpenGLBuffer *EBO;

/*-----------------------*
 *   OPEN GL FUNCTIONS   *
 *-----------------------*/
public:
    void compileShaders(std::string vertexShaderName, std::string fragmentShaderName);

    void loadMesh(std::string meshName);
    void loadTexture(std::string textureName);

    virtual void render(QMatrix4x4 projectionViewMatrix, QVector3D ambientLight, QVector3D diffuseLight);
    virtual void updateTime(double timeRatio);

    virtual QVector3D getColor();
};

#endif // GL_OBJECT_H
