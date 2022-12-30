QT       += core gui opengl
QT       += openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += Libs\Include

SOURCES += \
    main.cpp \
    Launcher.cpp

HEADERS += \
    Launcher.h

FORMS += \
    Launcher.ui

LIBS += -lOpenGL32
LIBS += -lglu32
LIBS += $$PWD\Libs\Libs\assimp-vc143-mt.lib
LIBS += User32.lib

TRANSLATIONS += \
    ShipboardTools_en_GB.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#DISTFILES += \
#    Assets/Shaders/Shader.frag \
#    Assets/Shaders/Shader.vert \
#    Assets/Shaders/starShader.vert\
#    Assets/Shaders/starShader.frag\
#    Assets/Shaders/planetShader.vert\
#    Assets/Shaders/planetShader.frag\
#    Assets/Shaders/texture_shader.vert\
#    Assets/Shaders/texture_shader.frag

CONFIG += file_copies

COPIES += dllFiles
COPIES += glShaders
COPIES += glMeshes
COPIES += glTextures
COPIES += systems
COPIES += icons



@debug{
    glShaders.path = $$OUT_PWD/debug/Assets/Shaders
    glMeshes.path = $$OUT_PWD/debug/Assets/Meshes
    glTextures.path = $$OUT_PWD/debug/Assets/Textures
    systems.path = $$OUT_PWD/debug/Systems
    #icons.path = $$OUT_PWD/debug/Icons
    dllFiles.path = $$OUT_PWD/debug
}
release {
    glShaders.path = $$OUT_PWD/release/Assets/Shaders
    glMeshes.path = $$OUT_PWD/release/Assets/Meshes
    glTextures.path = $$OUT_PWD/release/Assets/Textures
    systems.path = $$OUT_PWD/release/Systems
    #icons.path = $$OUT_PWD/release/Icons
    dllFiles.path = $$OUT_PWD/release
}

dllFiles.files = $$files(assimp-vc143-mt.dll)

# LIST OF SHADER FILES TO COPY
glShaders.files = $$files(Assets/Shaders/*.vert)
glShaders.files += $$files(Assets/Shaders/*.frag)

# LIST OF MESH FILES TO COPY
glMeshes.files = $$files(Assets/Meshes/*.obj)

# LIST OF TEXTURE FILES TO COPY
glTextures.files = $$files(Assets/Textures/*.jpg)

# LIST OF SYSTEM FILES TO COPY
systems.files = $$files(Systems/*.json)

# LIST OF ICONS TO COPY
icons.path = $$OUT_PWD/Icons
icons.files = $$files(Icons/*.jpg)
#icons.files = $$files(Icons/*.png)
