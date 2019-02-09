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

#include "iconlabel.h"
#include "iconlabel_p.h"
#include "iconimage.h"
#include "mnemoniclabel.h"

#include <QtGui/private/qguiapplication_p.h>
#include <QtQuick/private/qquickitem_p.h>
#include <QtQuick/private/qquicktext_p.h>

static void beginClass(QQuickItem *item)
{
    if (QQmlParserStatus *parserStatus = qobject_cast<QQmlParserStatus *>(item))
        parserStatus->classBegin();
}

static void completeComponent(QQuickItem *item)
{
    if (QQmlParserStatus *parserStatus = qobject_cast<QQmlParserStatus *>(item))
        parserStatus->componentComplete();
}

bool IconLabelPrivate::hasIcon() const
{
    return display != IconLabel::TextOnly && !icon.isEmpty();
}

bool IconLabelPrivate::hasText() const
{
    return display != IconLabel::IconOnly && !text.isEmpty();
}

bool IconLabelPrivate::createImage()
{
    Q_Q(IconLabel);
    if (image)
        return false;

    image = new IconImage(q);
    watchChanges(image);
    beginClass(image);
    image->setObjectName(QStringLiteral("image"));
    image->setName(icon.name());
    image->setSource(icon.source());
    image->setSourceSize(QSize(icon.width(), icon.height()));
    image->setColor(icon.color());
    QQmlEngine::setContextForObject(image, qmlContext(q));
    if (componentComplete)
        completeComponent(image);
    return true;
}

bool IconLabelPrivate::destroyImage()
{
    if (!image)
        return false;

    unwatchChanges(image);
    delete image;
    image = nullptr;
    return true;
}

bool IconLabelPrivate::updateImage()
{
    if (!hasIcon())
        return destroyImage();
    return createImage();
}

void IconLabelPrivate::syncImage()
{
    if (!image || icon.isEmpty())
        return;

    image->setName(icon.name());
    image->setSource(icon.source());
    image->setSourceSize(QSize(icon.width(), icon.height()));
    image->setColor(icon.color());
    const int valign = alignment & Qt::AlignVertical_Mask;
    image->setVerticalAlignment(static_cast<QQuickImage::VAlignment>(valign));
    const int halign = alignment & Qt::AlignHorizontal_Mask;
    image->setHorizontalAlignment(static_cast<QQuickImage::HAlignment>(halign));
}

void IconLabelPrivate::updateOrSyncImage()
{
    if (updateImage()) {
        if (componentComplete) {
            updateImplicitSize();
            layout();
        }
    } else {
        syncImage();
    }
}

bool IconLabelPrivate::createLabel()
{
    Q_Q(IconLabel);
    if (label)
        return false;

    label = new MnemonicLabel(q);
    watchChanges(label);
    beginClass(label);
    label->setObjectName(QStringLiteral("label"));
    label->setFont(font);
    label->setColor(color);
    label->setElideMode(QQuickText::ElideRight);
    const int valign = alignment & Qt::AlignVertical_Mask;
    label->setVAlign(static_cast<QQuickText::VAlignment>(valign));
    const int halign = alignment & Qt::AlignHorizontal_Mask;
    label->setHAlign(static_cast<QQuickText::HAlignment>(halign));
    label->setText(text);
    if (componentComplete)
        completeComponent(label);
    return true;
}

bool IconLabelPrivate::destroyLabel()
{
    if (!label)
        return false;

    unwatchChanges(label);
    delete label;
    label = nullptr;
    return true;
}

bool IconLabelPrivate::updateLabel()
{
    if (!hasText())
        return destroyLabel();
    return createLabel();
}

void IconLabelPrivate::syncLabel()
{
    if (!label)
        return;

    label->setText(text);
}

void IconLabelPrivate::updateOrSyncLabel()
{
    if (updateLabel()) {
        if (componentComplete) {
            updateImplicitSize();
            layout();
        }
    } else {
        syncLabel();
    }
}

