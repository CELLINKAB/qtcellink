TARGET = qtcellinknativeplugin
TARGETPATH = QtCellink/Native
IMPORT_VERSION = 1.0

QT += qml quick
QT_PRIVATE += core-private gui-private qml-private quick-private quicktemplates2-private

DEFINES += QT_NO_CAST_TO_ASCII QT_NO_CAST_FROM_ASCII

OTHER_FILES += \
    qmldir

SOURCES += \
    $$PWD/qtcellinknativeplugin.cpp

include(native.pri)

CONFIG += no_cxx_module
load(qml_plugin)
