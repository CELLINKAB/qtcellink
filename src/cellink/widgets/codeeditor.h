/****************************************************************************
**
** Copyright (C) 2020 CELLINK AB <info@cellink.com>
** Copyright (C) 2016 The Qt Company Ltd.
**
** This file is based on the examples of the Qt Toolkit.
**
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
****************************************************************************/

#ifndef CODEEDITOR_H
#define CODEEDITOR_H

#include <QtWidgets/qplaintextedit.h>
#include "qtcellink/src/cellink/core/cellink.h"

QT_FORWARD_DECLARE_CLASS(QCompleter)

class Q_CELLINK_EXPORT CodeEditor : public QPlainTextEdit
{
    Q_OBJECT
    Q_PROPERTY(qreal highlightLineColorAlpha READ highlightLineColorAlpha WRITE setHighlightLineColorAlpha NOTIFY highlightLineColorAlphaChanged)

public:
    explicit CodeEditor(QWidget *parent = nullptr);

    QCompleter *completer() const;
    void setCompleter(QCompleter *completer);

    qreal highlightLineColorAlpha() const
    {
        return m_highlightLineColorAlpha;
    }

    void setHighlightLineColorAlpha(qreal alpha);

protected:
    void focusInEvent(QFocusEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

    virtual void complete(const QString &prefix);

signals:
    void highlightLineColorAlphaChanged(qreal alpha);

private slots:
    void highlightCurrentLine();
    void updateViewportMargins();
    void updateLineNumbers(const QRect &rect, int dy);
    void insertCompletion(const QString &completion);

private:
    QString textUnderCursor() const;
    void paintLineNumbers(QPainter *painter, const QRect &rect);

    friend class LineNumberBar;
    QWidget *m_lineNumberBar = nullptr;
    QCompleter *m_completer = nullptr;
    qreal m_highlightLineColorAlpha = 0.2;
};

#endif // CODEEDITOR_H
