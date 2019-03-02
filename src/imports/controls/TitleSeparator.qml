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
import QtCellink.Templates 1.0 as C

C.TitleSeparator {
    id: control

    implicitWidth: Math.max(background ? background.implicitWidth : 0, contentItem.implicitWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(background ? background.implicitHeight : 0, (!!title ? contentItem.implicitHeight : 0) + topPadding + bottomPadding)

    spacing: 6
    leftPadding: mirrored ? 20 : 0
    rightPadding: mirrored ? 20 : 0

    contentItem: Text {
        text: control.title
    }

    background: Item {
        implicitHeight: 2
        y: (control.height - height) / 2
        height: 2

        Rectangle {
            width: control.leftPadding - (contentItem.contentWidth > 0 ? control.spacing : 0)
            height: parent.height
            color: Qt.darker(control.palette.window, 1.1)

            Rectangle {
                y: 1
                width: parent.width
                height: 1
                color: Qt.lighter(control.palette.window, 1.1)
            }
        }

        Rectangle {
            x: contentItem.x + contentItem.contentWidth + (contentItem.contentWidth > 0 ? control.spacing : 0)
            width: control.width - x
            height: parent.height
            color: Qt.darker(control.palette.window, 1.1)

            Rectangle {
                y: 1
                width: parent.width
                height: 1
                color: Qt.lighter(control.palette.window, 1.1)
            }
        }
    }
}
