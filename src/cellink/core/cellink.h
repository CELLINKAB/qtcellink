/****************************************************************************
**
** Copyright (C) 2020 CELLINK AB <info@cellink.com>
** Copyright (C) 2017 The Qt Company Ltd.
**
** This file is part of QtCellink (based on the global headers in Qt).
**
** QtCellink is free software: you can redistribute it and/or modify it
** under the terms of the GNU Lesser General Public License as published
** by the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** QtCellink is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
** GNU Lesser General Public License for more details.
**
** You should have received a copy of the GNU Lesser General Public License
** along with QtCellink. If not, see <https://www.gnu.org/licenses/>.
**
****************************************************************************/

#ifndef CELLINK_H
#define CELLINK_H

#include <QtCore/qglobal.h>

#ifndef Q_CELLINK_EXPORT
#    ifndef QT_STATIC
#        if defined(QT_BUILD_CELLINK_LIB)
#            define Q_CELLINK_EXPORT Q_DECL_EXPORT
#        else
#            define Q_CELLINK_EXPORT Q_DECL_IMPORT
#        endif
#    else
#        define Q_CELLINK_EXPORT
#    endif
#endif

#endif // CELLINK_H
