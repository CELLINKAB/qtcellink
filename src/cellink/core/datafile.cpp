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
#include <QtCore/qvariant.h>

DataFile::DataFile(const QString &filePath) : m_filePath(filePath)
{
}

QString DataFile::filePath() const
{
    return m_filePath;
}

bool DataFile::loadGadget(void *gadget, const QMetaObject *metaObject, int revision)
{
    Q_ASSERT(gadget && metaObject);

    QFile file(m_filePath);
    if (!file.open(QIODevice::ReadOnly))
        return false;

    QDataStream stream(&file);
    int fileRevision = 0;
    stream >> fileRevision;

    if (stream.status() != QDataStream::Ok)
        return false;

    int count = metaObject->propertyCount();
    for (int i = 0; i < count; ++i) {
        QMetaProperty property = metaObject->property(i);
        if (!property.isWritable() || fileRevision < property.revision())
            continue;
        QVariant value;
        value.load(stream);
        if (revision >= property.revision())
            property.writeOnGadget(gadget, value);
    }
    return stream.status() == QDataStream::Ok;
}

bool DataFile::saveGadget(const void *gadget, const QMetaObject *metaObject, int revision)
{
    Q_ASSERT(gadget && metaObject);

    QFile file(m_filePath);
    if (!file.open(QIODevice::WriteOnly))
        return false;

    QDataStream stream(&file);
    stream << revision;

    if (stream.status() != QDataStream::Ok)
        return false;

    int count = metaObject->propertyCount();
    for (int i = 0; i < count; ++i) {
        QMetaProperty property = metaObject->property(i);
        if (!property.isWritable() || revision < property.revision())
            continue;
        QVariant value = property.readOnGadget(gadget);
        value.save(stream);
    }
    return stream.status() == QDataStream::Ok;
}
