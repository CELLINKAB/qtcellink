TARGET = qtcellinkmenusplugin
TARGETPATH = QtCellink/Menus
IMPORT_VERSION = 1.0

QT += qml quick
QT_PRIVATE += core-private gui-private qml-private quick-private quicktemplates2-private

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

HEADERS += \
    $$PWD/iconloader.h \
    $$PWD/nativemenu.h \
    $$PWD/nativemenubar.h \
    $$PWD/nativemenuitem.h \
    $$PWD/nativemenuseparator.h

SOURCES += \
    $$PWD/iconloader.cpp \
    $$PWD/nativemenu.cpp \
    $$PWD/nativemenubar.cpp \
    $$PWD/nativemenuitem.cpp \
    $$PWD/nativemenuseparator.cpp \
    $$PWD/qtcellinkmenusplugin.cpp

CONFIG += no_cxx_module
load(qml_plugin)
