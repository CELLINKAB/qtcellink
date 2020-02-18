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

#include "flipview.h"

#include <QtQml/qqmlinfo.h>
#include <QtQuickTemplates2/private/qquickcontainer_p_p.h>

static const qreal FrontAngle = 0;
static const qreal BackAngle = 180;
static const qreal HideAngle = 90;

class FlipViewPrivate : public QQuickContainerPrivate
{
    Q_DECLARE_PUBLIC(FlipView)

public:
    void flip();
    void updateAngle(qreal value);
    QQuickItem *getSide(const char *name);
    void resizeItem(QQuickItem *item);
    void resizeItems();

    void itemImplicitWidthChanged(QQuickItem *item) override;
    void itemImplicitHeightChanged(QQuickItem *item) override;

    qreal getContentWidth() const override;
    qreal getContentHeight() const override;

    bool showBack = false;
    bool showFront = false;
    int previousIndex = -1;
    Qt::Axis axis = Qt::XAxis;
    qreal angle = HideAngle;
};

class FlipViewAttachedPrivate : public QObjectPrivate
{
    Q_DECLARE_PUBLIC(FlipViewAttached)

public:
    static FlipViewAttachedPrivate *get(FlipViewAttached *attached)
    {
        return attached->d_func();
    }

    void update(FlipView *newView, int newIndex);
    void updateCurrentIndex();
    void setCurrentIndex(int i);

    int index = -1;
    int currentIndex = -1;
    FlipView *flipView = nullptr;
};

void FlipViewPrivate::flip()
{
    Q_Q(FlipView);
    if (currentIndex < 0 || currentIndex >= contentModel->count()) {
        showBack = false;
        showFront = false;
    } else if (showFront) {
        showBack = true;
        showFront = false;
    } else {
        showBack = false;
        showFront = true;
    }

    QQuickItem *currentItem = q->itemAt(currentIndex);
    if (currentItem) {
        QQuickItemPrivate::get(currentItem)->setCulled(false);
        currentItem->setParentItem(getSide(showFront ? "front" : showBack ? "back" : nullptr));
    }

    updateAngle(showFront ? FrontAngle : showBack ? BackAngle : HideAngle);

    previousIndex = currentIndex;
}

void FlipViewPrivate::updateAngle(qreal value)
{
    Q_Q(FlipView);
    if (qFuzzyCompare(angle, value))
        return;

    angle = value;
    emit q->angleChanged();
}

QQuickItem *FlipViewPrivate::getSide(const char *name)
{
    QQuickItem *side = contentItem->property(name).value<QQuickItem *>();
    if (!side) {
        side = new QQuickItem(contentItem);
        resizeItem(side);
        contentItem->setProperty(name, QVariant::fromValue(side));
    }
    return side;
}

void FlipViewPrivate::resizeItem(QQuickItem *item)
{
    if (!item)
        return;

    QQuickAnchors *anchors = QQuickItemPrivate::get(item)->_anchors;
    if (anchors && anchors->activeDirections() && !item->property("_FlipView_warned").toBool()) {
        qmlWarning(item) << "FlipView has detected conflicting anchors. Unable to layout the item.";
        item->setProperty("_FlipView_warned", true);
    }
    item->setSize(QSizeF(contentItem->width(), contentItem->height()));
}

void FlipViewPrivate::resizeItems()
{
    Q_Q(FlipView);
    const int count = q->count();
    for (int i = 0; i < count; ++i)
        resizeItem(itemAt(i));
    resizeItem(getSide("front"));
    resizeItem(getSide("back"));
}

void FlipViewPrivate::itemImplicitWidthChanged(QQuickItem *item)
{
    Q_Q(FlipView);
    QQuickContainerPrivate::itemImplicitWidthChanged(item);
    if (item == q->currentItem())
        updateImplicitContentWidth();
}

void FlipViewPrivate::itemImplicitHeightChanged(QQuickItem *item)
{
    Q_Q(FlipView);
    QQuickContainerPrivate::itemImplicitHeightChanged(item);
    if (item == q->currentItem())
        updateImplicitContentHeight();
}

qreal FlipViewPrivate::getContentWidth() const
{
    Q_Q(const FlipView);
    QQuickItem *currentItem = q->currentItem();
    return currentItem ? currentItem->implicitWidth() : 0;
}

qreal FlipViewPrivate::getContentHeight() const
{
    Q_Q(const FlipView);
    QQuickItem *currentItem = q->currentItem();
    return currentItem ? currentItem->implicitHeight() : 0;
}

