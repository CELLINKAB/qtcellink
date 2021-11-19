TARGET = qtcellinkmaterialplugin
TARGETPATH = QtCellink/Material
IMPORT_VERSION = 1.0

QT += qml

OTHER_FILES += \
    $$PWD/qmldir

HEADERS += \
    $$PWD/material.h

SOURCES += \
    $$PWD/material.cpp \
    $$PWD/qtcellinkmaterialplugin.cpp

RESOURCES += \
    material.qrc

CONFIG += no_cxx_module
load(qml_plugin)
