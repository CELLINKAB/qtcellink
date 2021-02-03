TARGET = qtcellinkextrasplugin
TARGETPATH = QtCellink/Extras
IMPORT_VERSION = 1.0

QT += qml quick
QT_PRIVATE += core-private gui-private qml-private quick-private quicktemplates2-private

DEFINES += QT_NO_CAST_TO_ASCII QT_NO_CAST_FROM_ASCII

OTHER_FILES += \
    $$PWD/qmldir

HEADERS += \
    $$PWD/color.h \
    $$PWD/colorimage.h \
    $$PWD/componentmodel.h \
    $$PWD/filtermodel.h \
    $$PWD/iconimage.h \
    $$PWD/iconimage_p.h \
    $$PWD/iconlabel.h \
    $$PWD/iconlabel_p.h \
    $$PWD/keyboard.h \
    $$PWD/licensemodel.h \
    $$PWD/mnemoniclabel.h \
    $$PWD/navigationgroup.h \
    $$PWD/navigationitem.h \
    $$PWD/navigationstack.h \
    $$PWD/nodedelegate.h \
    $$PWD/nodeitem.h \
    $$PWD/nodeview.h \
    $$PWD/paddedrectangle.h \
    $$PWD/rect.h \
    $$PWD/yoctolicense.h

SOURCES += \
    $$PWD/color.cpp \
    $$PWD/colorimage.cpp \
    $$PWD/componentmodel.cpp \
    $$PWD/filtermodel.cpp \
    $$PWD/iconimage.cpp \
    $$PWD/iconlabel.cpp \
    $$PWD/keyboard.cpp \
    $$PWD/licensemodel.cpp \
    $$PWD/mnemoniclabel.cpp \
    $$PWD/navigationgroup.cpp \
    $$PWD/navigationitem.cpp \
    $$PWD/navigationstack.cpp \
    $$PWD/nodedelegate.cpp \
    $$PWD/nodeitem.cpp \
    $$PWD/nodeview.cpp \
    $$PWD/paddedrectangle.cpp \
    $$PWD/qtcellinkextrasplugin.cpp \
    $$PWD/rect.cpp

CONFIG += no_cxx_module
load(qml_plugin)
