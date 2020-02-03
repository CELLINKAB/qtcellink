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

#ifndef JSON_H
#define JSON_H

#include <QtCellink/cellink.h>
#include <QtCore/qjsonarray.h>
#include <QtCore/qjsondocument.h>
#include <QtCore/qvector.h>

namespace Json
{
    Q_CELLINK_EXPORT QJsonDocument readFile(const QString &filePath);
    Q_CELLINK_EXPORT bool writeFile(const QString &filePath, const QJsonDocument &json);

    inline const QString Ext = QStringLiteral("json");

    template <typename T>
    QJsonArray fromVector(const QVector<T> &values)
    {
        QJsonArray array;
        for (T value : values)
            array += value;
        return array;
    }

    template <typename T>
    QVector<T> toVector(const QJsonArray &array)
    {
        QVector<T> values;
        for (const QJsonValue &value : array)
            values += value.toDouble();
        return values;
    }

    template <typename T>
    QJsonArray fromTable(const QVector<QVector<T>> &values)
    {
        QJsonArray array;
        for (const QVector<T> &row : values)
            array += fromVector(row);
        return array;
    }

    template <typename T>
    QVector<QVector<T>> toTable(const QJsonArray &values)
    {
        QVector<QVector<T>> table;
        for (const QJsonValue &row : values)
            table += toVector<T>(row.toArray());
        return table;
    }
} // namespace Json

#endif // JSON_H
