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

#ifndef DATAARRAY_H
#define DATAARRAY_H

#include <QtCore/qbytearray.h>
#include <QtCore/qendian.h>
#include <QtCore/qjsonarray.h>
#include <QtCore/qjsonvalue.h>
#include <QtCore/qmath.h>
#include <QtCellink/data.h>

template <typename T>
class DataArray
{
    Q_STATIC_ASSERT(std::is_unsigned<T>::value);

public:
    DataArray(const QByteArray &data = QByteArray()) : m_data(data) { }

    operator QByteArray() const { return m_data; }

    inline bool isNull() const { return m_data.isNull(); }
    inline bool isEmpty() const { return m_data.size() < int(sizeof(T)); }
    inline int count() const { return m_data.count() / int(sizeof(T)); }
    inline qsizetype size() const { return m_data.size() / int(sizeof(T)); }

    T at(int index) const
    {
        Q_ASSERT(index >= 0 && index < size());
        return qToBigEndian(*(reinterpret_cast<const T *>(m_data.constData()) + index));
    }

    T value(int index) const
    {
        if (index < 0 || index >= size())
            return T();
        return at(index);
    }

    class Iterator
    {
    public:
        Iterator(const T *it): it(it) { }
        Iterator operator++() { ++it; return *this; }
        T operator*() const { return qToBigEndian(*it); }
        bool operator!=(const Iterator &other) const { return it != other.it; }
    private:
        const T *it = nullptr;
    };

    Iterator begin() const { return Iterator(reinterpret_cast<const T *>(m_data.constData())); }
    Iterator end() const { return Iterator(reinterpret_cast<const T *>(m_data.constData()) + size()); }
    Iterator cbegin() const { return Iterator(reinterpret_cast<const T *>(m_data.constData())); }
    Iterator cend() const { return Iterator(reinterpret_cast<const T *>(m_data.constData()) + size()); }

    QJsonArray toJson() const
    {
        QJsonArray array;
        for (T value : *this)
            array += value;
        return array;
    }

    static DataArray<T> fromJson(const QJsonArray &array)
    {
        QByteArray data;
        for (const QJsonValue &value : array)
            data += Data::fromNumber<T>(value.toInt());
        return data;
    }

private:
    QByteArray m_data;
};

#endif // DATAARRAY_H
