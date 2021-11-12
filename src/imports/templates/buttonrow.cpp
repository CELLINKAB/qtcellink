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

#include "buttonrow.h"

#include <QtCore/qmath.h>
#include <QtGui/qfontinfo.h>
#include <QtQuickTemplates2/private/qquickcontainer_p_p.h>
#include <QtQuickTemplates2/private/qquicktheme_p.h>

#include "rowbutton.h"

class ButtonRowPrivate : public QQuickContainerPrivate
{
    Q_DECLARE_PUBLIC(ButtonRow)

public:
    void activate();
    void updateAttachedProperties();
    void updateCurrentItem();
    void updateCurrentIndex();
    void updateLayout();

    qreal getContentWidth() const override;
    qreal getContentHeight() const override;

    void itemGeometryChanged(QQuickItem* item,
                             QQuickGeometryChange change,
                             const QRectF& diff) override;
    void itemImplicitWidthChanged(QQuickItem* item) override;
    void itemImplicitHeightChanged(QQuickItem* item) override;

    bool exclusive = true;
    bool updatingLayout = false;
};

class ButtonRowAttachedPrivate : public QObjectPrivate
{
    Q_DECLARE_PUBLIC(ButtonRowAttached)

public:
    static ButtonRowAttachedPrivate* get(ButtonRowAttached* attached) { return attached->d_func(); }

    void update(ButtonRow* buttonRow, int index);

    int index = -1;
    bool isLastItem = true;
    bool isFirstItem = true;
    ButtonRow* buttonRow = nullptr;
};

void ButtonRowPrivate::activate()
{
    Q_Q(ButtonRow);
    RowButton* button = qobject_cast<RowButton*>(q->sender());
    if (button)
        emit q->activated(contentModel->indexOf(button, nullptr));
}

void ButtonRowPrivate::updateAttachedProperties()
{
    Q_Q(ButtonRow);
    const int count = contentModel->count();
    for (int i = 0; i < count; ++i) {
        RowButton* button = qobject_cast<RowButton*>(q->itemAt(i));
        if (button) {
            ButtonRowAttached* attached = qobject_cast<ButtonRowAttached*>(
                qmlAttachedPropertiesObject<ButtonRow>(button));
            if (attached)
                ButtonRowAttachedPrivate::get(attached)->update(q, i);
        }
    }
}

void ButtonRowPrivate::updateCurrentItem()
{
    Q_Q(ButtonRow);
    if (!exclusive)
        return;

    RowButton* button = qobject_cast<RowButton*>(contentModel->get(currentIndex));
    if (button) {
        button->setChecked(true);
    } else {
        const int count = contentModel->count();
        for (int i = 0; i < count; ++i) {
            RowButton* button = qobject_cast<RowButton*>(q->itemAt(i));
            if (button)
                button->setChecked(false);
        }
    }
}

void ButtonRowPrivate::updateCurrentIndex()
{
    Q_Q(ButtonRow);
    if (!exclusive)
        return;

    RowButton* button = qobject_cast<RowButton*>(q->sender());
    if (button && button->isChecked())
        q->setCurrentIndex(contentModel->indexOf(button, nullptr));
}

void ButtonRowPrivate::updateLayout()
{
    Q_Q(ButtonRow);
    const int count = contentModel->count();
    if (count <= 0 || !contentItem)
        return;

    const qreal totalSpacing = qMax(0, count - 1) * spacing;
    const qreal itemWidth = qFloor((contentItem->width() - totalSpacing) / qMax(1, count));

    updatingLayout = true;
    for (int i = 0; i < count; ++i) {
        QQuickItem* item = q->itemAt(i);
        if (item)
            item->setSize(QSizeF(itemWidth, contentHeight));
    }
    updatingLayout = false;
}

qreal ButtonRowPrivate::getContentWidth() const
{
    Q_Q(const ButtonRow);
    const int count = contentModel->count();
    qreal maxWidth = 0;
    for (int i = 0; i < count; ++i) {
        QQuickItem* item = q->itemAt(i);
        if (item)
            maxWidth = qMax<qreal>(maxWidth, qCeil(item->implicitWidth()));
    }
    return count * maxWidth;
}

qreal ButtonRowPrivate::getContentHeight() const
{
    Q_Q(const ButtonRow);
    const int count = contentModel->count();
    qreal maxHeight = 0;
    for (int i = 0; i < count; ++i) {
        QQuickItem* item = q->itemAt(i);
        if (item)
            maxHeight = qMax<qreal>(maxHeight, qCeil(item->implicitHeight()));
    }
    return maxHeight;
}

void ButtonRowPrivate::itemGeometryChanged(QQuickItem* item,
                                           QQuickGeometryChange change,
                                           const QRectF& diff)
{
    QQuickContainerPrivate::itemGeometryChanged(item, change, diff);
    if (!updatingLayout) {
        if (change.sizeChange())
            updateImplicitContentSize();
        updateLayout();
    }
}

void ButtonRowPrivate::itemImplicitWidthChanged(QQuickItem* item)
{
    QQuickContainerPrivate::itemImplicitWidthChanged(item);
    if (item != contentItem)
        updateImplicitContentWidth();
}

void ButtonRowPrivate::itemImplicitHeightChanged(QQuickItem* item)
{
    QQuickContainerPrivate::itemImplicitHeightChanged(item);
    if (item != contentItem)
        updateImplicitContentHeight();
}

