INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD
QT += core-private gui-private
CONFIG += no_private_qt_headers_warning

HEADERS += \
    $$PWD/qt3dwindow.h \
    $$PWD/qt3dwindow_p.h

SOURCES += \
    $$PWD/qt3dwindow.cpp
