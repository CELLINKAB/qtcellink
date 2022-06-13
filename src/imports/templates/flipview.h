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

#ifndef FLIPVIEW_H
#define FLIPVIEW_H

#include <QtQuickTemplates2/private/qquickcontainer_p.h>

class FlipViewAttached;
class FlipViewPrivate;

class FlipView : public QQuickContainer
{
    Q_OBJECT
    Q_PROPERTY(qreal angle READ angle NOTIFY angleChanged FINAL)
    Q_PROPERTY(Qt::Axis axis READ axis WRITE setAxis NOTIFY axisChanged FINAL)

public:
    explicit FlipView(QQuickItem* parent = nullptr);

    qreal angle() const;

    Qt::Axis axis() const;
    void setAxis(Qt::Axis axis);

    QQuickItem* front() const;
    QQuickItem* back() const;

    static FlipViewAttached* qmlAttachedProperties(QObject* object);

Q_SIGNALS:
    void angleChanged();
    void axisChanged();

protected:
    void componentComplete() override;
    void geometryChanged(const QRectF& newGeometry, const QRectF& oldGeometry) override;

    void itemAdded(int index, QQuickItem* item) override;
    void itemMoved(int index, QQuickItem* item) override;
    void itemRemoved(int index, QQuickItem* item) override;

#if QT_CONFIG(accessibility)
    QAccessible::Role accessibleRole() const override;
#endif

private:
    Q_DISABLE_COPY(FlipView)
    Q_DECLARE_PRIVATE(FlipView)
};

class FlipViewAttachedPrivate;

class FlipViewAttached : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int index READ index NOTIFY indexChanged FINAL)
    Q_PROPERTY(FlipView* view READ view NOTIFY viewChanged FINAL)
    Q_PROPERTY(bool isCurrentItem READ isCurrentItem NOTIFY isCurrentItemChanged FINAL)
    Q_PROPERTY(bool isPreviousItem READ isPreviousItem NOTIFY isPreviousItemChanged FINAL)

public:
    explicit FlipViewAttached(QObject* parent = nullptr);

    int index() const;
    FlipView* view() const;
    bool isCurrentItem() const;
    bool isPreviousItem() const;

Q_SIGNALS:
    void indexChanged();
    void viewChanged();
    void isCurrentItemChanged();
    void isPreviousItemChanged();

private:
    Q_DISABLE_COPY(FlipViewAttached)
    Q_DECLARE_PRIVATE(FlipViewAttached)
};

QML_DECLARE_TYPE(FlipView)
QML_DECLARE_TYPEINFO(FlipView, QML_HAS_ATTACHED_PROPERTIES)

#endif // FLIPVIEW_H
