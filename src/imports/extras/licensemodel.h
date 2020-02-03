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

#ifndef LICENSEMODEL_H
#define LICENSEMODEL_H

#include <QtCore/qabstractitemmodel.h>
#include "license.h"

/*!
    \class LicenseModel
    \ingroup license-qml
    \brief Indexes Yocto licenses

    ...
*/
class LicenseModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(Status status READ status NOTIFY statusChanged)
    Q_PROPERTY(int count READ count NOTIFY countChanged)
    Q_PROPERTY(bool empty READ isEmpty NOTIFY emptyChanged)
    Q_PROPERTY(QString manifest READ manifest WRITE setManifest NOTIFY manifestChanged)

public:
    explicit LicenseModel(QObject *parent = nullptr);

    enum Status { Null, Ready, Loading, Error };
    Q_ENUM(Status)

    Status status() const;
    int count() const;
    bool isEmpty() const;

    QString manifest() const;
    void setManifest(const QString &manifest);

    enum DataRole { NameRole, VersionRole, LicensesRole };
    Q_ENUM(DataRole)

    QHash<int, QByteArray> roleNames() const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = NameRole) const override;

    Q_INVOKABLE License get(int index) const;
    Q_INVOKABLE QString read(const QString &name) const;

signals:
    void statusChanged();
    void countChanged();
    void emptyChanged();
    void manifestChanged();

private slots:
    void setStatus(Status status);
    void setLicenses(const QList<License> &licenses);

private:
    Status m_status = Null;
    QString m_manifest;
    QList<License> m_licenses;
};

#endif // LICENSEMODEL_H
