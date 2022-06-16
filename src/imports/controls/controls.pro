TARGET = qtcellinkcontrolsplugin
TARGETPATH = QtCellink/Controls
IMPORT_VERSION = 1.0

QT += qml quick quickcontrols2
QT_PRIVATE += core-private gui-private qml-private quick-private quicktemplates2-private quickcontrols2-private

DEFINES += QT_NO_CAST_TO_ASCII QT_NO_CAST_FROM_ASCII

win32 {
    system(powershell -Command cp $$PWD/qmldir.win $$PWD/qmldir)
} else {
    system(cp $$PWD/qmldir.linux $$PWD/qmldir)
}

AUX_QML_FILES += \
    $$PWD/ButtonRow.qml \
    $$PWD/ComponentView.qml \
    $$PWD/DoubleSpinBox.qml \
    $$PWD/FlipView.qml \
    $$PWD/ProgressIndicator.qml \
    $$PWD/RowButton.qml \
    $$PWD/SplitView.qml \
    $$PWD/TitleSeparator.qml \
    $$PWD/arrow.png \
    $$PWD/arrow@2x.png

OTHER_FILES += \
    $$PWD/qmldir \
    $$AUX_QML_FILES

HEADERS += \
    $$PWD/progressindicator.h

SOURCES += \
    $$PWD/progressindicator.cpp \
    $$PWD/qtcellinkcontrolsplugin.cpp

# CONFIG += no_cxx_module
load(qml_plugin)

DISTFILES += \
    qmldir.linux \
    qmldir.win
