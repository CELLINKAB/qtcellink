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

#ifndef NODEDELEGATE_H
#define NODEDELEGATE_H

#include <optional>

#include <QtCore/qabstractitemmodel.h>
#include <QtCore/qobject.h>
#include <QtCore/qrect.h>
#include <QtCore/qstring.h>
#include <QtGui/qbrush.h>
#include <QtGui/qcolor.h>
#include <QtGui/qfont.h>
#include <QtGui/qimage.h>

class QSGNode;
class NodeItem;

class NodeDelegate : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qreal padding READ padding WRITE setPadding NOTIFY paddingChanged)
    Q_PROPERTY(qreal topPadding READ topPadding WRITE setTopPadding NOTIFY topPaddingChanged)
    Q_PROPERTY(qreal leftPadding READ leftPadding WRITE setLeftPadding NOTIFY leftPaddingChanged)
    Q_PROPERTY(qreal rightPadding READ rightPadding WRITE setRightPadding NOTIFY rightPaddingChanged)
    Q_PROPERTY(
        qreal bottomPadding READ bottomPadding WRITE setBottomPadding NOTIFY bottomPaddingChanged)

public:
    explicit NodeDelegate(QObject* parent = nullptr);

    qreal padding() const;
    void setPadding(qreal padding);

    qreal topPadding() const;
    void setTopPadding(qreal topPadding);

    qreal leftPadding() const;
    void setLeftPadding(qreal leftPadding);

    qreal rightPadding() const;
    void setRightPadding(qreal rightPadding);

    qreal bottomPadding() const;
    void setBottomPadding(qreal bottomPadding);

    virtual QSGNode* createNode(NodeItem* item) = 0;
    virtual void updateNode(QSGNode* node, const QModelIndex& index, NodeItem* item) = 0;

    virtual QRectF nodeRect(const QModelIndex& index, NodeItem* item) const;

signals:
    void changed();
    void paddingChanged();
    void topPaddingChanged();
    void leftPaddingChanged();
    void rightPaddingChanged();
    void bottomPaddingChanged();

private:
    qreal m_padding = 0;
    std::optional<qreal> m_topPadding;
    std::optional<qreal> m_leftPadding;
    std::optional<qreal> m_rightPadding;
    std::optional<qreal> m_bottomPadding;
};

class AbstractImageDelegate : public NodeDelegate
{
    Q_OBJECT

public:
    explicit AbstractImageDelegate(QObject* parent = nullptr);

    QSGNode* createNode(NodeItem* item) override;
    void updateNode(QSGNode* node, const QModelIndex& index, NodeItem* item) override;

    virtual QImage nodeImage(const QModelIndex& index, NodeItem* item) const = 0;
};

class AbstractRectDelegate : public NodeDelegate
{
    Q_OBJECT

public:
    explicit AbstractRectDelegate(QObject* parent = nullptr);

    QSGNode* createNode(NodeItem* item) override;
    void updateNode(QSGNode* node, const QModelIndex& index, NodeItem* item) override;

    virtual qreal nodeRadius(const QModelIndex& index, NodeItem* item) const = 0;
    virtual QColor nodeColor(const QModelIndex& index, NodeItem* item) const = 0;
    virtual QGradientStops* nodeGradientStops(const QModelIndex& index, NodeItem* item) const = 0;
    virtual Qt::Orientation nodeGradientOrientation(const QModelIndex& index,
                                                    NodeItem* item) const = 0;
    virtual QColor nodeBorderColor(const QModelIndex& index, NodeItem* item) const = 0;
    virtual qreal nodeBorderWidth(const QModelIndex& index, NodeItem* item) const = 0;
};

class RectDelegate : public AbstractRectDelegate
{
    Q_OBJECT
    Q_PROPERTY(qreal radius READ radius WRITE setRadius NOTIFY radiusChanged)
    Q_PROPERTY(QColor color READ color WRITE setColor RESET resetColor NOTIFY colorChanged)
    Q_PROPERTY(QColor currentColor READ currentColor WRITE setCurrentColor RESET resetCurrentColor
                   NOTIFY currentColorChanged)
    Q_PROPERTY(QColor selectedColor READ selectedColor WRITE setSelectedColor RESET
                   resetSelectedColor NOTIFY selectedColorChanged)
    Q_PROPERTY(QColor disabledColor READ disabledColor WRITE setDisabledColor RESET
                   resetDisabledColor NOTIFY disabledColorChanged)
    Q_PROPERTY(qreal borderWidth READ borderWidth WRITE setBorderWidth NOTIFY borderWidthChanged)
    Q_PROPERTY(qreal currentBorderWidth READ currentBorderWidth WRITE setCurrentBorderWidth NOTIFY
                   currentBorderWidthChanged)
    Q_PROPERTY(qreal selectedBorderWidth READ selectedBorderWidth WRITE setSelectedBorderWidth
                   NOTIFY selectedBorderWidthChanged)
    Q_PROPERTY(qreal disabledBorderWidth READ disabledBorderWidth WRITE setDisabledBorderWidth
                   NOTIFY disabledBorderWidthChanged)
    Q_PROPERTY(QColor borderColor READ borderColor WRITE setBorderColor RESET resetBorderColor
                   NOTIFY borderColorChanged)
    Q_PROPERTY(QColor currentBorderColor READ currentBorderColor WRITE setCurrentBorderColor RESET
                   resetCurrentBorderColor NOTIFY currentBorderColorChanged)
    Q_PROPERTY(QColor selectedBorderColor READ selectedBorderColor WRITE setSelectedBorderColor
                   RESET resetSelectedBorderColor NOTIFY selectedBorderColorChanged)
    Q_PROPERTY(QColor disabledBorderColor READ disabledBorderColor WRITE setDisabledBorderColor
                   RESET resetDisabledBorderColor NOTIFY disabledBorderColorChanged)

public:
    explicit RectDelegate(QObject* parent = nullptr);

