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

#include "objectmodel.h"
#include "object.h"
#include <QtCore/qcoreapplication.h>
#include <QtCore/qcoreevent.h>
#include <QtCore/qdir.h>
#include <QtCore/qfile.h>
#include <QtCore/qfileinfo.h>
#include <QtCore/qjsondocument.h>
#include <QtCore/qjsonobject.h>
#include <QtCore/qloggingcategory.h>
#include <QtCore/qstandardpaths.h>
#include <QtCellink/json.h>
#include <algorithm>

static QString ensureMkPath(const QString &filePath)
{
    QDir dir = QFileInfo(filePath).dir();
    if (!dir.exists())
        dir.mkpath(".");
    return QDir::cleanPath(filePath);
}

static QDir dataDir()
{
    QDir dir(QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation));
    return ensureMkPath(dir.filePath("."));
}

static QString defaultModelFilePath(const QString &category)
{
    // share/<org>/<app>/<category>.json
    return dataDir().filePath(category + ".json");
}

static QString defaultObjectFilePath(const QString &modelFilePath, const QString &category, const QString &uuid)
{
    // share/<org>/<app>/<category>/<uuid>.json
    QDir dir = QFileInfo(modelFilePath).dir().filePath(category);
    return ensureMkPath(dir.filePath(uuid + ".json"));
}

ObjectModel::ObjectModel(const QString &category, QObject *parent)
    : QAbstractListModel(parent), m_category(category)
{
}

ObjectModel::ObjectModel(const QString &category, const QMetaObject *metaObject, QObject *parent)
    : QAbstractListModel(parent), m_category(category), m_metaObject(metaObject)
{
}

QString ObjectModel::category() const
{
    return m_category;
}

void ObjectModel::setCategory(const QString &category)
{
    if (m_category == category)
        return;

    reset();
    m_category = category;
    load();
    emit categoryChanged();
}

int ObjectModel::count() const
{
    return m_objects.count();
}

bool ObjectModel::isEmpty() const
{
    return m_objects.isEmpty();
}

bool ObjectModel::isModified() const
{
    return m_modified;
}

Object *ObjectModel::current() const
{
    return m_current;
}

void ObjectModel::setCurrent(Object *current)
{
    if (m_current == current)
        return;

    if (m_current && m_currentIndex == -1) {
        disconnect(m_current, &Object::destroyed, this, &ObjectModel::remove);
        disconnect(m_current, &Object::modifiedChanged, this, &ObjectModel::updateModified);
    }
    m_current = current;
    m_currentIndex = m_objects.indexOf(current);
    if (current && m_currentIndex == -1) {
        connect(current, &Object::destroyed, this, &ObjectModel::remove);
        connect(current, &Object::modifiedChanged, this, &ObjectModel::updateModified);
    }
    updateModified();
    emit currentChanged();
}

int ObjectModel::currentIndex() const
{
    return m_currentIndex;
}

void ObjectModel::setCurrentIndex(int index)
{
    if (m_currentIndex == index)
        return;

    m_currentIndex = index;
    m_current = m_objects.value(index);
    updateModified();
    emit currentChanged();
}

QList<Object *> ObjectModel::objects() const
{
    return m_objects;
}

Object *ObjectModel::get(int index) const
{
    Object *object = m_objects.value(index);
    if (object && object->isLazy())
        loadObject(object);
    return object;
}

bool ObjectModel::contains(Object *object) const
{
    return m_objects.contains(object);
}

int ObjectModel::find(const QVariant &value, int role) const
{
    return match(index(0, 0), role, value, 1, Qt::MatchExactly).value(0).row();
}

Object *ObjectModel::create(const QString &name)
{
    Object *object = doCreate(this);
    m_danglingObjects += object;
    object->resetUuid();
    if (!name.isNull())
        object->setName(name);
    object->resetModified();
    qCDebug(loggingCategory()) << "created:" << object->name() << "(" << object->uuid() << ")";
    return object;
}

