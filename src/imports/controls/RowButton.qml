/****************************************************************************
**
** Copyright (C) 2020 CELLINK AB <info@cellink.com>
** Copyright (C) 2017 The Qt Company Ltd.
**
** This file is part of QtCellink (based on the Qt Quick Controls 2 module of Qt).
**
** QtCellink is free software: you can redistribute it and/or modify it
** under the terms of the GNU Lesser General Public License as published
** by the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** QtCellink is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
** GNU Lesser General Public License for more details.
**
** You should have received a copy of the GNU Lesser General Public License
** along with QtCellink. If not, see <https://www.gnu.org/licenses/>.
**
****************************************************************************/

import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.impl 2.12
import QtQuick.Controls.Fusion 2.12
import QtQuick.Controls.Fusion.impl 2.12
import QtCellink.Templates 1.0 as T

T.RowButton {
    id: control

    implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset,
                            implicitContentWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset,
                             implicitContentHeight + topPadding + bottomPadding)

    z: checked
    padding: 4
    spacing: 6

    icon.width: 16
    icon.height: 16

    contentItem: IconLabel {
        spacing: control.spacing
        mirrored: control.mirrored
        display: control.display

        icon: control.icon
        text: control.text
        font.family: control.font.family
        font.pixelSize: control.font.pixelSize * 0.8
        color: control.palette.buttonText
    }

    background: PaddedRectangle {
        implicitHeight: 24

        visible: !control.flat || control.down || control.checked || control.highlighted || control.visualFocus || control.hovered
        color: Fusion.buttonColor(control.palette, control.highlighted, control.down || control.checked, control.hovered)
        gradient: control.down || control.checked ? null : buttonGradient

        Gradient {
            id: buttonGradient
            GradientStop {
                position: 0
                color: Fusion.gradientStart(Fusion.buttonColor(control.palette, control.highlighted, control.down, control.hovered))
            }
            GradientStop {
                position: 1
                color: Fusion.gradientStop(Fusion.buttonColor(control.palette, control.highlighted, control.down, control.hovered))
            }
        }

        radius: 2
        border.color: Fusion.buttonOutline(control.palette, control.highlighted || control.visualFocus, control.enabled)

        clip: true
        leftPadding: !control.T.ButtonRow.isFirstItem ? -2 : 0
        rightPadding: !control.T.ButtonRow.isLastItem ? -2 : 0

        Rectangle {
            x: 0
            width: 1
            height: parent.height
            visible: !control.T.ButtonRow.isFirstItem
            color: Fusion.buttonOutline(control.palette, control.highlighted || control.visualFocus, control.enabled)
        }

        Rectangle {
            x: parent.width - 1
            width: 1
            height: parent.height
            visible: !control.T.ButtonRow.isLastItem
            color: Fusion.buttonOutline(control.palette, control.highlighted || control.visualFocus, control.enabled)
        }

        Rectangle {
            x: 1; y: 1
            width: parent.width - 2
            height: parent.height - 2
            border.color: Fusion.innerContrastLine
            color: "transparent"
            radius: 2
        }
    }
}
