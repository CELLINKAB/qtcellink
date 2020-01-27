TARGET = qtcellinklicenseplugin
TARGETPATH = QtCellink/License
IMPORT_VERSION = 1.0

QT += qml

OTHER_FILES += \
    $$PWD/qmldir

HEADERS += \
    $$PWD/license.h \
    $$PWD/licensemodel.h

SOURCES += \
    $$PWD/licensemodel.cpp \
    $$PWD/qtcellinklicenseplugin.cpp

CONFIG += no_cxx_module
load(qml_plugin)
