TARGET = qtcellinkextrasplugin
TARGETPATH = QtCellink/Extras
IMPORT_VERSION = 1.0


QT += qml quick
QT_PRIVATE += core-private gui-private qml-private quick-private quicktemplates2-private

versionAtLeast(QT_VERSION, 5.14.0) {
    message("Using qmlmodels library as we are Qt 5.14 or later")
    QT += qmlmodels qmlmodels-private
}

versionAtLeast(QT_VERSION, 5.15.0) {
    # QmlModelObjectAttached in private does not have EXPORT declataion
    win32:warning("Disabling qtcellinkextrasplugin due to DLL link issues on Windows")
    requires(!win32)
}

CONFIG += no_cxx_module

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
    $$PWD/mnemoniclabel.h \
    $$PWD/navigationgroup.h \
    $$PWD/navigationitem.h \
    $$PWD/navigationstack.h \
    $$PWD/nodedelegate.h \
    $$PWD/nodeitem.h \
    $$PWD/nodeview.h \
    $$PWD/paddedrectangle.h \
    $$PWD/rect.h \
    $$PWD/yoctolicense.h \
    $$PWD/yoctolicensemodel.h

SOURCES += \
    $$PWD/color.cpp \
    $$PWD/colorimage.cpp \
    $$PWD/componentmodel.cpp \
    $$PWD/filtermodel.cpp \
    $$PWD/iconimage.cpp \
    $$PWD/iconlabel.cpp \
    $$PWD/keyboard.cpp \
    $$PWD/mnemoniclabel.cpp \
    $$PWD/navigationgroup.cpp \
    $$PWD/navigationitem.cpp \
    $$PWD/navigationstack.cpp \
    $$PWD/nodedelegate.cpp \
    $$PWD/nodeitem.cpp \
    $$PWD/nodeview.cpp \
    $$PWD/paddedrectangle.cpp \
    $$PWD/qtcellinkextrasplugin.cpp \
    $$PWD/rect.cpp \
    $$PWD/yoctolicensemodel.cpp

load(qml_plugin)
