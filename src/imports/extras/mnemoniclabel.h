/****************************************************************************
**
** Copyright (C) 2020 CELLINK AB <info@cellink.com>
** Copyright (C) 2017 The Qt Company Ltd.
**
** This file is part of QtCellink (based on the Qt Quick Controls 2 module of Qt).
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

#ifndef MNEMONICLABEL_H
#define MNEMONICLABEL_H

#include <QtQuick/private/qquicktext_p.h>

class MnemonicLabel : public QQuickText
{
    Q_OBJECT
    Q_PROPERTY(QString text READ text WRITE setText FINAL)
    Q_PROPERTY(bool mnemonicVisible READ isMnemonicVisible WRITE setMnemonicVisible FINAL)

public:
    explicit MnemonicLabel(QQuickItem* parent = nullptr);

    QString text() const;
    void setText(const QString& text);

    bool isMnemonicVisible() const;
    void setMnemonicVisible(bool visible);

private:
    void updateMnemonic();

    bool m_mnemonicVisible = true;
    QString m_fullText;
};

QML_DECLARE_TYPE(MnemonicLabel)

#endif // MNEMONICLABEL_H
