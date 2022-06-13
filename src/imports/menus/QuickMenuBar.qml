import QtQuick 2.12
import QtQuick.Controls 2.12 as QQC2

QQC2.MenuBar {
    id: menuBar
    Component.onCompleted: QQC2.ApplicationWindow.window.menuBar = menuBar
}
