INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD
QT += core-private gui-private
CONFIG += no_private_qt_headers_warning


!win32 {
    HEADERS += \
        $$PWD/qt3dwindow.h

    SOURCES += \
        $$PWD/qt3dwindow.cpp
}
