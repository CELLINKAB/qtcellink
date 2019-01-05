import QtQuick 2.11
import QtQuick.Controls 2.4 as QQC2

QQC2.MenuBar {
    id: menuBar
    Component.onCompleted: QQC2.ApplicationWindow.window.menuBar = menuBar
}
