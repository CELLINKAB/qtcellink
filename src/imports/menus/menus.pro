TARGET = qtcellinkmenusplugin
TARGETPATH = QtCellink/Menus
IMPORT_VERSION = 1.0

QT += qml

DEFINES += QT_NO_CAST_TO_ASCII QT_NO_CAST_FROM_ASCII

AUX_QML_FILES += \
    $$PWD/NativeMenu.qml \
    $$PWD/NativeMenuBar.qml \
    $$PWD/NativeMenuItem.qml \
    $$PWD/NativeMenuSeparator.qml \
    $$PWD/QuickMenu.qml \
    $$PWD/QuickMenuBar.qml \
    $$PWD/QuickMenuItem.qml \
    $$PWD/QuickMenuSeparator.qml

OTHER_FILES += \
    $$PWD/qmldir \
    $$AUX_QML_FILES

SOURCES += \
    $$PWD/qtcellinkmenusplugin.cpp

CONFIG += no_cxx_module
load(qml_plugin)