FlipView::FlipView(QQuickItem *parent)
    : QQuickContainer(*(new FlipViewPrivate), parent)
{
    Q_D(FlipView);
    d->changeTypes |= QQuickItemPrivate::ImplicitWidth | QQuickItemPrivate::ImplicitHeight;
    setFlag(ItemIsFocusScope);
    setActiveFocusOnTab(true);
    QObjectPrivate::connect(this, &QQuickContainer::currentIndexChanged, d, &FlipViewPrivate::flip);
    QObjectPrivate::connect(this, &QQuickContainer::currentItemChanged, d, &QQuickControlPrivate::updateImplicitContentSize);
}

qreal FlipView::angle() const
{
    Q_D(const FlipView);
    return d->angle;
}

Qt::Axis FlipView::axis() const
{
    Q_D(const FlipView);
    return d->axis;
}

void FlipView::setAxis(Qt::Axis axis)
{
    Q_D(FlipView);
    if (d->axis == axis)
        return;

    d->axis = axis;
    emit axisChanged();
}

FlipViewAttached *FlipView::qmlAttachedProperties(QObject *object)
{
    return new FlipViewAttached(object);
}

void FlipView::componentComplete()
{
    Q_D(FlipView);
    QQuickContainer::componentComplete();
    d->resizeItems();
}

void FlipView::geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry)
{
    Q_D(FlipView);
    QQuickContainer::geometryChanged(newGeometry, oldGeometry);
    d->resizeItems();
}

void FlipView::itemAdded(int index, QQuickItem *item)
{
    Q_D(FlipView);
    QQuickItemPrivate::get(item)->setCulled(true);
    FlipViewAttached *attached = qobject_cast<FlipViewAttached *>(qmlAttachedPropertiesObject<FlipView>(item));
    if (attached)
        FlipViewAttachedPrivate::get(attached)->update(this, index);
    d->resizeItem(item);
}

void FlipView::itemMoved(int index, QQuickItem *item)
{
    FlipViewAttached *attached = qobject_cast<FlipViewAttached *>(qmlAttachedPropertiesObject<FlipView>(item));
    if (attached)
        FlipViewAttachedPrivate::get(attached)->update(this, index);
}

void FlipView::itemRemoved(int, QQuickItem *item)
{
    FlipViewAttached *attached = qobject_cast<FlipViewAttached *>(qmlAttachedPropertiesObject<FlipView>(item));
    if (attached)
        FlipViewAttachedPrivate::get(attached)->update(nullptr, -1);
}

#if QT_CONFIG(accessibility)
QAccessible::Role FlipView::accessibleRole() const
{
    return QAccessible::PageTabList;
}
#endif

void FlipViewAttachedPrivate::updateCurrentIndex()
{
    setCurrentIndex(flipView ? flipView->currentIndex() : -1);
}

void FlipViewAttachedPrivate::setCurrentIndex(int i)
{
    if (i == currentIndex)
        return;

    Q_Q(FlipViewAttached);
    const bool wasCurrent = q->isCurrentItem();
    const bool wasPrevious = q->isPreviousItem();

    currentIndex = i;
    if (wasCurrent != q->isCurrentItem())
        emit q->isCurrentItemChanged();
    if (wasPrevious != q->isPreviousItem())
        emit q->isPreviousItemChanged();
}

void FlipViewAttachedPrivate::update(FlipView *newView, int newIndex)
{
    Q_Q(FlipViewAttached);
    int oldIndex = index;
    FlipView *oldView = flipView;

    index = newIndex;
    flipView = newView;

    if (oldView != newView) {
        if (oldView)
            disconnect(oldView, &FlipView::currentIndexChanged, this, &FlipViewAttachedPrivate::updateCurrentIndex);
        if (newView)
            connect(newView, &FlipView::currentIndexChanged, this, &FlipViewAttachedPrivate::updateCurrentIndex);
        emit q->viewChanged();
    }
    if (oldIndex != newIndex)
        emit q->indexChanged();

    updateCurrentIndex();
}

FlipViewAttached::FlipViewAttached(QObject *parent)
    : QObject(*(new FlipViewAttachedPrivate), parent)
{
    if (!qobject_cast<QQuickItem *>(parent))
        qmlWarning(parent) << "FlipView: attached properties must be accessed from within a child item";
}

int FlipViewAttached::index() const
{
    Q_D(const FlipViewAttached);
    return d->index;
}

FlipView *FlipViewAttached::view() const
{
    Q_D(const FlipViewAttached);
    return d->flipView;
}

bool FlipViewAttached::isCurrentItem() const
{
    Q_D(const FlipViewAttached);
    return d->index != -1 && d->currentIndex != -1 && d->index == d->currentIndex;
}

bool FlipViewAttached::isPreviousItem() const
{
    Q_D(const FlipViewAttached);
    return d->index != -1 && d->currentIndex != -1 && d->index == d->currentIndex - 1;
}
