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

#ifndef BUTTONROW_H
#define BUTTONROW_H

#include <QtQuickTemplates2/private/qquickcontainer_p.h>
#include <QtQml/qqml.h>

class ButtonRowPrivate;
class ButtonRowAttached;
class ButtonRowAttachedPrivate;

class ButtonRow : public QQuickContainer
{
    Q_OBJECT
    Q_PROPERTY(bool exclusive READ isExclusive WRITE setExclusive NOTIFY exclusiveChanged)

public:
    explicit ButtonRow(QQuickItem *parent = nullptr);

    bool isExclusive() const;
    void setExclusive(bool exclusive);

    static ButtonRowAttached *qmlAttachedProperties(QObject *object);

Q_SIGNALS:
    void exclusiveChanged();
    void activated(int index);

protected:
    void updatePolish() override;
    void componentComplete() override;
    void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry) override;
    bool isContent(QQuickItem *item) const override;
    void itemAdded(int index, QQuickItem *item) override;
    void itemMoved(int index, QQuickItem *item) override;
    void itemRemoved(int index, QQuickItem *item) override;

    QFont defaultFont() const override;
    QPalette defaultPalette() const override;

#if QT_CONFIG(accessibility)
    QAccessible::Role accessibleRole() const override;
#endif

private:
    Q_DISABLE_COPY(ButtonRow)
    Q_DECLARE_PRIVATE(ButtonRow)
};

class ButtonRowAttached : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int index READ index NOTIFY indexChanged FINAL)
    Q_PROPERTY(bool isLastItem READ isLastItem NOTIFY isLastItemChanged FINAL)
    Q_PROPERTY(bool isFirstItem READ isFirstItem NOTIFY isFirstItemChanged FINAL)
    Q_PROPERTY(ButtonRow *buttonRow READ buttonRow NOTIFY buttonRowChanged FINAL)

public:
    explicit ButtonRowAttached(QObject *parent = nullptr);

    int index() const;
    bool isLastItem() const;
    bool isFirstItem() const;
    ButtonRow *buttonRow() const;

Q_SIGNALS:
    void indexChanged();
    void isLastItemChanged();
    void isFirstItemChanged();
    void buttonRowChanged();

private:
    Q_DISABLE_COPY(ButtonRowAttached)
    Q_DECLARE_PRIVATE(ButtonRowAttached)
};

QML_DECLARE_TYPE(ButtonRow)
QML_DECLARE_TYPEINFO(ButtonRow, QML_HAS_ATTACHED_PROPERTIES)

#endif // BUTTONROW_H
