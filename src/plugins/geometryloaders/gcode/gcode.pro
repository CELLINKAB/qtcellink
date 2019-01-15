TARGET = gcodegeometryloader
QT += core-private 3dcore 3dcore-private 3drender 3drender-private

HEADERS += \
    gcodegeometryloader.h

SOURCES += \
    gcodegeometryloader.cpp \
    gcodegeometryloaderplugin.cpp

DISTFILES += \
    gcode.json

PLUGIN_TYPE = geometryloaders
PLUGIN_CLASS_NAME = GcodeGeometryLoaderPlugin
load(qt_build_config)
load(qt_plugin)