void IconLabelPrivate::updateImplicitSize()
{
    Q_Q(IconLabel);
    const bool showIcon = image && hasIcon();
    const bool showText = label && hasText();
    const qreal horizontalPadding = leftPadding + rightPadding;
    const qreal verticalPadding = topPadding + bottomPadding;
    const qreal iconImplicitWidth = showIcon ? image->implicitWidth() : 0;
    const qreal iconImplicitHeight = showIcon ? image->implicitHeight() : 0;
    const qreal textImplicitWidth = showText ? label->implicitWidth() : 0;
    const qreal textImplicitHeight = showText ? label->implicitHeight() : 0;
    const qreal effectiveSpacing = showText && showIcon && image->implicitWidth() > 0 ? spacing : 0;
    const qreal implicitWidth = display == IconLabel::TextBesideIcon ? iconImplicitWidth + textImplicitWidth + effectiveSpacing
                                                                           : qMax(iconImplicitWidth, textImplicitWidth);
    const qreal implicitHeight = display == IconLabel::TextUnderIcon ? iconImplicitHeight + textImplicitHeight + effectiveSpacing
                                                                           : qMax(iconImplicitHeight, textImplicitHeight);
    q->setImplicitSize(implicitWidth + horizontalPadding, implicitHeight + verticalPadding);
}

// adapted from QStyle::alignedRect()
static QRectF alignedRect(bool mirrored, Qt::Alignment alignment, const QSizeF &size, const QRectF &rectangle)
{
    alignment = QGuiApplicationPrivate::visualAlignment(mirrored ? Qt::RightToLeft : Qt::LeftToRight, alignment);
    qreal x = rectangle.x();
    qreal y = rectangle.y();
    const qreal w = size.width();
    const qreal h = size.height();
    if ((alignment & Qt::AlignVCenter) == Qt::AlignVCenter)
        y += rectangle.height() / 2 - h / 2;
    else if ((alignment & Qt::AlignBottom) == Qt::AlignBottom)
        y += rectangle.height() - h;
    if ((alignment & Qt::AlignRight) == Qt::AlignRight)
        x += rectangle.width() - w;
    else if ((alignment & Qt::AlignHCenter) == Qt::AlignHCenter)
        x += rectangle.width() / 2 - w / 2;
    return QRectF(x, y, w, h);
}

void IconLabelPrivate::layout()
{
    Q_Q(IconLabel);
    if (!componentComplete)
        return;

    const qreal availableWidth = width - leftPadding - rightPadding;
    const qreal availableHeight = height - topPadding - bottomPadding;

    switch (display) {
    case IconLabel::IconOnly:
        if (image) {
            const QRectF iconRect = alignedRect(mirrored, alignment,
                                                QSizeF(qMin(image->implicitWidth(), availableWidth),
                                                       qMin(image->implicitHeight(), availableHeight)),
                                                QRectF(leftPadding, topPadding, availableWidth, availableHeight));
            image->setSize(iconRect.size());
            image->setPosition(iconRect.topLeft());
        }
        break;
    case IconLabel::TextOnly:
        if (label) {
            const QRectF textRect = alignedRect(mirrored, alignment,
                                                QSizeF(qMin(label->implicitWidth(), availableWidth),
                                                       qMin(label->implicitHeight(), availableHeight)),
                                                QRectF(leftPadding, topPadding, availableWidth, availableHeight));
            label->setSize(textRect.size());
            label->setPosition(textRect.topLeft());
        }
        break;

    case IconLabel::TextUnderIcon: {
        // Work out the sizes first, as the positions depend on them.
        QSizeF iconSize;
        QSizeF textSize;
        if (image) {
            iconSize.setWidth(qMin(image->implicitWidth(), availableWidth));
            iconSize.setHeight(qMin(image->implicitHeight(), availableHeight));
        }
        qreal effectiveSpacing = 0;
        if (label) {
            if (!iconSize.isEmpty())
                effectiveSpacing = spacing;
            textSize.setWidth(qMin(label->implicitWidth(), availableWidth));
            textSize.setHeight(qMin(label->implicitHeight(), availableHeight - iconSize.height() - effectiveSpacing));
        }

        QRectF combinedRect = alignedRect(mirrored, alignment,
                                          QSizeF(qMax(iconSize.width(), textSize.width()),
                                                 iconSize.height() + effectiveSpacing + textSize.height()),
                                          QRectF(leftPadding, topPadding, availableWidth, availableHeight));
        if (image) {
            QRectF iconRect = alignedRect(mirrored, Qt::AlignHCenter | Qt::AlignTop, iconSize, combinedRect);
            image->setSize(iconRect.size());
            image->setPosition(iconRect.topLeft());
        }
        if (label) {
            QRectF textRect = alignedRect(mirrored, Qt::AlignHCenter | Qt::AlignBottom, textSize, combinedRect);
            label->setSize(textRect.size());
            label->setPosition(textRect.topLeft());
        }
        break;
    }

    case IconLabel::TextBesideIcon:
    default:
        // Work out the sizes first, as the positions depend on them.
        QSizeF iconSize(0, 0);
        QSizeF textSize(0, 0);
        if (image) {
            iconSize.setWidth(qMin(image->implicitWidth(), availableWidth));
            iconSize.setHeight(qMin(image->implicitHeight(), availableHeight));
        }
        qreal effectiveSpacing = 0;
        if (label) {
            if (!iconSize.isEmpty())
                effectiveSpacing = spacing;
            textSize.setWidth(qMin(label->implicitWidth(), availableWidth - iconSize.width() - effectiveSpacing));
            textSize.setHeight(qMin(label->implicitHeight(), availableHeight));
        }

        const QRectF combinedRect = alignedRect(mirrored, alignment,
                                                QSizeF(iconSize.width() + effectiveSpacing + textSize.width(),
                                                       qMax(iconSize.height(), textSize.height())),
                                                QRectF(leftPadding, topPadding, availableWidth, availableHeight));
        if (image) {
            const QRectF iconRect = alignedRect(mirrored, Qt::AlignLeft | Qt::AlignVCenter, iconSize, combinedRect);
            image->setSize(iconRect.size());
            image->setPosition(iconRect.topLeft());
        }
        if (label) {
            const QRectF textRect = alignedRect(mirrored, Qt::AlignRight | Qt::AlignVCenter, textSize, combinedRect);
            label->setSize(textRect.size());
            label->setPosition(textRect.topLeft());
        }
        break;
    }

    q->setBaselineOffset(label ? label->y() + label->baselineOffset() : 0);
}

