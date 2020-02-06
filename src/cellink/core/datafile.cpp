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

#include "datafile.h"
#include <QtCore/qdatastream.h>
#include <QtCore/qfile.h>
#include <QtCore/qfileinfo.h>
#include <QtCore/qloggingcategory.h>
#include <QtCore/qvariant.h>

Q_LOGGING_CATEGORY(lcData, "qtcellink.data")

DataFile::DataFile(const QString &filePath) : m_filePath(filePath)
{
}

QString DataFile::filePath() const
{
    return m_filePath;
}

static inline QString fileName(const QString &filePath)
{
    return QFileInfo(filePath).fileName();
}

static QByteArray qualifiedPropertyName(const char *className, const char *propertyName, int revision)
{
    QByteArray name = className + QByteArray("::") + propertyName;
    if (revision > 0)
        name += " (REVISION " + QByteArray::number(revision) + ")";
    return name;
}

static QByteArray streamStatusString(QDataStream::Status status)
{
    switch (status) {
    case QDataStream::Ok: return "QDataStream::Ok";
    case QDataStream::ReadPastEnd: return "QDataStream::ReadPastEnd";
    case QDataStream::ReadCorruptData: return "QDataStream::ReadCorruptData";
    case QDataStream::WriteFailed: return "QDataStream::WriteFailed";
    default: return "QDataStream::Status(" + QByteArray::number(status) +")";
    }
}

bool DataFile::loadGadget(void *gadget, const QMetaObject *metaObject, int revision)
{
    Q_ASSERT(gadget && metaObject);

    QFile file(m_filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qCWarning(lcData) << "failed to open" << fileName(m_filePath) << "for reading:" << file.errorString();
        return false;
    }

    QDataStream stream(&file);
    int fileRevision = 0;
    stream >> fileRevision;

    if (stream.status() != QDataStream::Ok) {
        qCWarning(lcData).nospace() << "failed to read revision from " << fileName(m_filePath) << ": " << streamStatusString(stream.status());
        return false;
    }

    int lastRevision = 0;
    int propertyCount = metaObject->propertyCount();
    for (int i = 0; i < propertyCount; ++i) {
        QMetaProperty property = metaObject->property(i);
        int propertyRevision = property.revision();
        if (!property.isWritable() || fileRevision < propertyRevision)
            continue;

        if (propertyRevision < lastRevision) {
            qCCritical(lcData).noquote() << "failed to read misordered property" << qualifiedPropertyName(metaObject->className(), property.name(), propertyRevision);
            return false;
        }
        lastRevision = propertyRevision;

        QVariant value;
        value.load(stream);

        if (stream.status() != QDataStream::Ok) {
            qCCritical(lcData) << "failed to read property" << property.name() << "from" << fileName(m_filePath) << streamStatusString(stream.status());
            return false;
        }

        if (revision >= propertyRevision)
            property.writeOnGadget(gadget, value);
    }
    return true;
}

bool DataFile::saveGadget(const void *gadget, const QMetaObject *metaObject, int revision)
{
    Q_ASSERT(gadget && metaObject);

    QFile file(m_filePath);
    if (!file.open(QIODevice::WriteOnly)) {
        qCWarning(lcData) << "failed to open" << fileName(m_filePath) << "for writing:" << file.errorString();
        return false;
    }

    QDataStream stream(&file);
    stream << revision;

    if (stream.status() != QDataStream::Ok) {
        qCWarning(lcData).nospace() << "failed to write revision to " << fileName(m_filePath) << ": " << streamStatusString(stream.status());
        return false;
    }

    int lastRevision = 0;
    int propertyCount = metaObject->propertyCount();
    for (int i = 0; i < propertyCount; ++i) {
        QMetaProperty property = metaObject->property(i);
        int propertyRevision = property.revision();
        if (!property.isWritable() || revision < propertyRevision)
            continue;

        if (propertyRevision < lastRevision) {
            qCCritical(lcData).noquote() << "failed to write misordered property" << qualifiedPropertyName(metaObject->className(), property.name(), propertyRevision);
            return false;
        }
        lastRevision = propertyRevision;

        QVariant value = property.readOnGadget(gadget);
        value.save(stream);

        if (stream.status() != QDataStream::Ok) {
            qCCritical(lcData) << "failed to write property" << property.name() << "to" << fileName(m_filePath) << streamStatusString(stream.status());
            return false;
        }
    }
    return true;
}
