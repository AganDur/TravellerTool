#include "GL_Object.h"

#include "Globals.h"

#include <QOpenGLShader>
#include <QOpenGLTexture>

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"


std::vector<std::string> GL_Object::texturesLoaded_Names = std::vector<std::string>();
std::vector<QImage> GL_Object::texturesLoaded = std::vector<QImage>();
std::vector<GL_Mesh> GL_Object::preloadedMeshes = std::vector<GL_Mesh>();


GL_Object::GL_Object() {
    shaderProgram = new QOpenGLShaderProgram();
    shaderProgram->create();

    // Create and Bind Vertex Array Object before setup
    VAO.create();
    VAO.bind();

    // Prepare Vertex Buffer Object
    VBO = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    VBO->create();
    VBO->bind();
    VBO->setUsagePattern(QOpenGLBuffer::StaticDraw);

    // Prepare Element Buffer Object
    EBO = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    EBO->create();
    EBO->bind();
    EBO->setUsagePattern(QOpenGLBuffer::StaticDraw);

    // Release Vertex Array Object after setup
    VAO.release();

    // Prepare QT openGL functionalities
    initializeOpenGLFunctions();
}

GL_Object::GL_Object(GL_Object &object){
    // Create and Bind Vertex Array Object before setup
    VAO.create();
    VAO.bind();

    // Prepare Vertex Buffer Object
    VBO = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    VBO->create();
    VBO->bind();
    VBO->setUsagePattern(QOpenGLBuffer::StaticDraw);

    // Prepare Element Buffer Object
    EBO = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    EBO->create();
    EBO->bind();
    EBO->setUsagePattern(QOpenGLBuffer::StaticDraw);

    // Release Vertex Array Object after setup
    VAO.release();

    // Prepare QT openGL functionalities
    initializeOpenGLFunctions();

    // Compile necessary shaders
    //compileShaders("", "");
}

GL_Object::~GL_Object() {
    //delete(shaderProgram);
    //delete(texture);
    //delete(VBO);
    //delete(EBO);
}

/**
 * @brief GL_Object::compileShaders
 * @param vertexShaderName
 * @param fragmentShaderName
 * Function to load and compile the necessary vertex and fragment shaders. If the object's shader program was already
 * created, it will be destroyed and recreated from scratch.
 */
void GL_Object::compileShaders(std::string vertexShaderName, std::string fragmentShaderName) {
    // Create Shader Program
    if(shaderProgram->isLinked()){
        shaderProgram->release();
        delete(shaderProgram);
        shaderProgram = new QOpenGLShaderProgram();
        shaderProgram->create();
    }

    // Load Vertex Shader
    QOpenGLShader vert(QOpenGLShader::Vertex);
    vert.compileSourceFile(QString::fromStdString(
       global::path() + "Assets/Shaders/"  + vertexShaderName + ".vert"
    ));

    // Load Fragment Shader
    QOpenGLShader frag(QOpenGLShader::Fragment);
    frag.compileSourceFile(QString::fromStdString(
       global::path() + "Assets/Shaders/"  + fragmentShaderName + ".frag"
    ));

    // Link Shaders
    shaderProgram->addShader(&vert);
    shaderProgram->addShader(&frag);

    // Compile Shader Program
    shaderProgram->link();
}

/**
 * @brief GL_Object::loadMesh
 * @param meshName
 * Function to load a mesh from file using the Assimp library and set the vertex and index data as necessary.
 */
void GL_Object::loadMesh(std::string meshName) {
    bool foundMesh = false;
    int meshIndex = 0;

    while(meshIndex<preloadedMeshes.size() && !foundMesh){
        if(preloadedMeshes[meshIndex].getName().compare(meshName) == 0) foundMesh = true;
        else meshIndex++;
    }

    // If the mesh already exists, get its values
    if(foundMesh){
        GL_Mesh mesh = preloadedMeshes[meshIndex];
        vertices = mesh.getVertices();
        indices = mesh.getIndices();
    }
    // Otherwise, load it from file
    else {
        Assimp::Importer importer;

        // Open the mesh file
        const aiScene* scene = importer.ReadFile(
            global::path() + "Assets/Meshes/" + meshName, aiProcess_Triangulate | aiProcess_FlipUVs
        );

        // Throw an error and return if the file was not successfully open
        // (File not open, incorrect flags or missing root)
        if(!scene || (scene->mFlags && AI_SCENE_FLAGS_INCOMPLETE) || !scene->mRootNode){
            qDebug() << "ERROR::ASSIMP::" << importer.GetErrorString();
            return;
        }

        aiMesh* meshData;
        meshData = scene->mMeshes[0];

        // Load and fill the vertex data
        for(unsigned int i=0 ; i < meshData->mNumVertices ; i++){
            // Load the Vertex Position data
            vertices.push_back(meshData->mVertices[i].x);
            vertices.push_back(meshData->mVertices[i].y);
            vertices.push_back(meshData->mVertices[i].z);

            // Load the Vertex UV data
            vertices.push_back(meshData->mTextureCoords[0][i].x);
            vertices.push_back(meshData->mTextureCoords[0][i].y);
        }

        // Load and fill the index data
        for(unsigned int i=0 ; i < meshData->mNumFaces ; i++ ){
            aiFace face = meshData->mFaces[i];
            for(unsigned int j=0 ; j < face.mNumIndices ; j++) indices.push_back(face.mIndices[j]);
        }

        GL_Mesh newMesh(meshName, vertices, indices);
        preloadedMeshes.push_back(newMesh);
    }

    // Prepare the buffers for rendering with the newly-loaded data
    VAO.bind();
    VBO->bind();
    EBO->bind();
    VBO->allocate(vertices.data(), vertices.size()*sizeof(GLfloat));
    EBO->allocate(indices.data(), indices.size()*sizeof(unsigned int));
    VAO.release();
}

/**
 * @brief GL_Object::loadTexture
 * @param textureName
 * Function used to set an object's texture. The texture can be obtained in two ways:
 *  - It can be loaded from file
 *  - If the texture has already been loaded once, the already-loaded data can be reused.
 */
void GL_Object::loadTexture(std::string textureName) {
    bool loaded = false;
    int textureIndex;
    int i=0;

    // Check if the texture has already been loaded
    while(i<texturesLoaded_Names.size() && !loaded) {
        std::string currentTextureName = texturesLoaded_Names.at(i);
        if(currentTextureName.compare(textureName)==0){
            qDebug() << "Texture " << QString::fromStdString(textureName) << " already loaded.";
            loaded = true;
            textureIndex = i;
        }
        i++;
    }

    // If the texture is known, get it from memory
    if(loaded) {
        this->texture = new QOpenGLTexture(texturesLoaded.at(textureIndex));
    }
    // Otherwise, load it from the file
    else {
        QImage textureImage;
        // Try to load the texture from file and add it to loaded textures
        if(textureImage.load(QString::fromStdString(global::path() + "Assets/Textures/" + textureName))) {
            texturesLoaded.push_back(textureImage);
            texturesLoaded_Names.push_back(textureName);
            this->texture = new QOpenGLTexture(textureImage);
        }
        else {
            qDebug() << "Error Loading the selected texture.";
        }
    }
    texture->bind();
}

void GL_Object::render(QMatrix4x4 projectionViewMatrix, QVector3D ambientLight, QVector3D diffuseLight){
    // TODO
    qDebug() << "GL_OBJECT.CPP RENDER()";
}

void GL_Object::updateTime(double timeRatio){
    // TODO
}

QVector3D GL_Object::getColor(){
    return QVector3D(0.0f,0.0f,0.0f);
}
