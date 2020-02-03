#ifndef CSV_H
#define CSV_H

#include <QtCore/qfile.h>
#include <QtCore/qregularexpression.h>
#include <QtCore/qstring.h>
#include <QtCore/qtextstream.h>
#include <QtCore/qvariant.h>
#include <QtCore/qvector.h>

namespace Csv
{
    template <typename T>
    static QVector<QVector<T>> readFile(const QString &filePath)
    {
        QVector<QVector<T>> csv;

        QFile file(filePath);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return csv;

        QString line;
        QTextStream stream(&file);
        while (stream.readLineInto(&line)) {
            QVector<T> v;
            const QStringList parts = line.split(QRegularExpression(QStringLiteral("[,;:\\s]")), QString::SkipEmptyParts);
            for (const QString &p : parts)
                v += QVariant(p).value<T>();
            csv += v;
        }

        return csv;
    }
} // namespace Csv

#endif // CSV_H
