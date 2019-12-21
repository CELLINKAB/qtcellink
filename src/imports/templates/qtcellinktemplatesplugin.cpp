/****************************************************************************
**
** Copyright (C) 2019 CELLINK AB <info@cellink.com>
**
** This file is part of QtCellink.
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

#include <QtQml/qqmlextensionplugin.h>
#include <QtQml/qqml.h>
#include <QtCore/qloggingcategory.h>

#include "buttonrow.h"
#include "doublespinbox.h"
#include "flipview.h"
#include "progressindicator.h"
#include "rowbutton.h"
#include "tabbar.h"
#include "titleseparator.h"

#include "nativemenubar.h"
#include "nativemenu.h"
#include "nativemenuitem.h"
#include "nativemenuseparator.h"

Q_LOGGING_CATEGORY(lcMenus, "qtcellink.menus")

class QtCellinkTemplatesPlugin: public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)

public:
    QtCellinkTemplatesPlugin(QObject *parent = nullptr);
    void registerTypes(const char *uri) override;
};

QtCellinkTemplatesPlugin::QtCellinkTemplatesPlugin(QObject *parent) : QQmlExtensionPlugin(parent)
{
}

void QtCellinkTemplatesPlugin::registerTypes(const char *uri)
{
    qmlRegisterType<ButtonRow>(uri, 1, 0, "ButtonRow");
    qmlRegisterType<DoubleSpinBox>(uri, 1, 0, "DoubleSpinBox");
    qmlRegisterType<DoubleSpinButton>();
    qmlRegisterType<FlipView>(uri, 1, 0, "FlipView");
    qmlRegisterType<FlipViewAttached>();
    qmlRegisterType<ProgressIndicator>(uri, 1, 0, "ProgressIndicator");
    qmlRegisterType<RowButton>(uri, 1, 0, "RowButton");
    qmlRegisterType<TabBar>(uri, 1, 0, "TabBar");
    qmlRegisterType<TabBarAttached>();
    qmlRegisterType<TitleSeparator>(uri, 1, 0, "TitleSeparator");

    qmlRegisterType<NativeMenu>(uri, 1, 0, "NativeMenu");
    qmlRegisterType<NativeMenuBar>(uri, 1, 0, "NativeMenuBar");
    qmlRegisterType<NativeMenuItem>(uri, 1, 0, "NativeMenuItem");
    qmlRegisterType<NativeMenuSeparator>(uri, 1, 0, "NativeMenuSeparator");

    qmlRegisterRevision<QQuickItem, QT_VERSION_MINOR>(uri, 1, 0);
    qmlRegisterRevision<QQuickControl, QT_VERSION_MINOR>(uri, 1, 0);
    qmlRegisterRevision<QQuickContainer, QT_VERSION_MINOR>(uri, 1, 0);
    qmlRegisterRevision<QQuickAbstractButton, QT_VERSION_MINOR>(uri, 1, 0);
    qmlRegisterRevision<QQuickTabBar, QT_VERSION_MINOR>(uri, 1, 0);
}

#include "qtcellinktemplatesplugin.moc"
