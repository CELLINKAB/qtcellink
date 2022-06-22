/****************************************************************************
**
** Copyright (C) 2020 CELLINK AB <info@cellink.com>
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

#include <QtQml/qqml.h>
#include <QtQml/qqmlengine.h>
#include <QtQml/qqmlextensionplugin.h>

#include "color.h"
#include "colorimage.h"
#include "componentmodel.h"
#include "filtermodel.h"
#include "iconimage.h"
#include "iconlabel.h"
#include "keyboard.h"
#include "mnemoniclabel.h"
#include "navigationgroup.h"
#include "navigationitem.h"
#include "navigationstack.h"
#include "nodedelegate.h"
#include "nodeitem.h"
#include "nodeview.h"
#include "paddedrectangle.h"
#include "rect.h"
#include "yoctolicense.h"
#include "yoctolicensemodel.h"

#if (QT_VERSION < QT_VERSION_CHECK(5, 14, 0))
template<typename T>
static void qmlRegisterAnonymousType(const char*, int)
{
    qmlRegisterType<T>();
}
#endif

class QtCellinkExtrasPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)

public:
    explicit QtCellinkExtrasPlugin(QObject* parent = nullptr);

    void registerTypes(const char* uri) override;
};

QtCellinkExtrasPlugin::QtCellinkExtrasPlugin(QObject* parent)
    : QQmlExtensionPlugin(parent)
{}

namespace {
template<typename T>
int workaroundQmlRegisterType(const char* uri, int versionMajor, int versionMinor, const char* qmlName)
{
    QML_GETTYPENAMES

    QQmlPrivate::RegisterType type
        = {0,
           qRegisterNormalizedMetaType<T*>(pointerName.constData()),
           qRegisterNormalizedMetaType<QQmlListProperty<T>>(listName.constData()),
           sizeof(T),
           QQmlPrivate::createInto<T>,
           QString(),
           uri,
           versionMajor,
           versionMinor,
           qmlName,
           &T::staticMetaObject,
           QQmlPrivate::attachedPropertiesFunc<T>(),
           T::qmlAttachedProperties(nullptr)->metaObject(),
           QQmlPrivate::StaticCastSelector<T, QQmlParserStatus>::cast(),
           QQmlPrivate::StaticCastSelector<T, QQmlPropertyValueSource>::cast(),
           QQmlPrivate::StaticCastSelector<T, QQmlPropertyValueInterceptor>::cast(),
           nullptr,
           nullptr,
           nullptr,
           0};

    return QQmlPrivate::qmlregister(QQmlPrivate::TypeRegistration, &type);
}

} // namespace

void QtCellinkExtrasPlugin::registerTypes(const char* uri)
{
#if (QT_VERSION < QT_VERSION_CHECK(5, 15, 0))
    qmlRegisterType<ComponentModel>(uri, 1, 0, "ComponentModel");
#else
    workaroundQmlRegisterType<ComponentModel>(uri, 1, 0, "ComponentModel");
#endif

    qmlRegisterSingletonType<Color>(uri, 1, 0, "Color", [](QQmlEngine* engine, QJSEngine*) -> QObject* {
        return new Color(engine);
    });
    qmlRegisterType<ColorImage>(uri, 1, 0, "ColorImage");
    qmlRegisterType<FilterModel>(uri, 1, 0, "FilterModel");
    qmlRegisterType<HeaderDelegate>(uri, 1, 0, "HeaderDelegate");
    qmlRegisterType<IconImage>(uri, 1, 0, "IconImage");
    qmlRegisterType<IconLabel>(uri, 1, 0, "IconLabel");
    qmlRegisterSingletonType<Keyboard>(uri,
                                       1,
                                       0,
                                       "Keyboard",
                                       [](QQmlEngine* engine, QJSEngine*) -> QObject* {
                                           return new Keyboard(engine);
                                       });
    qRegisterMetaType<YoctoLicense>();
    qmlRegisterType<YoctoLicenseModel>(uri, 1, 0, "YoctoLicenseModel");
    qmlRegisterType<MnemonicLabel>(uri, 1, 0, "MnemonicLabel");
    qmlRegisterType<NavigationGroup>(uri, 1, 0, "NavigationGroup");
    qmlRegisterType<NavigationItem>(uri, 1, 0, "NavigationItem");
    qmlRegisterType<NavigationStack>(uri, 1, 0, "NavigationStack");
    qmlRegisterType<NodeItem>(uri, 1, 0, "NodeItem");
    qmlRegisterType<NodeView>(uri, 1, 0, "NodeView");
    qmlRegisterAnonymousType<NodeDelegate>(uri, 1);
    qmlRegisterType<OpacityDelegate>(uri, 1, 0, "OpacityDelegate");
    qmlRegisterType<PaddedRectangle>(uri, 1, 0, "PaddedRectangle");
    qmlRegisterType<ProgressDelegate>(uri, 1, 0, "ProgressDelegate");
    qmlRegisterSingletonType<Rect>(uri, 1, 0, "Rect", [](QQmlEngine* engine, QJSEngine*) -> QObject* {
        return new Rect(engine);
    });
    qmlRegisterType<RectDelegate>(uri, 1, 0, "RectDelegate");
    qmlRegisterType<ScaleDelegate>(uri, 1, 0, "ScaleDelegate");
    qmlRegisterType<TextDelegate>(uri, 1, 0, "TextDelegate");

    qmlRegisterRevision<QQuickItem, QT_VERSION_MINOR>(uri, 1, 0);
    qmlRegisterRevision<QQuickFlickable, QT_VERSION_MINOR>(uri, 1, 0);
}

#include "qtcellinkextrasplugin.moc"
