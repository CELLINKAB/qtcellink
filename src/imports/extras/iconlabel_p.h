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

#ifndef ICONLABEL_P_H
#define ICONLABEL_P_H

#include <QtQuick/private/qquickitem_p.h>

#include "iconlabel.h"

class IconImage;
class MnemonicLabel;

class IconLabelPrivate : public QQuickItemPrivate, public QQuickItemChangeListener
{
    Q_DECLARE_PUBLIC(IconLabel)

public:
    bool hasIcon() const;
    bool hasText() const;

    bool createImage();
    bool destroyImage();
    bool updateImage();
    void syncImage();
    void updateOrSyncImage();

    bool createLabel();
    bool destroyLabel();
    bool updateLabel();
    void syncLabel();
    void updateOrSyncLabel();

    void updateImplicitSize();
    void layout();

    void watchChanges(QQuickItem* item);
    void unwatchChanges(QQuickItem* item);
    void setPositioningDirty();

    bool isLeftToRight() const;

    void itemImplicitWidthChanged(QQuickItem*) override;
    void itemImplicitHeightChanged(QQuickItem*) override;
    void itemDestroyed(QQuickItem* item) override;

    bool mirrored = false;
    IconLabel::Display display = IconLabel::TextBesideIcon;
    Qt::Alignment alignment = Qt::AlignCenter;
    qreal spacing = 0;
    qreal topPadding = 0;
    qreal leftPadding = 0;
    qreal rightPadding = 0;
    qreal bottomPadding = 0;
    QFont font;
    QColor color;
    QString text;
    QQuickIcon icon;
    IconImage* image = nullptr;
    MnemonicLabel* label = nullptr;
};

#endif // ICONLABEL_P_H
