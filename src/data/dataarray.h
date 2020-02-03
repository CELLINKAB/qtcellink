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
