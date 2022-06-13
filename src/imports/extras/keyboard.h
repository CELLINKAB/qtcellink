/****************************************************************************
**
** Copyright (C) 2020 CELLINK AB <info@cellink.com>
**
** This file is part of QtCellink.
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

#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <QtCore/qobject.h>
#include <QtGui/qguiapplication.h>

class Keyboard : public QObject
{
    Q_OBJECT

public:
    explicit Keyboard(QObject* parent = nullptr);

    Q_INVOKABLE static Qt::KeyboardModifiers modifiers()
    {
        return QGuiApplication::keyboardModifiers();
    }
};

#endif // KEYBOARD_H
