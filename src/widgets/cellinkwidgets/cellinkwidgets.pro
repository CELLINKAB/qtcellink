TARGET      = cellinkwidgets

CONFIG      += c++17 create_prl
QT          += widgets multimedia multimediawidgets designer 3dextras svg
DEFINES     += BUILD_CELLINKWIDGETS QT_DEPRECATED_WARNINGS
LIBS        += -L. -L$$BUILD_TREE/lib -L$$BUILD_TREE/plugins/designer
INCLUDEPATH += $$SOURCE_TREE/src/libs/heartwarecore/src \
               $$PWD/../../styles/cellinkstyles # style color only

load(designer)
load(copytobin)

linux:QMAKE_RPATHDIR += $$BUILD_TREE/bin

requires(!heartos)

PRECOMPILED_HEADER = \
    cellinkwidgets_stable.h

HEADERS     = \
    cellinkwidgets/buttonrow.h \
    cellinkwidgets/collapsebox.h \
    cellinkwidgets/combobox.h \
    cellinkwidgets/comboboxdelegate.h \
    cellinkwidgets/doublespinbox.h \
    cellinkwidgets/growablestackedwidget.h \
    cellinkwidgets/iconbutton.h \
    cellinkwidgets/menubutton.h \
    cellinkwidgets/menutabbuttons.h \
    cellinkwidgets/numberoffsetwidget.h \
    cellinkwidgets/paintedvideowidget.h \
    cellinkwidgets/paper.h \
    cellinkwidgets/popupbutton.h \
    cellinkwidgets/progressbar.h \
    cellinkwidgets/progresscircle.h \
    cellinkwidgets/progressindicator.h \
    cellinkwidgets/qt3dwidget.h \
    cellinkwidgets/qtdialogs.h \
    cellinkwidgets/roundedpopup.h \
    cellinkwidgets/sliderspinboxwidget.h \
    cellinkwidgets/spinbox.h \
    cellinkwidgets/styleinterface.h \
    cellinkwidgets/tabbuttons.h \
    cellinkwidgets/toggleswitch.h \
    cellinkwidgets/tooltabbuttons.h \
    cellinkwidgets/utils.h \
    cellinkwidgets/videowidget.h \
    cellinkwidgets_global.h \
    cellinkwidgets_stable.h

SOURCES     = \
    buttonrowplugin.cpp \
    cellinkwidgets/buttonrow.cpp \
    cellinkwidgets/collapsebox.cpp \
    cellinkwidgets/combobox.cpp \
    cellinkwidgets/comboboxdelegate.cpp \
    cellinkwidgets/doublespinbox.cpp \
    cellinkwidgets/growablestackedwidget.cpp \
    cellinkwidgets/iconbutton.cpp \
    cellinkwidgets/menubutton.cpp \
    cellinkwidgets/menutabbuttons.cpp \
    cellinkwidgets/numberoffsetwidget.cpp \
    cellinkwidgets/paintedvideowidget.cpp \
    cellinkwidgets/paper.cpp \
    cellinkwidgets/popupbutton.cpp \
    cellinkwidgets/progressbar.cpp \
    cellinkwidgets/progresscircle.cpp \
    cellinkwidgets/progressindicator.cpp \
    cellinkwidgets/qt3dwidget.cpp \
    cellinkwidgets/qtdialogs.cpp \
    cellinkwidgets/roundedpopup.cpp \
    cellinkwidgets/sliderspinboxwidget.cpp \
    cellinkwidgets/spinbox.cpp \
    cellinkwidgets/tabbuttons.cpp \
    cellinkwidgets/toggleswitch.cpp \
    cellinkwidgets/tooltabbuttons.cpp \
    cellinkwidgets/utils.cpp \
    cellinkwidgets/videowidget.cpp \
    cellinkwidgetsplugin.cpp \
    collapseboxplugin.cpp \
    doublespinboxplugin.cpp \
    growablestackedwidgetplugin.cpp \
    iconbuttonplugin.cpp \
    menubuttonplugin.cpp \
    numberoffsetwidgetplugin.cpp \
    paintedvideowidgetplugin.cpp \
    progressbarplugin.cpp \
    qt3dwidgetplugin.cpp \
    sliderspinboxwidgetplugin.cpp \
    spinboxplugin.cpp \
    toggleswitchplugin.cpp \
    videowidgetplugin.cpp

RESOURCES   = \
    icons.qrc

DISTFILES += \
    README.md

FORMS += \
    cellinkwidgets/iconbutton.ui \
    cellinkwidgets/menutabbuttons.ui \
    cellinkwidgets/videowidget.ui \
    cellinkwidgets/popupbutton.ui \
    cellinkwidgets/tabbuttons.ui \
    cellinkwidgets/tooltabbutton.ui \
    cellinkwidgets/tooltabbuttons.ui \
    cellinkwidgets/numberoffsetwidget.ui \
    cellinkwidgets/rondedpopup.ui \
    cellinkwidgets/sliderspinboxwidget.ui
