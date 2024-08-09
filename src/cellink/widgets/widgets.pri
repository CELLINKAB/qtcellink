INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD
QT += widgets

HEADERS += \
    $$PWD/codeeditor_ci.h \
    $$PWD/doublespinbox_ci.h \
    $$PWD/highlightlines_ci.h \
    $$PWD/progressindicator_ci.h \
    $$PWD/rangeslider_ci.h \
    $$PWD/spinbox_ci.h

# _ci suffix to avoid .obj clash with qtcellinkinternal/widgets/ .cpp files with same name
SOURCES += \
    $$PWD/codeeditor_ci.cpp \
    $$PWD/doublespinbox_ci.cpp \
    $$PWD/progressindicator_ci.cpp \
    $$PWD/rangeslider_ci.cpp \
    $$PWD/spinbox_ci.cpp

include($$PWD/../core/global.pri)
INCLUDEPATH += \
    $$PWD/../../../..