ButtonRow::ButtonRow(QQuickItem* parent)
    : QQuickContainer(*(new ButtonRowPrivate), parent)
{
    Q_D(ButtonRow);
    d->changeTypes |= QQuickItemPrivate::Geometry | QQuickItemPrivate::ImplicitWidth
                      | QQuickItemPrivate::ImplicitHeight;
    setFlag(ItemIsFocusScope);
    QObjectPrivate::connect(this,
                            &ButtonRow::currentIndexChanged,
                            d,
                            &ButtonRowPrivate::updateCurrentItem);
}

bool ButtonRow::isExclusive() const
{
    Q_D(const ButtonRow);
    return d->exclusive;
}

void ButtonRow::setExclusive(bool exclusive)
{
    Q_D(ButtonRow);
    if (d->exclusive == exclusive)
        return;

    d->exclusive = exclusive;
    const int count = d->contentModel->count();
    for (int i = 0; i < count; ++i) {
        RowButton* button = qobject_cast<RowButton*>(itemAt(i));
        if (button)
            button->setAutoExclusive(exclusive);
    }
    emit exclusiveChanged();
}

ButtonRowAttached* ButtonRow::qmlAttachedProperties(QObject* object)
{
    return new ButtonRowAttached(object);
}

void ButtonRow::updatePolish()
{
    Q_D(ButtonRow);
    QQuickContainer::updatePolish();
    d->updateLayout();
}

void ButtonRow::componentComplete()
{
    Q_D(ButtonRow);
    QQuickContainer::componentComplete();
    d->updateCurrentItem();
    d->updateLayout();
}

void ButtonRow::geometryChanged(const QRectF& newGeometry, const QRectF& oldGeometry)
{
    Q_D(ButtonRow);
    QQuickContainer::geometryChanged(newGeometry, oldGeometry);
    d->updateLayout();
}

bool ButtonRow::isContent(QQuickItem* item) const
{
    return qobject_cast<RowButton*>(item);
}

void ButtonRow::itemAdded(int index, QQuickItem* item)
{
    Q_D(ButtonRow);
    Q_UNUSED(index);
    QQuickItemPrivate::get(item)->setCulled(true); // QTBUG-55129
    if (RowButton* button = qobject_cast<RowButton*>(item)) {
        button->setAutoExclusive(d->exclusive);
        QObjectPrivate::connect(button, &RowButton::toggled, d, &ButtonRowPrivate::activate);
        QObjectPrivate::connect(button,
                                &RowButton::checkedChanged,
                                d,
                                &ButtonRowPrivate::updateCurrentIndex);
    }
    d->updateAttachedProperties();
    d->updateImplicitContentSize();
    if (isComponentComplete())
        polish();
}

void ButtonRow::itemMoved(int index, QQuickItem* item)
{
    Q_D(ButtonRow);
    Q_UNUSED(index)
    Q_UNUSED(item)
    d->updateAttachedProperties();
}

void ButtonRow::itemRemoved(int index, QQuickItem* item)
{
    Q_D(ButtonRow);
    Q_UNUSED(index);
    if (RowButton* button = qobject_cast<RowButton*>(item)) {
        QObjectPrivate::disconnect(button, &RowButton::clicked, d, &ButtonRowPrivate::activate);
        QObjectPrivate::disconnect(button,
                                   &RowButton::checkedChanged,
                                   d,
                                   &ButtonRowPrivate::updateCurrentIndex);
    }
    d->updateAttachedProperties();
    ButtonRowAttached* attached = qobject_cast<ButtonRowAttached*>(
        qmlAttachedPropertiesObject<ButtonRow>(item));
    if (attached)
        ButtonRowAttachedPrivate::get(attached)->update(nullptr, -1);
    d->updateImplicitContentSize();
    if (isComponentComplete())
        polish();
}

QFont ButtonRow::defaultFont() const
{
    // ### TODO: fonts for custom controls via QQuickTheme?
    return QQuickTheme::font(QQuickTheme::TabBar);
}

QPalette ButtonRow::defaultPalette() const
{
    return QQuickTheme::palette(QQuickTheme::TabBar);
}

#if QT_CONFIG(accessibility)
QAccessible::Role ButtonRow::accessibleRole() const
{
    return QAccessible::PageTabList;
}
#endif

void ButtonRowAttachedPrivate::update(ButtonRow* newButtonRow, int newIndex)
{
    Q_Q(ButtonRowAttached);
    const int oldIndex = index;
    const ButtonRow* oldButtonRow = buttonRow;
    const bool oldIsLastItem = isLastItem;
    const bool oldIsFirstItem = isFirstItem;

    const int count = newButtonRow ? newButtonRow->count() : 0;

    index = newIndex;
    buttonRow = newButtonRow;
    isLastItem = newIndex == count - 1;
    isFirstItem = newIndex == 0;

    if (oldButtonRow != newButtonRow)
        emit q->buttonRowChanged();
    if (oldIndex != newIndex)
        emit q->indexChanged();
    if (oldIsLastItem != isLastItem)
        emit q->isLastItemChanged();
    if (oldIsFirstItem != isFirstItem)
        emit q->isFirstItemChanged();
}

ButtonRowAttached::ButtonRowAttached(QObject* parent)
    : QObject(*(new ButtonRowAttachedPrivate), parent)
{}

int ButtonRowAttached::index() const
{
    Q_D(const ButtonRowAttached);
    return d->index;
}

bool ButtonRowAttached::isLastItem() const
{
    Q_D(const ButtonRowAttached);
    return d->isLastItem;
}

bool ButtonRowAttached::isFirstItem() const
{
    Q_D(const ButtonRowAttached);
    return d->isFirstItem;
}

ButtonRow* ButtonRowAttached::buttonRow() const
{
    Q_D(const ButtonRowAttached);
    return d->buttonRow;
}