static const QQuickItemPrivate::ChangeTypes itemChangeTypes =
    QQuickItemPrivate::ImplicitWidth
    | QQuickItemPrivate::ImplicitHeight
    | QQuickItemPrivate::Destroyed;

void IconLabelPrivate::watchChanges(QQuickItem *item)
{
    QQuickItemPrivate *itemPrivate = QQuickItemPrivate::get(item);
    itemPrivate->addItemChangeListener(this, itemChangeTypes);
}

void IconLabelPrivate::unwatchChanges(QQuickItem* item)
{
    QQuickItemPrivate *itemPrivate = QQuickItemPrivate::get(item);
    itemPrivate->removeItemChangeListener(this, itemChangeTypes);
}

void IconLabelPrivate::itemImplicitWidthChanged(QQuickItem *)
{
    updateImplicitSize();
    layout();
}

void IconLabelPrivate::itemImplicitHeightChanged(QQuickItem *)
{
    updateImplicitSize();
    layout();
}

void IconLabelPrivate::itemDestroyed(QQuickItem *item)
{
    unwatchChanges(item);
    if (item == image)
        image = nullptr;
    else if (item == label)
        label = nullptr;
}

IconLabel::IconLabel(QQuickItem *parent)
    : QQuickItem(*(new IconLabelPrivate), parent)
{
}

IconLabel::~IconLabel()
{
    Q_D(IconLabel);
    if (d->image)
        d->unwatchChanges(d->image);
    if (d->label)
        d->unwatchChanges(d->label);
}

QQuickIcon IconLabel::icon() const
{
    Q_D(const IconLabel);
    return d->icon;
}

void IconLabel::setIcon(const QQuickIcon &icon)
{
    Q_D(IconLabel);
    if (d->icon == icon)
        return;

    d->icon = icon;
    d->updateOrSyncImage();
}

QString IconLabel::text() const
{
    Q_D(const IconLabel);
    return d->text;
}

void IconLabel::setText(const QString text)
{
    Q_D(IconLabel);
    if (d->text == text)
        return;

    d->text = text;
    d->updateOrSyncLabel();
}

QFont IconLabel::font() const
{
    Q_D(const IconLabel);
    return d->font;
}

void IconLabel::setFont(const QFont &font)
{
    Q_D(IconLabel);
    if (d->font == font)
        return;

    d->font = font;
    if (d->label)
        d->label->setFont(font);
}

QColor IconLabel::color() const
{
    Q_D(const IconLabel);
    return d->color;
}

void IconLabel::setColor(const QColor &color)
{
    Q_D(IconLabel);
    if (d->color == color)
        return;

    d->color = color;
    if (d->label)
        d->label->setColor(color);
}

