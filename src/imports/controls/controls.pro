TARGET = cellinkcontrolsplugin
TARGETPATH = Cellink/Controls
IMPORT_VERSION = 1.0

QT += qml quick
QT_PRIVATE += core-private gui-private qml-private quick-private quicktemplates2-private

DEFINES += QT_NO_CAST_TO_ASCII QT_NO_CAST_FROM_ASCII

AUX_QML_FILES += \
    $$PWD/DoubleSpinBox.qml \
    $$PWD/TitleSeparator.qml \
    $$PWD/arrow.png \
    $$PWD/arrow@2x.png

OTHER_FILES += \
    $$PWD/qmldir \
    $$AUX_QML_FILES

SOURCES += \
    $$PWD/cellinkcontrolsplugin.cpp

CONFIG += no_cxx_module
load(qml_plugin)
