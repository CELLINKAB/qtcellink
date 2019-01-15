/****************************************************************************
**
** Copyright (C) 2019 CELLINK AB <info@cellink.com>
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

#ifndef TITLESEPARATOR_H
#define TITLESEPARATOR_H

#include <QtQuickTemplates2/private/qquickcontrol_p.h>

class TitleSeparatorPrivate;

class TitleSeparator : public QQuickControl
{
    Q_OBJECT
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged FINAL)

public:
    explicit TitleSeparator(QQuickItem *parent = nullptr);

    QString title() const;
    void setTitle(QString &title);

Q_SIGNALS:
    void titleChanged();

protected:
#if QT_CONFIG(accessibility)
    QAccessible::Role accessibleRole() const override;
#endif

private:
    Q_DISABLE_COPY(TitleSeparator)
    Q_DECLARE_PRIVATE(TitleSeparator)
};

QML_DECLARE_TYPE(TitleSeparator)

#endif // QQUICKTITLESEPARATOR_P_H
