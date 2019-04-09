/****************************************************************************
**
** Copyright (C) 2019 CELLINK AB <info@cellink.com>
**
** This file is part of QtCellink.
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

#ifndef AMFGEOMETRYLOADER_H
#define AMFGEOMETRYLOADER_H

#include "basegeometryloader_p.h"

class AmfGeometryLoader : public Qt3DRender::BaseGeometryLoader
{
protected:
    bool doLoad(QIODevice *ioDev, const QString &subMesh) final;
};

#endif // AMFGEOMETRYLOADER_H
