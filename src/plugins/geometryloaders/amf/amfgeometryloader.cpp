/****************************************************************************
**
** Copyright (C) 2020 CELLINK AB <info@cellink.com>
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

#include "amfgeometryloader.h"

#include <assimp/Importer.hpp>
#include <assimp/mesh.h>
#include <assimp/scene.h>

#include <QtCore/qiodevice.h>

static QVector3D toQVector3D(const aiVector3D& v)
{
    return QVector3D(v.x, v.y, v.z);
}

static QVector2D toQVector2D(const aiVector3D& v)
{
    return QVector2D(v.x, v.y);
}

bool AmfGeometryLoader::doLoad(QIODevice* device, const QString& subMesh)
{
    if (!device)
        return false;

    const QByteArray buffer = device->readAll();

    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFileFromMemory(buffer, buffer.size(), 0, nullptr);
    if (!scene)
        return false;

    const aiNode* node = scene->mRootNode;
    if (!subMesh.isEmpty()) {
        node = node->FindNode(subMesh.toUtf8());
        if (!node)
            return false;
    }

    uint count = node ? node->mNumMeshes : scene->mNumMeshes;

    for (uint m = 0; m < count; ++m) {
        uint idx = node ? node->mMeshes[m] : m;
        const aiMesh* mesh = scene->mMeshes[idx];

        m_points.reserve(m_points.size() + mesh->mNumVertices);
        if (mesh->mNormals)
            m_normals.reserve(m_normals.size() + mesh->mNumVertices);

        for (uint v = 0; v < mesh->mNumVertices; ++v) {
            m_points += toQVector3D(mesh->mVertices[v]);
            if (mesh->mNormals)
                m_normals += toQVector3D(mesh->mNormals[v]);
            if (mesh->mTextureCoords) { //NOLINT
                for (uint t = 0; t < AI_MAX_NUMBER_OF_TEXTURECOORDS; ++t) {
                    if (!mesh->mTextureCoords[t])
                        break;
                    m_texCoords += toQVector2D(*mesh->mTextureCoords[t]);
                }
            }
        }

        for (uint f = 0; f < mesh->mNumFaces; ++f) {
            const aiFace& face = mesh->mFaces[f];
            for (uint i = 0; i < face.mNumIndices; ++i)
                m_indices += face.mIndices[i];
        }
    }

    return true;
}
