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

#ifndef DATA_H
#define DATA_H

#include <QtCore/qbytearray.h>
#include <QtCore/qendian.h>
#include <QtCore/qvector.h>

namespace Data
{
template <typename T>
T toNumber(const QByteArray &data)
{
    return qFromBigEndian<T>(data.constData());
}

template <typename T>
QByteArray fromNumber(T num, int size = sizeof(T))
{
    QByteArray data(size, 0x0);
    qToBigEndian<T>(num, data.data() + size - sizeof(T));
    return data;
}

template <typename T>
QVector<T> toVector(const QByteArray &data)
{
    int count = data.size() / sizeof(T);
    QVector<T> vector;
    vector.reserve(count);
    const char *rawData = data.constData();
    for (int i = 0; i < count; ++i)
        vector += qFromBigEndian<T>(rawData + i * sizeof(T));
    return vector;
}

template <typename T>
QByteArray fromVector(const QVector<T> &vector)
{
    int count = vector.count();
    QByteArray data;
    data.resize(count * sizeof(T));
    char *rawData = data.data();
    for (int i = 0; i < count; ++i)
        qToBigEndian<T>(vector.at(i), rawData + i * sizeof(T));
    return data;
}

inline bool toBool(const QByteArray &data)
{
    bool ok = false;
    int number = data.toInt(&ok);
    if (ok)
        return number;

    return qstricmp(data, "true") == 0 || qstricmp(data, "on") == 0 || qstricmp(data, "yes") == 0;
}
} // namespace Data

#endif // DATA_H
