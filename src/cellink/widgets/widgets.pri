INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD
QT += widgets

HEADERS += \
    $$PWD/codeeditor.h \
    $$PWD/doublespinbox.h \
    $$PWD/highlightlines.h \
    $$PWD/progressindicator.h \
    $$PWD/rangeslider.h \
    $$PWD/spinbox.h

SOURCES += \
    $$PWD/codeeditor.cpp \
    $$PWD/doublespinbox.cpp \
    $$PWD/progressindicator.cpp \
    $$PWD/rangeslider.cpp \
    $$PWD/spinbox.cpp

include($$PWD/../core/global.pri)
INCLUDEPATH += \
    $$PWD/../../../..
