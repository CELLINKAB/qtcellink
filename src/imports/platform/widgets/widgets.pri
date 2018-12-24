QT += widgets
DEPENDPATH += $$PWD

HEADERS += \
    $$PWD/qwidgetplatform_p.h

qtConfig(menu) {
    HEADERS += \
        $$PWD/qwidgetplatformmenu_p.h \
        $$PWD/qwidgetplatformmenuitem_p.h
    SOURCES += \
        $$PWD/qwidgetplatformmenu.cpp \
        $$PWD/qwidgetplatformmenuitem.cpp
}
