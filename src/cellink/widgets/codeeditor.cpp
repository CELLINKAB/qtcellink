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

#include "codeeditor.h"

#include <QtCore/qabstractitemmodel.h>
#include <QtGui/qfont.h>
#include <QtGui/qpainter.h>
#include <QtGui/qtextobject.h>
#include <QtWidgets/qabstractitemview.h>
#include <QtWidgets/qcompleter.h>
#include <QtWidgets/qscrollbar.h>

static const int MARGIN = 4;

static QFont monospaceFont()
{
    QFont font("Monospace");
    font.setStyleHint(QFont::Monospace);
    return font;
}

class LineNumberBar : public QWidget
{
public:
    LineNumberBar(CodeEditor *editor) : QWidget(editor), codeEditor(editor)
    {
        QFont font = monospaceFont();
        font.setPixelSize(0.7 * QFontInfo(font).pixelSize());
        setFont(font);

        connect(editor, &CodeEditor::blockCountChanged, this, &LineNumberBar::updateSize);
    }

    QSize sizeHint() const override
    {
        return size;
    }

protected:
    void paintEvent(QPaintEvent *event) override
    {
        QPainter painter(this);
        painter.setFont(font());
        codeEditor->paintLineNumbers(&painter, event->rect());
    }

private:
    void updateSize(int blockCount)
    {
        int digits = 1;
        int max = qMax(1, blockCount);
        while (max >= 10) {
            max /= 10;
            ++digits;
        }
        size.setWidth(2 * MARGIN + fontMetrics().horizontalAdvance(QLatin1Char('9')) * digits);
        updateGeometry();
    }

    QSize size;
    CodeEditor *codeEditor = nullptr;
};

CodeEditor::CodeEditor(QWidget *parent) : QPlainTextEdit(parent), m_lineNumberBar(new LineNumberBar(this))
{
    setFont(monospaceFont());

    connect(this, &CodeEditor::updateRequest, this, &CodeEditor::updateLineNumbers);
    connect(this, &CodeEditor::cursorPositionChanged, this, &CodeEditor::highlightCurrentLine);
    connect(this, &CodeEditor::blockCountChanged, this, &CodeEditor::updateViewportMargins);

    updateViewportMargins();
    highlightCurrentLine();
}

QCompleter *CodeEditor::completer() const
{
    return m_completer;
}

void CodeEditor::setCompleter(QCompleter *completer)
{
    if (m_completer)
        QObject::disconnect(m_completer, 0, this, 0);

    m_completer = completer;

    if (!m_completer)
        return;

    m_completer->setWidget(this);
    m_completer->setCompletionMode(QCompleter::PopupCompletion);
    m_completer->setCaseSensitivity(Qt::CaseInsensitive);
    QObject::connect(m_completer, QOverload<const QString &>::of(&QCompleter::activated), this, &CodeEditor::insertCompletion);
}

void CodeEditor::focusInEvent(QFocusEvent *event)
{
    if (m_completer)
        m_completer->setWidget(this);
    QPlainTextEdit::focusInEvent(event);
}

void CodeEditor::keyPressEvent(QKeyEvent *event)
{
    if (m_completer && m_completer->popup()->isVisible()) {
        // The following keys are forwarded by the completer to the widget
       switch (event->key()) {
       case Qt::Key_Enter:
       case Qt::Key_Return:
       case Qt::Key_Escape:
       case Qt::Key_Tab:
       case Qt::Key_Backtab:
            event->ignore();
            return; // let the completer do default behavior
       default:
           break;
       }
    }

    bool isShortcut = ((event->modifiers() & Qt::ControlModifier) && event->key() == Qt::Key_E); // CTRL+E
    if (!m_completer || !isShortcut) // do not process the shortcut when we have a completer
        QPlainTextEdit::keyPressEvent(event);

    const bool ctrlOrShift = event->modifiers() & (Qt::ControlModifier | Qt::ShiftModifier);
    if (!m_completer || (ctrlOrShift && event->text().isEmpty()) || event->key() == Qt::Key_Backspace || event->key() == Qt::Key_Return)
        return;

    static QString eow("~!@#$%^&*()_+{}|:\"<>?,./;'[]\\-="); // end of word
    bool hasModifier = (event->modifiers() != Qt::NoModifier) && !ctrlOrShift;
    QString completionPrefix = textUnderCursor();

    if (!isShortcut && (hasModifier || event->text().isEmpty() || eow.contains(event->text().right(1)))) {
        m_completer->popup()->hide();
        return;
    }

    complete(completionPrefix);
}

