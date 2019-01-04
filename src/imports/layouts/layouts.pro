TARGET = cellinklayoutsplugin
TARGETPATH = Cellink/Layouts
IMPORT_VERSION = 1.0

QT += qml quick
QT_PRIVATE += core-private gui-private qml-private quick-private

DEFINES += QT_NO_CAST_TO_ASCII QT_NO_CAST_FROM_ASCII

OTHER_FILES += \
    $$PWD/qmldir

HEADERS += \
    $$PWD/layoutgroup.h

SOURCES += \
    $$PWD/cellinklayoutsplugin.cpp \
    $$PWD/layoutgroup.cpp

CONFIG += no_cxx_module
load(qml_plugin)
