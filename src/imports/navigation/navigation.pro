TARGET = qtcellinknavigationplugin
TARGETPATH = QtCellink/Navigation
IMPORT_VERSION = 1.0

QT += qml quick
QT_PRIVATE += core-private gui-private qml-private quick-private

OTHER_FILES += \
    qmldir

SOURCES += \
    $$PWD/qtcellinknavigationplugin.cpp

include(navigation.pri)

CONFIG += no_cxx_module
load(qml_plugin)