void ObjectModel::append(Object *object)
{
    insert(rowCount(), object);
}

void ObjectModel::prepend(Object *object)
{
    insert(0, object);
}

void ObjectModel::insert(int index, Object *object)
{
    if (!object)
        return;

    int oldIndex = m_objects.indexOf(object);
    if (oldIndex != -1) {
        move(oldIndex, index);
    } else {
        bool wasEmpty = m_objects.isEmpty();

        beginInsertRows(QModelIndex(), index, index);
        doInsert(index, object);
        endInsertRows();

        if (wasEmpty)
            emit emptyChanged();
        emit countChanged();
        saveLater();
    }
}

void ObjectModel::move(int from, int to)
{
    if (from == to)
        return;

    beginMoveRows(QModelIndex(), from, from, QModelIndex(), from < to ? to + 1 : to);
    m_objects.move(from, to);
    endMoveRows();
    saveLater();
}

void ObjectModel::remove(Object *object)
{
    if (object == m_current)
        setCurrent(nullptr);
    m_danglingObjects.removeOne(object);

    removeAt(m_objects.indexOf(object));
}

void ObjectModel::removeAt(int index)
{
    if (index < 0 || index >= m_objects.count())
        return;

    if (m_currentIndex == index)
        setCurrentIndex(-1);

    beginRemoveRows(QModelIndex(), index, index);
    Object *object = m_objects.takeAt(index);
    cleanupObject(object);
    endRemoveRows();

    if (m_objects.isEmpty())
        emit emptyChanged();
    emit countChanged();
    saveLater();
}

void ObjectModel::sort(int role, Qt::SortOrder order)
{
    beginResetModel();
    std::sort(m_objects.begin(), m_objects.end(), [=](Object *left, Object *right) {
        return lessThan(left, right, role) == (order == Qt::AscendingOrder);
    });
    endResetModel();
}

void ObjectModel::restoreState(const QJsonArray &json)
{
    QList<QJsonObject> objects;
    for (const QJsonValue &value : json) {
        if (!value.isObject())
            continue;
        objects += value.toObject();
    }

    if (objects.isEmpty())
        return;

    beginInsertRows(QModelIndex(), 0, objects.count() - 1);
    for (const QJsonValue &value : json) {
        Object *object = doCreate(this);
        object->setMetaData(value.toObject());
        object->setLazy(true);
        doInsert(rowCount(), object);
    }
    endInsertRows();
    emit emptyChanged();
    emit countChanged();
}

QJsonArray ObjectModel::saveState() const
{
    QJsonArray json;
    for (Object *object : m_objects)
        json.append(object->metaData());
    return json;
}

QHash<int, QByteArray> ObjectModel::roleNames() const
{
    static const QHash<int, QByteArray> roles = {
        { ObjectRole, "object" },
        { NameRole, "name" },
        { UuidRole, "uuid" },
        { DateRole, "date" }
    };
    return roles;
}

int ObjectModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_objects.count();
}

QVariant ObjectModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_objects.count())
        return QVariant();

    switch (role) {
    case ObjectRole:
    if (role == ObjectRole)
         return QVariant::fromValue(get(index.row()));
    case NameRole:
        return m_objects.at(index.row())->name();
    case UuidRole:
        return m_objects.at(index.row())->uuid();
    case DateRole:
        return m_objects.at(index.row())->date();
    default:
        break;
    }

    Object *object = get(index.row());
    const QByteArray propertyName = roleNames().value(role);
    if (!object || propertyName.isEmpty())
         return QVariant();

    return object->property(propertyName);
}

QString ObjectModel::filePath() const
{
    if (!m_filePath.isEmpty())
        return m_filePath;

    return defaultModelFilePath(m_category);
}

