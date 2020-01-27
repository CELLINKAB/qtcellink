CONFIG += qmltestcase

IMPORTPATH += $$BUILD_TREE/qml
DEFINES += IMPORT_PATH="\\\"$$BUILD_TREE/qml\\\""

HEADERS += \
    $$PWD/qmltestcase.h

include(testcase.pri)
