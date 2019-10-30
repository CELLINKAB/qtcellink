/****************************************************************************
**
** Copyright (C) 2019 CELLINK AB <info@cellink.com>
**
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are met:
**
** 1. Redistributions of source code must retain the above copyright notice,
**    this list of conditions and the following disclaimer.
**
** 2. Redistributions in binary form must reproduce the above copyright notice,
**    this list of conditions and the following disclaimer in the documentation
**    and/or other materials provided with the distribution.
**
** 3. Neither the name of the copyright holder nor the names of its contributors
**    may be used to endorse or promote products derived from this software
**    without specific prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
** AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
** IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
** ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
** LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
** CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
** SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
** INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
** CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
** ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
** POSSIBILITY OF SUCH DAMAGE.
**
****************************************************************************/

#include "quickengine.h"

#include <QtCore/qdir.h>
#include <QtCore/qlocale.h>
#include <QtGui/qfont.h>
#include <QtGui/qfontdatabase.h>
#include <QtGui/qguiapplication.h>
#include <QtGui/qicon.h>
#include <QtQml/qqmlcontext.h>
#include <QtQuickControls2/qquickstyle.h>

QuickEngine::QuickEngine(QObject *parent) : QQmlApplicationEngine(parent)
{
    QLocale locale;
    locale.setNumberOptions(locale.numberOptions() | QLocale::OmitGroupSeparator);
    QLocale::setDefault(locale);

#if !defined(Q_OS_MACOS)
    QString appPath = QCoreApplication::applicationDirPath();
    QStringList libraryPaths = QCoreApplication::libraryPaths();
    QDir pluginDir(appPath);
    if (pluginDir.cd("../plugins"))
        libraryPaths.prepend(pluginDir.canonicalPath());
    libraryPaths.prepend(appPath);
    QCoreApplication::setLibraryPaths(libraryPaths);
#endif
}

static inline QString organizationStylePath()
{
    return QCoreApplication::organizationName() + QStringLiteral("/Styles");
}

void QuickEngine::init(const QString &style)
{
    QIcon::setThemeName(style);
    QQuickStyle::setStyle(style);
    QQuickStyle::addStylePath(QStringLiteral("qrc:/qt-project.org/imports/%1").arg(organizationStylePath()));
}

static void initEngine(QQmlEngine *engine)
{
    QQmlContext *context = engine->rootContext();
    context->setContextProperty("QT_VERSION_STR", QT_VERSION_STR);
#ifdef BUILD_DATE
    context->setContextProperty("BUILD_DATE", BUILD_DATE);
#endif

    engine->addImportPath(":/qml");

    QDir appDir(QCoreApplication::applicationDirPath());
    if (appDir.exists(QCoreApplication::organizationName()) || appDir.cd("../qml") || appDir.cd("../Resources/qml")) {
        engine->addImportPath(appDir.absolutePath());
        if (appDir.cd(organizationStylePath()))
            QQuickStyle::addStylePath(appDir.path());
    } else {
        const QStringList importPaths = engine->importPathList();
        for (const QString &importPath : importPaths) {
            QDir importDir(importPath);
            if (importDir.cd(organizationStylePath()))
                QQuickStyle::addStylePath(importDir.path());
        }
    }
}

bool QuickEngine::load(const QUrl &url)
{
    if (rootObjects().isEmpty())
        initEngine(this);

    QQmlApplicationEngine::load(url);
    return !rootObjects().isEmpty();
}

void QuickEngine::addFont(const QString &source)
{
    QFontDatabase::addApplicationFont(source);
}

void QuickEngine::setFont(const QString &family, int pixelSize)
{
    QFont font(family);
    font.setPixelSize(pixelSize);
    QGuiApplication::setFont(font);
}