QString ObjectModel::filePath(Object *object) const
{
    if (!object)
        return QString();

    QString fp = object->filePath();
    if (!fp.isEmpty())
        return fp;

    return defaultObjectFilePath(filePath(), m_category, object->uuid());
}

bool ObjectModel::load(const QString &filePath)
{
    if (!filePath.isNull())
        m_filePath = filePath;
    QString fp = ObjectModel::filePath();
    restoreState(Json::readFile(fp).array());
    qCDebug(loggingCategory()) << "loaded:" << count() << qPrintable(m_category) << "from" << fp;
    return true;
}

bool ObjectModel::save(const QString &filePath)
{
    if (!filePath.isNull())
        m_filePath = filePath;
    QString fp = ObjectModel::filePath();
    for (Object *object : m_objects) {
        if (!QFile::exists(ObjectModel::filePath(object)))
            saveObject(object);
    }
    qCDebug(loggingCategory()) << "saved:" << count() << qPrintable(m_category) << "to" << fp;
    m_saving = false;
    return Json::writeFile(fp, QJsonDocument(saveState()));
}

void ObjectModel::cleanup()
{
    for (Object *object : qAsConst(m_danglingObjects)) {
        if (object == m_current)
            setCurrent(nullptr);
        cleanupObject(object);
    }
    m_danglingObjects.clear();
}

void ObjectModel::clear()
{
    if (m_objects.isEmpty())
        return;

    for (Object *object : m_objects)
        cleanupObject(object);
    reset();
    saveLater();
}

void ObjectModel::reset()
{
    beginRemoveRows(QModelIndex(), 0, m_objects.count() - 1);
    m_objects.clear();
    endRemoveRows();
    updateModified();
    emit emptyChanged();
    emit countChanged();
}

void ObjectModel::flush()
{
    QCoreApplication::sendPostedEvents(this, QEvent::MetaCall);
}

Object *ObjectModel::doCreate(QObject *parent) const
{
    if (!m_metaObject)
        return new Object(parent);

    return qobject_cast<Object *>(m_metaObject->newInstance(Q_ARG(QObject *, parent)));
}

void ObjectModel::doInsert(int index, Object *object)
{
    m_objects.insert(index, object);
    if (object == m_current) {
        updateModified();
    } else {
        connect(object, &Object::destroyed, this, &ObjectModel::remove);
        connect(object, &Object::modifiedChanged, this, &ObjectModel::updateModified);
    }
    connect(object, &Object::modified, this, [=]() { saveObject(object); });
    connect(object, &Object::metaDataChanged, this, &ObjectModel::saveLater);
}

bool ObjectModel::lessThan(Object *left, Object *right, int role) const
{
    const QByteArray propertyName = roleNames().value(role);
    if (propertyName.isEmpty()) {
        qCWarning(loggingCategory()) << "unsupported sort role:" << role;
        return false;
    }

    return left->property(propertyName) < right->property(propertyName);
}

void ObjectModel::cleanupObject(Object *object) const
{
    QString fp = filePath(object);
    object->cleanup(fp);
    qCDebug(loggingCategory()) << "deleted:" << fp << "for" << object->name();
    object->deleteLater();
}

void ObjectModel::loadObject(Object *object) const
{
    QString fp = filePath(object);
    object->load(fp);
    qCDebug(loggingCategory()) << "loaded:" << object->name() << "from" << fp;
}

void ObjectModel::saveObject(Object *object) const
{
    QString fp = filePath(object);
    object->save(fp);
    qCDebug(loggingCategory()) << "saved:" << object->name() << "to" << fp;
}

void ObjectModel::saveLater()
{
    if (m_saving)
        return;

    m_saving = true;
    QMetaObject::invokeMethod(this, [=]() { save(); }, Qt::QueuedConnection);
}

void ObjectModel::updateModified()
{
    bool modified = m_current && m_current->isModified() && !contains(m_current);
    if (m_modified == modified)
        return;

    m_modified = modified;
    emit modifiedChanged();
}
