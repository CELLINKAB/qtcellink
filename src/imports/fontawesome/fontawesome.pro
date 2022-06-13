TARGET = qtcellinkfontawesomeplugin
TARGETPATH = QtCellink/FontAwesome
IMPORT_VERSION = 1.0

QT += qml

DEFINES += QT_NO_CAST_TO_ASCII QT_NO_CAST_FROM_ASCII

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
