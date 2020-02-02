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

#include "object.h"
#include <QtCore/qfile.h>
#include <QtCore/qjsondocument.h>
#include <QtCore/quuid.h>
#include <QtCellink/json.h>

static QString generateUuid()
{
    return QUuid::createUuid().toString(QUuid::WithoutBraces);
}

Object::Object(QObject *parent) : QObject(parent)
{
}

Object::~Object()
{
    emit destroyed(this);
}

bool Object::isValid() const
{
    return m_valid;
}

void Object::setValid(bool valid)
{
    if (m_valid == valid)
        return;

    m_valid = valid;
    emit validChanged();
}

QString Object::uuid() const
{
    return m_uuid;
}

void Object::setUuid(const QString &uuid)
{
    if (m_uuid == uuid)
        return;

    m_uuid = uuid;
    emit metaDataChanged();
}

void Object::resetUuid()
{
    setUuid(generateUuid());
}

QString Object::name() const
{
    return m_name;
}

void Object::setName(const QString &name)
{
    if (m_name == name)
        return;

    m_name = name;
    emit nameChanged();
    emit metaDataChanged();
}

QDate Object::date() const
{
    return m_date;
}

void Object::setDate(const QDate &date)
{
    if (m_date == date)
        return;

    m_date = date;
    emit dateChanged();
    emit metaDataChanged();
}

void Object::modify()
{
    if (!m_initialized)
        return;

    setModified(true);
    updateValid();
    emit modified();
}

bool Object::isModified() const
{
    return m_modified;
}

void Object::setModified(bool modified)
{
    if (m_modified == modified || !m_initialized)
        return;

    m_modified = modified;
    emit modifiedChanged();
}

void Object::resetModified()
{
    setModified(false);
}

bool Object::isLazy() const
{
    return m_lazy;
}

void Object::setLazy(bool lazy)
{
    m_lazy = lazy;
}

QJsonObject Object::metaData() const
{
    QJsonObject json;
    json.insert("name", m_name);
    json.insert("uuid", m_uuid);
    if (m_date.isValid())
        json.insert("date", m_date.toString(Qt::ISODate));
    return json;
}

void Object::setMetaData(const QJsonObject &metaData)
{
    setName(metaData.value("name").toString());
    setUuid(metaData.value("uuid").toString(generateUuid()));
    if (metaData.contains("date"))
        setDate(QDate::fromString(metaData.value("date").toString(), Qt::ISODate));
}

QJsonObject Object::saveState() const
{
    return toJson();
}

void Object::restoreState(const QJsonObject &json)
{
    beginInitialize();
    initJson(json);
    endInitialize();

    resetModified();
    updateValid();
}

QString Object::filePath() const
{
    return m_filePath;
}

bool Object::load(const QString &filePath)
{
    if (!filePath.isEmpty())
        m_filePath = filePath;
    QJsonDocument json = Json::readFile(m_filePath);
    restoreState(json.object());
    setLazy(false);
    return !json.isNull();
}

bool Object::save(const QString &filePath)
{
    if (!filePath.isEmpty())
        m_filePath = filePath;
    return Json::writeFile(m_filePath, QJsonDocument(saveState()));
}

bool Object::cleanup(const QString &filePath)
{
    if (!filePath.isEmpty())
        m_filePath = filePath;

    return QFile::remove(m_filePath);
}

bool Object::isInitialized() const
{
    return m_initialized;
}

void Object::beginInitialize()
{
    m_initialized = false;
}

void Object::endInitialize()
{
    m_initialized = true;
}

QJsonObject Object::toJson() const
{
    return QJsonObject();
}

void Object::initJson(const QJsonObject &json)
{
    Q_UNUSED(json);
}

void Object::updateValid()
{
    setValid(true);
}
