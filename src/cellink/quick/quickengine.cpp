/****************************************************************************
**
** Copyright (C) 2020 CELLINK AB <info@cellink.com>
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

Q_GLOBAL_STATIC(QByteArrayList, allowExternalModules)
static QtMessageHandler messageHandler = nullptr;

QuickEngine::QuickEngine(QObject *parent) : QQmlApplicationEngine(parent)
{
    QLocale locale;
    locale.setNumberOptions(locale.numberOptions() | QLocale::OmitGroupSeparator);
    QLocale::setDefault(locale);
}

static inline QString organizationStylePath()
{
    return QCoreApplication::organizationName() + QStringLiteral("/Styles");
}

void QuickEngine::init(const QString &style, const QString &path)
{
    QIcon::setThemeName(style);
    QQuickStyle::setStyle(style);
    QQuickStyle::addStylePath(path.isEmpty() ? QStringLiteral("qrc:/qt-project.org/imports/%1").arg(organizationStylePath()) : path);
}

static void addStylePaths(const QString &path)
{
    QDir dir(path);
    if (dir.cd(QCoreApplication::organizationName())) {
        dir.cd(QStringLiteral("Styles"));
        QQuickStyle::addStylePath(dir.path());
    }
}

static void initEngine(QQmlEngine *engine)
{
    QQmlContext *context = engine->rootContext();
    context->setContextProperty("QT_VERSION_STR", QT_VERSION_STR);
    context->setContextProperty("BUILD_DATE", __DATE__);
    context->setContextProperty("BUILD_TIME", __TIME__);

    engine->addImportPath(":/qml");

    QDir appDir(QCoreApplication::applicationDirPath());
    if (appDir.exists(QCoreApplication::organizationName()) || appDir.cd("../qml") || appDir.cd("../Resources/qml")) {
        engine->addImportPath(appDir.absolutePath());
        addStylePaths(appDir.path());
    } else {
        const QStringList importPaths = engine->importPathList();
        for (const QString &importPath : importPaths)
            addStylePaths(importPath);
    }
}

bool QuickEngine::load(const QUrl &url)
{
    if (rootObjects().isEmpty())
        initEngine(this);

    QQmlApplicationEngine::load(url);
    if (messageHandler)
        qInstallMessageHandler(messageHandler);
    messageHandler = nullptr;
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


void externalRegistrationHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    if (type == QtWarningMsg && msg.startsWith("Module '")) {
        const QByteArrayList modules = *allowExternalModules();
        for (const QByteArray &module : modules) {
            if (msg == QStringLiteral("Module '%1' does not contain a module identifier directive - it cannot be protected from external registrations.").arg(QString::fromLocal8Bit(module)))
                return;
        }
    }
    if (messageHandler)
        messageHandler(type, context, msg);
}

void QuickEngine::allowExternalRegistrations(const char *uri)
{
    if (!messageHandler)
        messageHandler = qInstallMessageHandler(externalRegistrationHandler);

    allowExternalModules()->append(uri);
}
