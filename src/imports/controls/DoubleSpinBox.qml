/****************************************************************************
**
** Copyright (C) 2019 CELLINK AB <info@cellink.com>
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

import QtQuick 2.11
import QtQuick.Templates 2.4 as T
import QtQuick.Controls 2.4
import QtQuick.Controls.impl 2.4
import QtQuick.Controls.Fusion 2.4
import QtQuick.Controls.Fusion.impl 2.4
import Cellink.Templates 1.0 as C

C.DoubleSpinBox {
    id: control

    implicitWidth: Math.max(background ? background.implicitWidth : 0,
                            contentItem.implicitWidth + 2 * padding +
                            Math.max(up.indicator ? up.indicator.implicitWidth : 0,
                                    down.indicator ? down.indicator.implicitWidth : 0))
    implicitHeight: Math.max(contentItem.implicitHeight + topPadding + bottomPadding,
                             background ? background.implicitHeight : 0,
                             (up.indicator ? up.indicator.implicitHeight : 0 +
                              down.indicator ? down.indicator.implicitHeight : 0))
    baselineOffset: contentItem.y + contentItem.baselineOffset

    spacing: 2
    padding: 4
    leftPadding: padding + (control.mirrored ? Math.max(up.indicator ? up.indicator.width : 0, down.indicator ? down.indicator.width : 0) : 0)
    rightPadding: padding + (control.mirrored ? 0 : Math.max(up.indicator ? up.indicator.width : 0, down.indicator ? down.indicator.width : 0))

    validator: DoubleValidator {
        decimals: control.decimals
        locale: control.locale.name
        notation: DoubleValidator.StandardNotation
        bottom: Math.min(control.from, control.to)
        top: Math.max(control.from, control.to)
    }

    contentItem: TextInput {
        z: 2
        text: control.displayText

        font: control.font
        color: control.palette.text
        selectionColor: control.palette.highlight
        selectedTextColor: control.palette.highlightedText
        horizontalAlignment: Qt.AlignHCenter
        verticalAlignment: Qt.AlignVCenter

        readOnly: !control.editable
        validator: control.validator
        inputMethodHints: control.inputMethodHints
        selectByMouse: true

        Text {
            text: control.prefix
            x: control.leftPadding
            anchors.baseline: parent.baseline
            font.family: control.font.family
            font.pixelSize: control.font.pixelSize - 2
            color: control.palette.text
        }

        Text {
            text: control.suffix
            x: (parent.width + parent.contentWidth) / 2 + control.spacing
            anchors.baseline: parent.baseline
            font.family: control.font.family
            font.pixelSize: control.font.pixelSize - 2
            color: control.palette.text
        }
    }

    up.indicator: PaddedRectangle {
        x: control.mirrored ? 1 : parent.width - width - 1
        y: 1
        height: parent.height / 2 - 1
        implicitWidth: 16
        implicitHeight: 10

        radius: 1.7
        clip: true
        topPadding: -2
        leftPadding: -2
        color: control.up.pressed ? Fusion.buttonColor(control.palette, false, true, true) : "transparent"

        ColorImage {
            scale: -1
            width: parent.width
            height: parent.height
            opacity: enabled ? 1.0 : 0.5
            color: control.palette.buttonText
            source: "arrow.png"
            fillMode: Image.Pad
        }
    }

    down.indicator: PaddedRectangle {
        x: control.mirrored ? 1 : parent.width - width - 1
        y: parent.height - height - 1
        height: parent.height / 2 - 1
        implicitWidth: 16
        implicitHeight: 10

        radius: 1.7
        clip: true
        topPadding: -2
        leftPadding: -2
        color: control.down.pressed ? Fusion.buttonColor(control.palette, false, true, true) : "transparent"

        ColorImage {
            width: parent.width
            height: parent.height
            opacity: enabled ? 1.0 : 0.5
            color: control.palette.buttonText
            source: "arrow.png"
            fillMode: Image.Pad
        }
    }

    background: Rectangle {
        implicitWidth: 120
        implicitHeight: 24

        radius: 2
        color: control.palette.base
        border.color: control.activeFocus ? Fusion.highlightedOutline(control.palette) : Fusion.outline(control.palette)

        Rectangle {
            x: 2
            y: 1
            width: parent.width - 4
            height: 1
            color: Fusion.topShadow
        }

        Rectangle {
            x: control.mirrored ? 1 : parent.width - width - 1
            y: 1
            width: Math.max(up.indicator ? up.indicator.width : 0,
                            down.indicator ? down.indicator.width : 0) + 1
            height: parent.height - 2

            radius: 2
            gradient: Gradient {
                GradientStop {
                    position: 0
                    color: Fusion.gradientStart(Fusion.buttonColor(control.palette, control.visualFocus, false, control.up.hovered || control.down.hovered))
                }
                GradientStop {
                    position: 1
                    color: Fusion.gradientStop(Fusion.buttonColor(control.palette, control.visualFocus, false, control.up.hovered || control.down.hovered))
                }
            }

            Rectangle {
                x: control.mirrored ? parent.width - 1 : 0
                height: parent.height
                width: 1
                color: Fusion.outline(control.palette)
            }
        }

        Rectangle {
            x: 1; y: 1
            width: parent.width - 2
            height: parent.height - 2
            color: "transparent"
            border.color: Color.transparent(Fusion.highlightedOutline(control.palette), 40 / 255)
            visible: control.activeFocus
            radius: 1.7
        }
    }
}
