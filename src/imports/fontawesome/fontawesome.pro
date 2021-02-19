TARGET = qtcellinkfontawesomeplugin
TARGETPATH = QtCellink/FontAwesome
IMPORT_VERSION = 1.0
load(qml_plugin)

QT += qml

DEFINES += QT_NO_CAST_TO_ASCII QT_NO_CAST_FROM_ASCII

QML_FILES += \
    $$PWD/FontAwesome.qml

OTHER_FILES += \
    $$PWD/qmldir \
    $$QML_FILES

SOURCES += \
    $$PWD/qtcellinkfontawesomeplugin.cpp

RESOURCES += \
    fontawesome.qrc

CONFIG += no_cxx_module builtin_resources qtquickcompiler

### TODO: fix qml_module.prf (no way to turn off install_qml_files)
qmldir.files = $$qmldir_file
