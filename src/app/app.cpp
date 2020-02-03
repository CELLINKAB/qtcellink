#include "app.h"
#include <QtCore/qstandardpaths.h>

QDir App::dataDir(const QString &subdir)
{
    QDir dir(QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation));
    dir.mkpath(dir.filePath(subdir));
    return dir;
}
