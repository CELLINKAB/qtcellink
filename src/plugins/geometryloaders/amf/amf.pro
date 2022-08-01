TARGET = amfgeometryloader
QT += core-private 3dcore 3dcore-private 3drender 3drender-private
CONFIG += assimp

INCLUDEPATH += $$MOC_DIR

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
load(qt_build_config)
load(qt_plugin)
