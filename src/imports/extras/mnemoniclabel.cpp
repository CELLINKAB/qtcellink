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

#include "mnemoniclabel.h"

#include <QtQuick/private/qquicktext_p_p.h>

MnemonicLabel::MnemonicLabel(QQuickItem* parent)
    : QQuickText(parent)
{}

QString MnemonicLabel::text() const
{
    return m_fullText;
}

void MnemonicLabel::setText(const QString& text)
{
    if (m_fullText == text)
        return;

    m_fullText = text;
    updateMnemonic();
}

bool MnemonicLabel::isMnemonicVisible() const
{
    return m_mnemonicVisible;
}

void MnemonicLabel::setMnemonicVisible(bool visible)
{
    if (m_mnemonicVisible == visible)
        return;

    m_mnemonicVisible = visible;
    updateMnemonic();

    if (isComponentComplete())
        forceLayout();
}

static QTextLayout::FormatRange underlineRange(int start, int length = 1)
{
    QTextLayout::FormatRange range;
    range.start = start;
    range.length = length;
    range.format.setFontUnderline(true);
    return range;
}

// based on QPlatformTheme::removeMnemonics()
void MnemonicLabel::updateMnemonic()
{
    QString text(m_fullText.size(), 0);
    int idx = 0;
    int pos = 0;
    int len = m_fullText.length();
    QVector<QTextLayout::FormatRange> formats;
    while (len) {
        if (m_fullText.at(pos) == QLatin1Char('&')
            && (len == 1 || m_fullText.at(pos + 1) != QLatin1Char('&'))) {
            if (m_mnemonicVisible && (pos == 0 || m_fullText.at(pos - 1) != QLatin1Char('&')))
                formats += underlineRange(pos);
            ++pos;
            --len;
            if (len == 0)
                break;
        } else if (m_fullText.at(pos) == QLatin1Char('(') && len >= 4
                   && m_fullText.at(pos + 1) == QLatin1Char('&')
                   && m_fullText.at(pos + 2) != QLatin1Char('&')
                   && m_fullText.at(pos + 3) == QLatin1Char(')')) {
            // a mnemonic with format "\s*(&X)"
            if (m_mnemonicVisible) {
                formats += underlineRange(pos + 1);
            } else {
                int n = 0;
                while (idx > n && text.at(idx - n - 1).isSpace())
                    ++n;
                idx -= n;
                pos += 4;
                len -= 4;
                continue;
            }
        }
        text[idx] = m_fullText.at(pos);
        ++pos;
        ++idx;
        --len;
    }
    text.truncate(idx);

    QQuickTextPrivate::get(this)->layout.setFormats(formats);
    QQuickText::setText(text);
}
