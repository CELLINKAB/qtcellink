TARGET = amfgeometryloader
QT += core-private 3dcore 3dcore-private 3drender 3drender-private
CONFIG += assimp

PLUGIN_TYPE = geometryloaders
PLUGIN_CLASS_NAME = AmfGeometryLoaderPlugin
load(qt_build_config)
load(qt_plugin)

# Conan setup
OTHER_FILES += $$PWD/conanfile.txt
system("conan install . -g qmake -if $$BUILD_TREE")
CONFIG += conan_basic_setup
include($$BUILD_TREE/conanbuildinfo.pri)
linux:QMAKE_RPATHDIR += $$CONAN_LIBSSH2_ROOT/lib $$CONAN_ASSIMP_ROOT/lib
# end Conan Setup

HEADERS += \
    amfgeometryloader.h \
    basegeometryloader_p.h

SOURCES += \
    amfgeometryloader.cpp \
    amfgeometryloaderplugin.cpp \
    basegeometryloader.cpp

DISTFILES += \
    amf.json \
    conanfile.txt