    qreal radius() const;
    void setRadius(qreal radius);

    QColor color() const;
    void setColor(const QColor& color);
    void resetColor();

    QColor currentColor() const;
    void setCurrentColor(const QColor& currentColor);
    void resetCurrentColor();

    QColor selectedColor() const;
    void setSelectedColor(const QColor& selectedColor);
    void resetSelectedColor();

    QColor disabledColor() const;
    void setDisabledColor(const QColor& disabledColor);
    void resetDisabledColor();

    qreal borderWidth() const;
    void setBorderWidth(qreal borderWidth);

    qreal currentBorderWidth() const;
    void setCurrentBorderWidth(qreal currentBorderWidth);

    qreal selectedBorderWidth() const;
    void setSelectedBorderWidth(qreal selectedBorderWidth);

    qreal disabledBorderWidth() const;
    void setDisabledBorderWidth(qreal disabledBorderWidth);

    QColor borderColor() const;
    void setBorderColor(const QColor& borderColor);
    void resetBorderColor();

    QColor currentBorderColor() const;
    void setCurrentBorderColor(const QColor& currentBorderColor);
    void resetCurrentBorderColor();

    QColor selectedBorderColor() const;
    void setSelectedBorderColor(const QColor& selectedBorderColor);
    void resetSelectedBorderColor();

    QColor disabledBorderColor() const;
    void setDisabledBorderColor(const QColor& disabledBorderColor);
    void resetDisabledBorderColor();

signals:
    void radiusChanged();
    void colorChanged();
    void currentColorChanged();
    void selectedColorChanged();
    void disabledColorChanged();
    void borderWidthChanged();
    void currentBorderWidthChanged();
    void selectedBorderWidthChanged();
    void disabledBorderWidthChanged();
    void borderColorChanged();
    void currentBorderColorChanged();
    void selectedBorderColorChanged();
    void disabledBorderColorChanged();

protected:
    qreal nodeRadius(const QModelIndex& index, NodeItem* item) const override;
    QColor nodeColor(const QModelIndex& index, NodeItem* item) const override;
    QGradientStops* nodeGradientStops(const QModelIndex& index, NodeItem* item) const override;
    Qt::Orientation nodeGradientOrientation(const QModelIndex& index, NodeItem* item) const override;
    QColor nodeBorderColor(const QModelIndex& index, NodeItem* item) const override;
    qreal nodeBorderWidth(const QModelIndex& index, NodeItem* item) const override;

private:
    qreal m_radius = 0;
    QColor m_color;
    QColor m_currentColor;
    QColor m_selectedColor;
    QColor m_disabledColor;
    qreal m_borderWidth = -1;
    qreal m_currentBorderWidth = -1;
    qreal m_selectedBorderWidth = -1;
    qreal m_disabledBorderWidth = -1;
    QColor m_borderColor;
    QColor m_currentBorderColor;
    QColor m_selectedBorderColor;
    QColor m_disabledBorderColor;
};

class AbstractTextDelegate : public NodeDelegate
{
    Q_OBJECT

public:
    explicit AbstractTextDelegate(QObject* parent = nullptr);

    QSGNode* createNode(NodeItem* item) override;
    void updateNode(QSGNode* node, const QModelIndex& index, NodeItem* item) override;

    virtual QString nodeText(const QModelIndex& index, NodeItem* item) const = 0;
    virtual QColor nodeColor(const QModelIndex& index, NodeItem* item) const = 0;
    virtual QFont nodeFont(const QModelIndex& index, NodeItem* item) const = 0;
    virtual Qt::Alignment nodeAlignment(const QModelIndex& index, NodeItem* item) const = 0;
};

