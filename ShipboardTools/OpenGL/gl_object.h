#ifndef GL_OBJECT_H
#define GL_OBJECT_H

#include "GL_Mesh.h"

#include <vector>
#include <string>

#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QImage>

class QOpenGLTexture;

class GL_Object: protected QOpenGLFunctions {
/*------------------*
 *   CONSTRUCTORS   *
 *------------------*/
public:
    GL_Object();
    GL_Object(GL_Object &object);
    virtual ~GL_Object();

    void setParents(std::vector<GL_Object*> parents);
    void addParent(GL_Object *parent);
    QVector3D getParentsCenter();

/*------------------------*
 *   OPEN GL PARAMETERS   *
 *------------------------*/
protected:
    /*
     * Trackers for textures and meshes already loaded,
     * allows reusing textures and meshes instead of reading
     * from file everytime.
     */
    static std::vector<std::string> texturesLoaded_Names;
    static std::vector<QImage> texturesLoaded;
    static std::vector<GL_Mesh> preloadedMeshes;

    /*
     * Vertex and index data for the mesh,
     * indices might be unused for a given object.
     */
    std::vector<GLfloat> vertices;
    std::vector<unsigned int> indices;

    std::vector<GL_Object*> parents = std::vector<GL_Object*>();

    QOpenGLTexture *texture;

    QOpenGLShaderProgram *shaderProgram;

    /*
     * OpenGL buffers necessary for rendering
     */
    QOpenGLVertexArrayObject VAO; // VAO handles the context for rendering, to avoid bind all the buffers everytime
    QOpenGLBuffer *VBO; // VBO handles the Vertex data buffer
    QOpenGLBuffer *EBO; // EBO handles the Index data buffer when necessary


/*-----------------------*
 *   OPEN GL FUNCTIONS   *
 *-----------------------*/
public:
    virtual void compileShaders(std::string vertexShaderName, std::string fragmentShaderName);

    void loadMesh(std::string meshName);
    void loadTexture(std::string textureName);

    virtual void render(QMatrix4x4 projectionViewMatrix, QVector3D ambientLight, QVector3D diffuseLight);
    virtual void updateTime(double timeRatio);

    virtual QVector3D getColor();

    virtual QVector3D getPosition();
};

#endif // GL_OBJECT_H
