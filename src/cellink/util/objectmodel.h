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

#ifndef OBJECTMODEL_H
#define OBJECTMODEL_H

#include <QtCellink/cellink.h>
#include <QtCore/qabstractitemmodel.h>
#include <QtCore/qjsonarray.h>

class Object;

class Q_CELLINK_EXPORT ObjectModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QString category READ category WRITE setCategory NOTIFY categoryChanged)
    Q_PROPERTY(int count READ count NOTIFY countChanged)
    Q_PROPERTY(bool empty READ isEmpty NOTIFY emptyChanged)
    Q_PROPERTY(bool modified READ isModified NOTIFY modifiedChanged)
    Q_PROPERTY(Object *current READ current WRITE setCurrent NOTIFY currentChanged)
    Q_PROPERTY(int currentIndex READ currentIndex WRITE setCurrentIndex NOTIFY currentChanged)

public:
    explicit ObjectModel(const QString &category, QObject *parent = nullptr);
    explicit ObjectModel(const QString &category, const QMetaObject *metaObject, QObject *parent = nullptr);

    QString category() const;
    void setCategory(const QString &category);

    int count() const;
    bool isEmpty() const;
    bool isModified() const;

    Object *current() const;
    void setCurrent(Object *current);
    int currentIndex() const;
    void setCurrentIndex(int index);

    Q_INVOKABLE QList<Object *> objects() const;
    Q_INVOKABLE Object *get(int index) const;
    Q_INVOKABLE bool contains(Object *object) const;
    Q_INVOKABLE int find(const QVariant &value, int role = UuidRole) const;

    Q_INVOKABLE Object *create(const QString &name = QString());
    Q_INVOKABLE void append(Object *object);
    Q_INVOKABLE void prepend(Object *object);
    Q_INVOKABLE void insert(int index, Object *object);
    Q_INVOKABLE void move(int from, int to);
    Q_INVOKABLE void remove(Object *object);
    Q_INVOKABLE void removeAt(int index);

    Q_INVOKABLE void sort(int role, Qt::SortOrder order = Qt::AscendingOrder) override;

    Q_INVOKABLE void restoreState(const QJsonArray &json);
    Q_INVOKABLE QJsonArray saveState() const;

    enum DataRole { ObjectRole, NameRole, UuidRole, DateRole, ObjectRoleCount };
    Q_ENUM(DataRole)

    QHash<int, QByteArray> roleNames() const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = ObjectRole) const override;

    QString filePath() const;
    QString filePath(Object *object) const;

public slots:
    virtual bool load(const QString &filePath = QString());
    virtual bool save(const QString &filePath = QString());
    void cleanup();
    void clear();
    void reset();
    void flush();

signals:
    void categoryChanged();
    void countChanged();
    void emptyChanged();
    void modifiedChanged();
    void currentChanged();

protected:
    virtual Object *doCreate(QObject *parent) const;
    virtual void doInsert(int index, Object *object);
    virtual bool lessThan(Object *left, Object *right, int role) const;
    virtual const QLoggingCategory &loggingCategory() const = 0;

protected slots:
    void cleanupObject(Object *object) const;
    void loadObject(Object *object) const;
    void saveObject(Object *object) const;
    void saveLater();
    void updateModified();

private:
    bool m_saving = false;
    bool m_modified = false;
    int m_currentIndex = -1;
    QString m_category;
    QString m_filePath;
    Object *m_current = nullptr;
    QList<Object *> m_objects;
    QList<Object *> m_danglingObjects;
    const QMetaObject *m_metaObject = nullptr;
};

#endif // OBJECTMODEL_H
