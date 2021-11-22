/****************************************************************************
**
** Copyright (C) 2020 CELLINK AB <info@cellink.com>
** Copyright (C) 2017 The Qt Company Ltd.
**
** This file is part of QtCellink (based on the Qt Quick Templates 2 module of Qt).
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

#ifndef ROWBUTTON_H
#define ROWBUTTON_H

#include <QtQuickTemplates2/private/qquickabstractbutton_p.h>

class RowButtonPrivate;

class RowButton : public QQuickAbstractButton
{
    Q_OBJECT
    Q_PROPERTY(bool highlighted READ isHighlighted WRITE setHighlighted NOTIFY highlightedChanged FINAL)

public:
    explicit RowButton(QQuickItem* parent = nullptr);

    bool isHighlighted() const;
    void setHighlighted(bool highlighted);

Q_SIGNALS:
    void highlightedChanged();

protected:
    QFont defaultFont() const override;
    QPalette defaultPalette() const override;

#if QT_CONFIG(accessibility)
    QAccessible::Role accessibleRole() const override;
#endif

private:
    Q_DISABLE_COPY(RowButton)
    Q_DECLARE_PRIVATE(RowButton)
};

QML_DECLARE_TYPE(RowButton)

#endif // ROWBUTTON_H
