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

#include "iconimage.h"

#include <QtCore/qmath.h>
#include <QtQuick/private/qquickimagebase_p_p.h>

#include "iconimage_p.h"

bool IconImagePrivate::updateDevicePixelRatio(qreal targetDevicePixelRatio)
{
    if (isThemeIcon) {
        devicePixelRatio = calculateDevicePixelRatio();
        return true;
    }

    return QQuickImagePrivate::updateDevicePixelRatio(targetDevicePixelRatio);
}

void IconImagePrivate::updateIcon()
{
    Q_Q(IconImage);
    // Both geometryChanged() and QQuickImageBase::sourceSizeChanged()
    // (which we connect to updateIcon() in the constructor) can be called as a result
    // of updateIcon() changing the various sizes, so we must check that we're not recursing.
    if (updatingIcon)
        return;

    updatingIcon = true;

    QSize size = sourcesize;
    // If no size is specified for theme icons, it will use the smallest available size.
    if (size.width() <= 0)
        size.setWidth(q->width());
    if (size.height() <= 0)
        size.setHeight(q->height());

    const qreal dpr = calculateDevicePixelRatio();
    const QIconLoaderEngineEntry* entry = QIconLoaderEngine::entryForSize(icon,
                                                                          size * dpr,
                                                                          qCeil(dpr));

    if (entry) {
        QQmlContext* context = qmlContext(q);
        const QUrl entryUrl = QUrl::fromLocalFile(entry->filename);
        url = context ? context->resolvedUrl(entryUrl) : entryUrl;
        isThemeIcon = true;
    } else {
        url = source;
        isThemeIcon = false;
    }
    q->load();

    updatingIcon = false;
}

void IconImagePrivate::updateFillMode()
{
    Q_Q(IconImage);
    // If we start with a sourceSize of 28x28 and then set sourceSize.width to 24, the fillMode
    // will change to PreserveAspectFit (because pixmapSize.width() > width()), which causes the
    // pixmap to be reloaded at its original size of 28x28, which causes the fillMode to change
    // to Pad (because pixmapSize.width() <= width()), and so on.
    if (updatingFillMode)
        return;

    updatingFillMode = true;

    const QSize pixmapSize = QSize(pix.width(), pix.height()) / calculateDevicePixelRatio();
    if (pixmapSize.width() > q->width() || pixmapSize.height() > q->height())
        q->setFillMode(QQuickImage::PreserveAspectFit);
    else
        q->setFillMode(QQuickImage::Pad);

    updatingFillMode = false;
}

qreal IconImagePrivate::calculateDevicePixelRatio() const
{
    Q_Q(const IconImage);
    return q->window() ? q->window()->effectiveDevicePixelRatio() : qApp->devicePixelRatio();
}

IconImage::IconImage(QQuickItem* parent)
    : QQuickImage(*(new IconImagePrivate), parent)
{
    setFillMode(Pad);
}

QString IconImage::name() const
{
    Q_D(const IconImage);
    return d->icon.iconName;
}

void IconImage::setName(const QString& name)
{
    Q_D(IconImage);
    if (d->icon.iconName == name)
        return;

    d->icon = QIconLoader::instance()->loadIcon(name);
    if (isComponentComplete())
        d->updateIcon();
    emit nameChanged();
}

QColor IconImage::color() const
{
    Q_D(const IconImage);
    return d->color;
}

void IconImage::setColor(const QColor& color)
{
    Q_D(IconImage);
    if (d->color == color)
        return;

    d->color = color;
    if (isComponentComplete())
        d->updateIcon();
    emit colorChanged();
}

void IconImage::setSource(const QUrl& source)
{
    Q_D(IconImage);
    if (d->source == source)
        return;

    d->source = source;
    if (isComponentComplete())
        d->updateIcon();
    emit sourceChanged(source);
}

void IconImage::componentComplete()
{
    Q_D(IconImage);
    QQuickImage::componentComplete();
    d->updateIcon();
    QObjectPrivate::connect(this,
                            &QQuickImageBase::sourceSizeChanged,
                            d,
                            &IconImagePrivate::updateIcon);
}

void IconImage::geometryChanged(const QRectF& newGeometry, const QRectF& oldGeometry)
{
    Q_D(IconImage);
    QQuickImage::geometryChanged(newGeometry, oldGeometry);
    if (isComponentComplete() && newGeometry.size() != oldGeometry.size())
        d->updateIcon();
}

void IconImage::itemChange(ItemChange change, const ItemChangeData& value)
{
    Q_D(IconImage);
    if (change == ItemDevicePixelRatioHasChanged)
        d->updateIcon();
    QQuickImage::itemChange(change, value);
}

void IconImage::pixmapChange()
{
    Q_D(IconImage);
    QQuickImage::pixmapChange();
    d->updateFillMode();

    // Don't apply the color if we're recursing (updateFillMode() can cause us to recurse).
    if (!d->updatingFillMode && d->color.alpha() > 0) {
        QImage image = d->pix.image();
        if (!image.isNull()) {
            QPainter painter(&image);
            painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
            painter.fillRect(image.rect(), d->color);
            d->pix.setImage(image);
        }
    }
}
