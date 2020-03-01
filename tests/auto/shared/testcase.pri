TEMPLATE = app
QT += testlib
DEFINES += PLUGIN_PATH="\\\"$$BUILD_TREE/plugins\\\""
CONFIG += testcase link_prl
macos:CONFIG -= app_bundle
linux:QMAKE_RPATHDIR += $$BUILD_TREE/lib

INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/qtest_fuzzy.h \
    $$PWD/qtest_json.h \
    $$PWD/serialtestcase.h \
    $$PWD/testcase.h
