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

#include "yoctolicensemodel.h"
#include <QtCore/qdir.h>
#include <QtCore/qfile.h>
#include <QtCore/qfileinfo.h>
#include <QtCore/qpointer.h>
#include <QtCore/qtextstream.h>
#include <thread>

static const QLatin1String PackageKey("PACKAGE NAME");
static const QLatin1String VersionKey("PACKAGE VERSION");
static const QLatin1String RecipeKey("RECIPE NAME");
static const QLatin1String LicenseKey("LICENSE");
static const QString LicenseFile = QStringLiteral("generic_%1");

YoctoLicenseModel::YoctoLicenseModel(QObject *parent) : QAbstractListModel(parent)
{
    qRegisterMetaType<Status>("Status");
    qRegisterMetaType<YoctoLicense>("YoctoLicense");
}

YoctoLicenseModel::Status YoctoLicenseModel::status() const
{
    return m_status;
}

int YoctoLicenseModel::count() const
{
    return m_licenses.count();
}

bool YoctoLicenseModel::isEmpty() const
{
    return m_licenses.isEmpty();
}

QString YoctoLicenseModel::manifest() const
{
    return m_manifest;
}

static YoctoLicense parseLicense(YoctoLicense license, const QString &value, const QStringList &licenses)
{
    license.licenses = licenses;
    const QStringList parts = value.split(QLatin1Char(' '), Qt::SkipEmptyParts);
    for (QString part : parts) {
        while (!part.isEmpty() && !part.front().isLetterOrNumber())
            part.remove(0, 1);
        while (!part.isEmpty() && !part.back().isLetterOrNumber())
            part.chop(1);
        if (!part.isEmpty() && !license.licenses.contains(part))
            license.licenses += part;
    }
    return license;
}

void YoctoLicenseModel::setManifest(const QString &manifest)
{
    if (m_manifest == manifest)
        return;

    m_manifest = manifest;

    setStatus(Loading);
    QPointer<YoctoLicenseModel> model(this);
    std::thread([model, manifest]() {
        QFile file(manifest);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QMetaObject::invokeMethod(model.data(), "setStatus", Qt::QueuedConnection, Q_ARG(Status, Error));
            return;
        }

        QString line;
        YoctoLicense license;
        QMap<QString, YoctoLicense> licenses;
        QTextStream stream(&file);
        while (!model.isNull() && stream.readLineInto(&line)) {
            int colon = line.indexOf(QLatin1Char(':'));
            if (colon == -1)
                continue;

            const QString key = line.mid(0, colon).trimmed();
            const QString value = line.mid(colon + 1).trimmed();
            if (key == PackageKey)
                license = value;
            else if (key == VersionKey)
                license.version = value;
            else if (key == RecipeKey)
                license.name = value;
            else if (key == LicenseKey)
                licenses.insert(license.name, parseLicense(license, value, licenses.value(license.name).licenses));
        }

        if (model) {
            QMetaObject::invokeMethod(model.data(), "setLicenses", Qt::QueuedConnection, Q_ARG(QList<YoctoLicense>, licenses.values()));
            QMetaObject::invokeMethod(model.data(), "setStatus", Qt::QueuedConnection, Q_ARG(Status, Ready));
        }
    }).detach();

    emit manifestChanged();
}

QHash<int, QByteArray> YoctoLicenseModel::roleNames() const
{
    return {
        { NameRole, "name" },
        { VersionRole, "version" },
        { LicensesRole, "licenses" }
    };
}

int YoctoLicenseModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_licenses.count();
}

QVariant YoctoLicenseModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    YoctoLicense license = m_licenses.value(index.row());
    switch (role) {
    case NameRole:
        return license.name;
    case VersionRole:
        return license.version;
    case LicensesRole:
        return license.licenses;
    default:
        break;
    }

    return QVariant();
}

YoctoLicense YoctoLicenseModel::get(int index) const
{
    return m_licenses.value(index);
}

QString YoctoLicenseModel::read(const QString &name) const
{
    QString filePath = QFileInfo(m_manifest).dir().filePath(LicenseFile.arg(name));
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return QString();

    return QTextStream(&file).readAll();
}

void YoctoLicenseModel::setStatus(Status status)
{
    if (m_status == status)
        return;

    m_status = status;
    emit statusChanged();
}

void YoctoLicenseModel::setLicenses(const QList<YoctoLicense> &licenses)
{
    if (m_licenses == licenses)
        return;

    int oldCount = m_licenses.count();
    bool wasEmpty = m_licenses.isEmpty();
    beginResetModel();
    m_licenses = licenses;
    endResetModel();
    if (wasEmpty != licenses.isEmpty())
        emit emptyChanged();
    if (oldCount != licenses.count())
        emit countChanged();
}
