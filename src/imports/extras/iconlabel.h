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

#ifndef ICONLABEL_H
#define ICONLABEL_H

#include <QtQuick/qquickitem.h>
#include <QtQuickTemplates2/private/qquickicon_p.h>

class IconLabelPrivate;

class IconLabel : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QQuickIcon icon READ icon WRITE setIcon FINAL)
    Q_PROPERTY(QString text READ text WRITE setText FINAL)
    Q_PROPERTY(QFont font READ font WRITE setFont FINAL)
    Q_PROPERTY(QColor color READ color WRITE setColor FINAL)
    Q_PROPERTY(Display display READ display WRITE setDisplay FINAL)
    Q_PROPERTY(qreal spacing READ spacing WRITE setSpacing FINAL)
    Q_PROPERTY(bool mirrored READ isMirrored WRITE setMirrored FINAL)
    Q_PROPERTY(Qt::Alignment alignment READ alignment WRITE setAlignment FINAL)
    Q_PROPERTY(qreal topPadding READ topPadding WRITE setTopPadding RESET resetTopPadding FINAL)
    Q_PROPERTY(qreal leftPadding READ leftPadding WRITE setLeftPadding RESET resetLeftPadding FINAL)
    Q_PROPERTY(
        qreal rightPadding READ rightPadding WRITE setRightPadding RESET resetRightPadding FINAL)
    Q_PROPERTY(qreal bottomPadding READ bottomPadding WRITE setBottomPadding RESET
                   resetBottomPadding FINAL)

public:
    enum Display
    {
        IconOnly,
        TextOnly,
        TextBesideIcon,
        TextUnderIcon
    };
    Q_ENUM(Display)

    explicit IconLabel(QQuickItem* parent = nullptr);
    ~IconLabel();

    QQuickIcon icon() const;
    void setIcon(const QQuickIcon& icon);

    QString text() const;
    void setText(const QString text);

    QFont font() const;
    void setFont(const QFont& font);

    QColor color() const;
    void setColor(const QColor& color);

    Display display() const;
    void setDisplay(Display display);

    qreal spacing() const;
    void setSpacing(qreal spacing);

    bool isMirrored() const;
    void setMirrored(bool mirrored);

    Qt::Alignment alignment() const;
    void setAlignment(Qt::Alignment alignment);

    qreal topPadding() const;
    void setTopPadding(qreal padding);
    void resetTopPadding();

    qreal leftPadding() const;
    void setLeftPadding(qreal padding);
    void resetLeftPadding();

    qreal rightPadding() const;
    void setRightPadding(qreal padding);
    void resetRightPadding();

    qreal bottomPadding() const;
    void setBottomPadding(qreal padding);
    void resetBottomPadding();

protected:
    void componentComplete() override;
    void geometryChanged(const QRectF& newGeometry, const QRectF& oldGeometry) override;

private:
    Q_DISABLE_COPY(IconLabel)
    Q_DECLARE_PRIVATE(IconLabel)
};

QML_DECLARE_TYPE(IconLabel)

#endif // ICONLABEL_H