class TextDelegate : public AbstractTextDelegate
{
    Q_OBJECT
    Q_PROPERTY(int textRole READ textRole WRITE setTextRole NOTIFY textRoleChanged)
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(QColor currentColor READ currentColor WRITE setCurrentColor NOTIFY currentColorChanged)
    Q_PROPERTY(
        QColor selectedColor READ selectedColor WRITE setSelectedColor NOTIFY selectedColorChanged)
    Q_PROPERTY(
        QColor disabledColor READ disabledColor WRITE setDisabledColor NOTIFY disabledColorChanged)
    Q_PROPERTY(QFont font READ font WRITE setFont NOTIFY fontChanged)
    Q_PROPERTY(QFont currentFont READ currentFont WRITE setCurrentFont NOTIFY currentFontChanged)
    Q_PROPERTY(QFont selectedFont READ selectedFont WRITE setSelectedFont NOTIFY selectedFontChanged)
    Q_PROPERTY(QFont disabledFont READ disabledFont WRITE setDisabledFont NOTIFY disabledFontChanged)
    Q_PROPERTY(Qt::Alignment alignment READ alignment WRITE setAlignment NOTIFY alignmentChanged)

public:
    explicit TextDelegate(QObject* parent = nullptr);

    int textRole() const;
    void setTextRole(int textRole);

    QColor color() const;
    void setColor(const QColor& color);

    QColor currentColor() const;
    void setCurrentColor(const QColor& currentColor);

    QColor selectedColor() const;
    void setSelectedColor(const QColor& selectedColor);

    QColor disabledColor() const;
    void setDisabledColor(const QColor& disabledColor);

    QFont font() const;
    void setFont(const QFont& font);

    QFont currentFont() const;
    void setCurrentFont(const QFont& currentFont);

    QFont selectedFont() const;
    void setSelectedFont(const QFont& selectedFont);

    QFont disabledFont() const;
    void setDisabledFont(const QFont& disabledFont);

    Qt::Alignment alignment() const;
    void setAlignment(Qt::Alignment alignment);

signals:
    void textRoleChanged();
    void colorChanged();
    void currentColorChanged();
    void selectedColorChanged();
    void disabledColorChanged();
    void fontChanged();
    void currentFontChanged();
    void selectedFontChanged();
    void disabledFontChanged();
    void alignmentChanged();

protected:
    QString nodeText(const QModelIndex& index, NodeItem* item) const override;
    QColor nodeColor(const QModelIndex& index, NodeItem* item) const override;
    QFont nodeFont(const QModelIndex& index, NodeItem* item) const override;
    Qt::Alignment nodeAlignment(const QModelIndex& index, NodeItem* item) const override;

private:
    int m_textRole = -1;
    QColor m_color;
    QColor m_currentColor;
    QColor m_selectedColor;
    QColor m_disabledColor;
    QFont m_font;
    std::optional<QFont> m_currentFont;
    std::optional<QFont> m_selectedFont;
    std::optional<QFont> m_disabledFont;
    Qt::Alignment m_alignment = Qt::AlignCenter;
};

class HeaderDelegate : public TextDelegate
{
    Q_OBJECT
    Q_PROPERTY(
        Qt::Orientation orientation READ orientation WRITE setOrientation NOTIFY orientationChanged)

public:
    explicit HeaderDelegate(QObject* parent = nullptr);

    Qt::Orientation orientation() const;
    void setOrientation(Qt::Orientation orientation);

signals:
    void orientationChanged();

protected:
    QString nodeText(const QModelIndex& index, NodeItem* item) const override;

private:
    Qt::Orientation m_orientation = Qt::Horizontal;
};

class AbstractOpacityDelegate : public NodeDelegate
{
    Q_OBJECT

public:
    explicit AbstractOpacityDelegate(QObject* parent = nullptr);

    QSGNode* createNode(NodeItem* item) override;
    void updateNode(QSGNode* node, const QModelIndex& index, NodeItem* item) override;

    virtual qreal nodeOpacity(const QModelIndex& index, NodeItem* item) const = 0;
};

class OpacityDelegate : public AbstractOpacityDelegate
{
    Q_OBJECT
    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity NOTIFY opacityChanged)
    Q_PROPERTY(qreal currentOpacity READ currentOpacity WRITE setCurrentOpacity NOTIFY
                   currentOpacityChanged)
    Q_PROPERTY(qreal selectedOpacity READ selectedOpacity WRITE setSelectedOpacity NOTIFY
                   selectedOpacityChanged)
    Q_PROPERTY(qreal disabledOpacity READ disabledOpacity WRITE setDisabledOpacity NOTIFY
                   disabledOpacityChanged)
    Q_PROPERTY(int opacityRole READ opacityRole WRITE setOpacityRole NOTIFY opacityRoleChanged)

