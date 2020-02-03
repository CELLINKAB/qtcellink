#ifndef APP_H
#define APP_H

#include <QtCellink/cellink.h>
#include <QtCore/qdir.h>
#include <QtCore/qstring.h>

class Q_CELLINK_EXPORT App
{
public:
    static QDir dataDir(const QString &subdir = QString());
};

#endif // APP_H
