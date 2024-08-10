QT       += core gui opengl
QT       += openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += Libs\Include

SOURCES += \
    ApplicationManager.cpp \
    Data/Sector.cpp \
    Data/Subsector.cpp \
    Data/System.cpp \
    Dialogs/Dialog_ShipSelection.cpp \
    Dialogs/Dialog_SystemSelection.cpp \
    Globals.cpp \
    Graphics/DeleteElementsWorker.cpp \
    Graphics/Hexagon.cpp \
    Graphics/MapView.cpp \
    Graphics/SectorRectangle.cpp \
    OpenGL/GL_Camera.cpp \
    OpenGL/GL_Instanced.cpp \
    OpenGL/GL_Mesh.cpp \
    OpenGL/GL_Orbit.cpp \
    OpenGL/GL_Planet.cpp \
    OpenGL/GL_Ship.cpp \
    OpenGL/GL_ShipViewerWidget.cpp \
    OpenGL/GL_Star.cpp \
    OpenGL/GL_SystemViewerWidget.cpp \
    OpenGL/GL_Unique.cpp \
    OpenGL/Gl_Widget.cpp \
    OpenGL/GL_Object.cpp \
    Options_FolderLine.cpp \
    Window_Options.cpp \
    Window_SectorMap.cpp \
    Window_ShipViewer.cpp \
    Window_SystemViewer.cpp \
    main.cpp \
    Launcher.cpp

HEADERS += \
    ApplicationManager.h \
    Data/Sector.h \
    Data/Subsector.h \
    Data/System.h \
    Dialogs/Dialog_ShipSelection.h \
    Dialogs/Dialog_SystemSelection.h \
    GlobalData.h \
    Globals.h \
    Graphics/DeleteElementsWorker.h \
    Graphics/Hexagon.h \
    Graphics/MapView.h \
    Graphics/SectorRectangle.h \
    Launcher.h \
    OpenGL/GL_Camera.h \
    OpenGL/GL_Instanced.h \
    OpenGL/GL_Mesh.h \
    OpenGL/GL_Orbit.h \
    OpenGL/GL_Planet.h \
    OpenGL/GL_Ship.h \
    OpenGL/GL_ShipViewerWidget.h \
    OpenGL/GL_Star.h \
    OpenGL/GL_SystemViewerWidget.h \
    OpenGL/GL_Unique.h \
    OpenGL/Gl_Widget.h \
    OpenGL/GL_Object.h \
    Options_FolderLine.h \
    Window_Options.h \
    Window_SectorMap.h \
    Window_ShipViewer.h \
    Window_SystemViewer.h

FORMS += \
    Dialogs/Dialog_ShipSelection.ui \
    Dialogs/Dialog_SystemSelection.ui \
    Launcher.ui \
    Window_Options.ui \
    Window_SectorMap.ui \
    Window_ShipViewer.ui \
    Window_SystemViewer.ui

LIBS += -lOpenGL32
LIBS += User32.lib
LIBS += -lglu32
LIBS += $$PWD\Libs\Libs\assimp-vc143-mt.lib

TRANSLATIONS += \
    ShipboardTools_en_GB.ts
#CONFIG += lrelease
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
COPIES += sectors



CONFIG(debug, debug|release){
    glShaders.path = $$OUT_PWD/debug/Assets/Shaders
    glMeshes.path = $$OUT_PWD/debug/Assets/Meshes
    glTextures.path = $$OUT_PWD/debug/Assets/Textures
    systems.path = $$OUT_PWD/debug/Systems
    sectors.path = $$OUT_PWD/debug/Sectors
    #icons.path = $$OUT_PWD/debug/Icons
    dllFiles.path = $$OUT_PWD/debug
}
CONFIG(release, debug|release) {
    glShaders.path = $$OUT_PWD/release/Assets/Shaders
    glMeshes.path = $$OUT_PWD/release/Assets/Meshes
    glTextures.path = $$OUT_PWD/release/Assets/Textures
    systems.path = $$OUT_PWD/release/Systems
    sectors.path = $$OUT_PWD/release/Sectors
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
sectors.files = $$files(Sectors/*.json)

# LIST OF ICONS TO COPY
icons.path = $$OUT_PWD/Icons
icons.files = $$files(Icons/*.jpg)
#icons.files = $$files(Icons/*.png)

DISTFILES += \
    Assets/Shaders/test.frag \
    Assets/Shaders/test.vert
