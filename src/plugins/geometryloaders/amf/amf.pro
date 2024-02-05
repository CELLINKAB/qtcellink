TARGET = amfgeometryloader
QT += core-private 3dcore 3dcore-private 3drender 3drender-private
CONFIG += assimp

load(assimp)

versionAtLeast(QT_VERSION, "6.0.0") {
   CONFIG += plugin
} else {
   load(qt_build_config)
   load(qt_plugin)
}

INCLUDEPATH += \
    $$MOC_DIR

HEADERS += \
    amfgeometryloader.h \
    basegeometryloader_p.h

SOURCES += \
    amfgeometryloader.cpp \
    amfgeometryloaderplugin.cpp \
    basegeometryloader.cpp

DISTFILES += \
    amf.json

PLUGIN_TYPE = geometryloaders
PLUGIN_CLASS_NAME = AmfGeometryLoaderPlugin


exists($$BUILD_TREE/conanbuildinfo.pri) {
    CONFIG += conan_basic_setup
    include($$BUILD_TREE/conanbuildinfo.pri)
}
