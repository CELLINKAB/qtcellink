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

#ifndef QTEST_JSON_H
#define QTEST_JSON_H

#include <QtTest/qtest.h>
#include <QtCore/qjsonarray.h>
#include <QtCore/qjsondocument.h>
#include <QtCore/qjsonobject.h>
#include <QtCore/qjsonvalue.h>

namespace QTest
{
    inline bool qCompare(QJsonValue const &t1, QJsonValue const &t2, const char *actual, const char *expected, const char *file, int line);
    inline bool qCompare(QJsonArray const &t1, QJsonArray const &t2, const char *actual, const char *expected, const char *file, int line);
    inline bool qCompare(QJsonObject const &t1, QJsonObject const &t2, const char *actual, const char *expected, const char *file, int line);
    inline bool qCompare(QJsonDocument const &t1, QJsonDocument const &t2, const char *actual, const char *expected, const char *file, int line);

    namespace Internal {
        inline QByteArray formatIndex(const QByteArray &path, int index)
        {
            return path + "[" + QByteArray::number(index) + "]";
        }

        inline QByteArray formatKey(const QByteArray &path, const QString &key)
        {
            return path + "['" + key.toLocal8Bit() + "']";
        }
    }

    inline bool qCompare(QJsonValue const &t1, QJsonValue const &t2, const char *actual, const char *expected, const char *file, int line)
    {
        if (t1.isArray() && t2.isArray())
            return qCompare(t1.toArray(), t2.toArray(), actual, expected, file, line);
        if (t1.isObject() && t2.isObject())
            return qCompare(t1.toObject(), t2.toObject(), actual, expected, file, line);
        return qCompare(t1.toVariant(), t2.toVariant(), actual, expected, file, line);
    }

    inline bool qCompare(QJsonArray const &t1, QJsonArray const &t2, const char *actual, const char *expected, const char *file, int line)
    {
        if (t1 != t2) {
            const int count = std::max(t1.count(), t2.count());
            for (int i = 0; i < count; ++i) {
                if (!qCompare(t1.at(i), t2.at(i), Internal::formatIndex(actual, i),
                                                  Internal::formatIndex(expected, i), file, line))
                    return false;
            }
        }
        return true;
    }

    inline bool qCompare(QJsonObject const &t1, QJsonObject const &t2, const char *actual, const char *expected, const char *file, int line)
    {
        if (t1 != t2) {
            for (auto it = t1.constBegin(); it != t1.constEnd(); ++it) {
                if (!qCompare(it.value(), t2.value(it.key()), Internal::formatKey(actual, it.key()),
                                                              Internal::formatKey(expected, it.key()), file, line))
                    return false;
            }
            for (auto it = t2.constBegin(); it != t2.constEnd(); ++it) {
                if (!qCompare(it.value(), t1.value(it.key()), Internal::formatKey(actual, it.key()),
                                                              Internal::formatKey(expected, it.key()), file, line))
                    return false;
            }
        }
        return true;
    }

    inline char *toString(QJsonDocument const &doc)
    {
        return toString(doc.isNull() ? "null" : doc.isEmpty() ? "empty" : doc.isArray() ? "array" : doc.isObject() ? "object" : "invalid");
    }

    inline bool qCompare(QJsonDocument const &t1, QJsonDocument const &t2, const char *actual, const char *expected, const char *file, int line)
    {
        if (t1.isNull() != t2.isNull() || t1.isEmpty() != t2.isEmpty() || t1.isArray() != t2.isArray() || t1.isObject() != t2.isObject()) {
            char msg[1024];
            msg[0] = '\0';
            char *val1 = toString(t1);
            char *val2 = toString(t2);
            qsnprintf(msg, sizeof(msg), "Compared documents are different.\n"
                      "   Actual   (%s): %s\n"
                      "   Expected (%s): %s", actual, val1 ? val1 : "<null>",
                                              expected, val2 ? val2 : "<null>");
            delete [] val1;
            delete [] val2;
            return compare_helper(false, msg, nullptr, nullptr, actual, expected, file, line);
        }
        if (t1.isArray())
            return qCompare(t1.array(), t2.array(), actual, expected, file, line);
        if (t1.isObject())
            return qCompare(t1.object(), t2.object(), actual, expected, file, line);
        return true;
    }
}

#endif // QTEST_JSON_H