void CodeEditor::resizeEvent(QResizeEvent *event)
{
    QPlainTextEdit::resizeEvent(event);

    QRect cr = contentsRect();
    m_lineNumberBar->setGeometry(QRect(cr.left(), cr.top(), m_lineNumberBar->sizeHint().width(), cr.height()));
}

void CodeEditor::complete(const QString &prefix)
{
    if (prefix != m_completer->completionPrefix()) {
        m_completer->setCompletionPrefix(prefix);
        m_completer->popup()->setCurrentIndex(m_completer->completionModel()->index(0, 0));
    }
    QRect cr = cursorRect();
    cr.setWidth(m_completer->popup()->sizeHintForColumn(0) + m_completer->popup()->verticalScrollBar()->sizeHint().width());
    m_completer->complete(cr); // popup it up!
}

void CodeEditor::highlightCurrentLine()
{
    QList<QTextEdit::ExtraSelection> extraSelections;

    if (!isReadOnly()) {
        QTextEdit::ExtraSelection selection;

        QColor lineColor = palette().color(QPalette::Highlight);
        lineColor.setAlphaF(0.2);

        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }

    setExtraSelections(extraSelections);
}

void CodeEditor::updateViewportMargins()
{
    setViewportMargins(m_lineNumberBar->sizeHint().width(), 0, 0, 0);
}

void CodeEditor::updateLineNumbers(const QRect &rect, int dy)
{
    if (dy)
        m_lineNumberBar->scroll(0, dy);
    else
        m_lineNumberBar->update(0, rect.y(), m_lineNumberBar->width(), rect.height());

    if (rect.contains(viewport()->rect()))
        updateViewportMargins();
}

void CodeEditor::insertCompletion(const QString& completion)
{
    if (m_completer->widget() != this)
        return;
    QTextCursor tc = textCursor();
    QString prefix = m_completer->completionPrefix();
    if (!prefix.isEmpty())
        tc.setPosition(tc.position() - prefix.length(), QTextCursor::KeepAnchor);
    tc.insertText(completion);
    setTextCursor(tc);
}

QString CodeEditor::textUnderCursor() const
{
    QTextCursor tc = textCursor();
    tc.select(QTextCursor::WordUnderCursor);
    return tc.selectedText();
}

void CodeEditor::paintLineNumbers(QPainter *painter, const QRect &rect)
{
    painter->setPen(palette().color(QPalette::Dark));
    painter->fillRect(rect, palette().color(QPalette::AlternateBase));

    int currentBlock = textCursor().blockNumber();

    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    QRectF bounds = blockBoundingGeometry(block);
    int top = (int) bounds.translated(contentOffset()).top();
    int bottom = top + (int) blockBoundingRect(block).height();

    while (block.isValid() && top <= rect.bottom()) {
        if (block.isVisible() && bottom >= rect.top()) {
            QString number = QString::number(blockNumber + 1);
            QFont font = painter->font();
            font.setBold(blockNumber == currentBlock);
            painter->setFont(font);
            painter->drawText(0, top, m_lineNumberBar->width() - MARGIN, fontMetrics().height(), Qt::AlignVCenter | Qt::AlignRight, number);
        }

        block = block.next();
        top = bottom;
        bottom = top + (int) blockBoundingRect(block).height();
        ++blockNumber;
    }
}
