/****************************************************************************
**
** Copyright (C) 2019 J-P Nurmi <jpnurmi@gmail.com>
** Copyright (C) 2017 The Qt Company Ltd.
**
** This file is part of QtCellink (based on the Qt Labs Platform module of Qt).
**
** QtCellink is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.

** QtCellink is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.

** You should have received a copy of the GNU General Public License
** along with QtCellink. If not, see <https://www.gnu.org/licenses/>.
**
****************************************************************************/

#ifndef QQUICKPLATFORMICON_P_H
#define QQUICKPLATFORMICON_P_H

#include <QtCore/qurl.h>
#include <QtCore/qstring.h>

QT_BEGIN_NAMESPACE

class QObject;

class QQuickPlatformIcon
{
    Q_GADGET
    Q_PROPERTY(QUrl source READ source WRITE setSource)
    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(bool mask READ isMask WRITE setMask)

public:
    QUrl source() const;
    void setSource(const QUrl &source);

    QString name() const;
    void setName(const QString &name);

    bool isMask() const;
    void setMask(bool mask);

    bool operator==(const QQuickPlatformIcon &other) const;
    bool operator!=(const QQuickPlatformIcon &other) const;

private:
    bool m_mask = false;
    QUrl m_source;
    QString m_name;
};

QT_END_NAMESPACE

#endif // QQUICKPLATFORMICON_P_H
