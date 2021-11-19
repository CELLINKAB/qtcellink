INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD
QT += core-private gui-private
CONFIG += no_private_qt_headers_warning

HEADERS += \
    $$PWD/qt3dwindow.h

SOURCES += \
    $$PWD/qt3dwindow.cpp

include($$PWD/../core/global.pri)
INCLUDEPATH += \
    $$PWD/../../../..
