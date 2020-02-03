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