IconLabel::Display IconLabel::display() const
{
    Q_D(const IconLabel);
    return d->display;
}

void IconLabel::setDisplay(Display display)
{
    Q_D(IconLabel);
    if (d->display == display)
        return;

    d->display = display;
    d->updateImage();
    d->updateLabel();
    d->updateImplicitSize();
    d->layout();
}

qreal IconLabel::spacing() const
{
    Q_D(const IconLabel);
    return d->spacing;
}

void IconLabel::setSpacing(qreal spacing)
{
    Q_D(IconLabel);
    if (qFuzzyCompare(d->spacing, spacing))
        return;

    d->spacing = spacing;
    if (d->image && d->label) {
        d->updateImplicitSize();
        d->layout();
    }
}

bool IconLabel::isMirrored() const
{
    Q_D(const IconLabel);
    return d->mirrored;
}

void IconLabel::setMirrored(bool mirrored)
{
    Q_D(IconLabel);
    if (d->mirrored == mirrored)
        return;

    d->mirrored = mirrored;
    d->layout();
}

Qt::Alignment IconLabel::alignment() const
{
    Q_D(const IconLabel);
    return d->alignment;
}

void IconLabel::setAlignment(Qt::Alignment alignment)
{
    Q_D(IconLabel);
    const int valign = alignment & Qt::AlignVertical_Mask;
    const int halign = alignment & Qt::AlignHorizontal_Mask;
    const uint align = (valign ? valign : Qt::AlignVCenter) | (halign ? halign : Qt::AlignHCenter);
    if (d->alignment == align)
        return;

    d->alignment = static_cast<Qt::Alignment>(align);
    if (d->label) {
        d->label->setVAlign(static_cast<QQuickText::VAlignment>(valign));
        d->label->setHAlign(static_cast<QQuickText::HAlignment>(halign));
    }
    if (d->image) {
        d->image->setVerticalAlignment(static_cast<QQuickImage::VAlignment>(valign));
        d->image->setHorizontalAlignment(static_cast<QQuickImage::HAlignment>(halign));
    }
    d->layout();
}

qreal IconLabel::topPadding() const
{
    Q_D(const IconLabel);
    return d->topPadding;
}

void IconLabel::setTopPadding(qreal padding)
{
    Q_D(IconLabel);
    if (qFuzzyCompare(d->topPadding, padding))
        return;

    d->topPadding = padding;
    d->updateImplicitSize();
    d->layout();
}

void IconLabel::resetTopPadding()
{
    setTopPadding(0);
}

qreal IconLabel::leftPadding() const
{
    Q_D(const IconLabel);
    return d->leftPadding;
}

void IconLabel::setLeftPadding(qreal padding)
{
    Q_D(IconLabel);
    if (qFuzzyCompare(d->leftPadding, padding))
        return;

    d->leftPadding = padding;
    d->updateImplicitSize();
    d->layout();
}

void IconLabel::resetLeftPadding()
{
    setLeftPadding(0);
}

qreal IconLabel::rightPadding() const
{
    Q_D(const IconLabel);
    return d->rightPadding;
}

void IconLabel::setRightPadding(qreal padding)
{
    Q_D(IconLabel);
    if (qFuzzyCompare(d->rightPadding, padding))
        return;

    d->rightPadding = padding;
    d->updateImplicitSize();
    d->layout();
}

void IconLabel::resetRightPadding()
{
    setRightPadding(0);
}

qreal IconLabel::bottomPadding() const
{
    Q_D(const IconLabel);
    return d->bottomPadding;
}

void IconLabel::setBottomPadding(qreal padding)
{
    Q_D(IconLabel);
    if (qFuzzyCompare(d->bottomPadding, padding))
        return;

    d->bottomPadding = padding;
    d->updateImplicitSize();
    d->layout();
}

void IconLabel::resetBottomPadding()
{
    setBottomPadding(0);
}

void IconLabel::componentComplete()
{
    Q_D(IconLabel);
    if (d->image)
        completeComponent(d->image);
    if (d->label)
        completeComponent(d->label);
    QQuickItem::componentComplete();
    d->layout();
}

void IconLabel::geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry)
{
    Q_D(IconLabel);
    QQuickItem::geometryChanged(newGeometry, oldGeometry);
    d->layout();
}
