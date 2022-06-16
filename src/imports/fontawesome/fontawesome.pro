TARGET = qtcellinkfontawesomeplugin
TARGETPATH = QtCellink/FontAwesome
IMPORT_VERSION = 1.0

QT += qml

DEFINES += QT_NO_CAST_TO_ASCII QT_NO_CAST_FROM_ASCII

win32 {
    system(powershell -Command cp $$PWD/qmldir.win $$PWD/qmldir)
} else {
    system(cp $$PWD/qmldir.linux $$PWD/qmldir)
}

QML_FILES += \
    $$files(*.qml)

OTHER_FILES += \
    $$PWD/qmldir \
    $$QML_FILES

SOURCES += \
    $$PWD/qtcellinkfontawesomeplugin.cpp

RESOURCES += \
    $$PWD/fontawesome.qrc

CONFIG += qtquickcompiler no_cxx_module
linux: CONFIG += builtin_resources

load(qml_plugin)

### TODO: fix qml_module.prf (no way to turn off install_qml_files)
qmldir.files = $$qmldir_file

DISTFILES += \
    qmldir.linux \
    qmldir.win
