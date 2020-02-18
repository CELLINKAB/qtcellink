import QtQuick 2.12
import QtCellink.Templates 1.0 as T

T.FlipView {
    id: control

    implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset,
                            contentWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset,
                             contentHeight + topPadding + bottomPadding)

    contentItem: Flipable {
        transform: Rotation {
            axis {
                x: control.axis === Qt.XAxis
                y: control.axis === Qt.YAxis
                z: control.axis === Qt.ZAxis
            }
            origin {
                x: control.availableWidth / 2
                y: control.availableHeight / 2
            }
            angle: control.angle
            Behavior on angle { NumberAnimation { duration: 175; easing.type: Easing.InOutCubic } }
        }
    }
}