public:
    explicit OpacityDelegate(QObject* parent = nullptr);

    qreal opacity() const;
    void setOpacity(qreal opacity);

    qreal currentOpacity() const;
    void setCurrentOpacity(qreal currentOpacity);

    qreal selectedOpacity() const;
    void setSelectedOpacity(qreal selectedOpacity);

    qreal disabledOpacity() const;
    void setDisabledOpacity(qreal disabledOpacity);

    int opacityRole() const;
    void setOpacityRole(int opacityRole);

signals:
    void opacityChanged();
    void currentOpacityChanged();
    void selectedOpacityChanged();
    void disabledOpacityChanged();
    void opacityRoleChanged();

protected:
    qreal nodeOpacity(const QModelIndex& index, NodeItem* item) const override;

private:
    int m_opacityRole = -1;
    qreal m_opacity = 1.0;
    qreal m_currentOpacity = -1.0;
    qreal m_selectedOpacity = -1.0;
    qreal m_disabledOpacity = -1.0;
};

class AbstractScaleDelegate : public NodeDelegate
{
    Q_OBJECT

public:
    explicit AbstractScaleDelegate(QObject* parent = nullptr);

    QSGNode* createNode(NodeItem* item) override;
    void updateNode(QSGNode* node, const QModelIndex& index, NodeItem* item) override;

    virtual qreal nodeScale(const QModelIndex& index, NodeItem* item) const = 0;
};

class ScaleDelegate : public AbstractScaleDelegate
{
    Q_OBJECT
    Q_PROPERTY(qreal scale READ scale WRITE setScale NOTIFY scaleChanged)
    Q_PROPERTY(qreal currentScale READ currentScale WRITE setCurrentScale NOTIFY currentScaleChanged)
    Q_PROPERTY(
        qreal selectedScale READ selectedScale WRITE setSelectedScale NOTIFY selectedScaleChanged)
    Q_PROPERTY(
        qreal disabledScale READ disabledScale WRITE setDisabledScale NOTIFY disabledScaleChanged)
    Q_PROPERTY(int scaleRole READ scaleRole WRITE setScaleRole NOTIFY scaleRoleChanged)

public:
    explicit ScaleDelegate(QObject* parent = nullptr);

    qreal scale() const;
    void setScale(qreal scale);

    qreal currentScale() const;
    void setCurrentScale(qreal currentScale);

    qreal selectedScale() const;
    void setSelectedScale(qreal selectedScale);

    qreal disabledScale() const;
    void setDisabledScale(qreal disabledScale);

    int scaleRole() const;
    void setScaleRole(int scaleRole);

signals:
    void scaleChanged();
    void currentScaleChanged();
    void selectedScaleChanged();
    void disabledScaleChanged();
    void scaleRoleChanged();

protected:
    qreal nodeScale(const QModelIndex& index, NodeItem* item) const override;

private:
    int m_scaleRole = -1;
    qreal m_scale = 1.0;
    qreal m_currentScale = -1.0;
    qreal m_selectedScale = -1.0;
    qreal m_disabledScale = -1.0;
};

class ProgressDelegate : public RectDelegate
{
    Q_OBJECT
    Q_PROPERTY(int colorRole READ colorRole WRITE setColorRole NOTIFY colorRoleChanged)
    Q_PROPERTY(int progressRole READ progressRole WRITE setProgressRole NOTIFY progressRoleChanged)
    Q_PROPERTY(
        Qt::Orientation orientation READ orientation WRITE setOrientation NOTIFY orientationChanged)
    Q_PROPERTY(Qt::LayoutDirection layoutDirection READ layoutDirection WRITE setLayoutDirection
                   NOTIFY layoutDirectionChanged)

public:
    explicit ProgressDelegate(QObject* parent = nullptr);

    int colorRole() const;
    void setColorRole(int colorRole);

    int progressRole() const;
    void setProgressRole(int progressRole);

    Qt::Orientation orientation() const;
    void setOrientation(Qt::Orientation orientation);

    Qt::LayoutDirection layoutDirection() const;
    void setLayoutDirection(Qt::LayoutDirection layoutDirection);

signals:
    void colorRoleChanged();
    void progressRoleChanged();
    void orientationChanged();
    void layoutDirectionChanged();

protected:
    QColor progressColor(const QModelIndex& index, NodeItem* item) const;
    QGradientStops* nodeGradientStops(const QModelIndex& index, NodeItem* item) const override;
    Qt::Orientation nodeGradientOrientation(const QModelIndex& index, NodeItem* item) const override;

private:
    int m_colorRole = -1;
    int m_progressRole = -1;
    Qt::Orientation m_orientation = Qt::Horizontal;
    Qt::LayoutDirection m_layoutDirection = Qt::LeftToRight;
};

#endif // NODEDELEGATE_H
