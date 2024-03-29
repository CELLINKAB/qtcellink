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

#include "nodedelegate.h"

#include <QtCore/qcache.h>
#include <QtGui/qtextlayout.h>
#include <QtQuick/private/qquickitem_p.h>
#include <QtQuick/private/qquicktextnode_p.h>
#include <QtQuick/private/qsgadaptationlayer_p.h>
#include <QtQuick/qquickwindow.h>
#include <QtQuick/qsgimagenode.h>

#include "nodeitem.h"

NodeDelegate::NodeDelegate(QObject* parent)
    : QObject(parent)
{}

qreal NodeDelegate::padding() const
{
    return m_padding;
}

void NodeDelegate::setPadding(qreal padding)
{
    if (qFuzzyCompare(m_padding, padding))
        return;

    m_padding = padding;
    emit paddingChanged();
    emit changed();
}

qreal NodeDelegate::topPadding() const
{
    return m_topPadding.value_or(m_padding);
}

void NodeDelegate::setTopPadding(qreal topPadding)
{
    if (qFuzzyCompare(m_topPadding.value_or(m_padding), topPadding))
        return;

    m_padding = topPadding;
    emit topPaddingChanged();
    emit changed();
}

qreal NodeDelegate::leftPadding() const
{
    return m_leftPadding.value_or(m_padding);
}

void NodeDelegate::setLeftPadding(qreal leftPadding)
{
    if (qFuzzyCompare(m_leftPadding.value_or(m_padding), leftPadding))
        return;

    m_padding = leftPadding;
    emit leftPaddingChanged();
    emit changed();
}

qreal NodeDelegate::rightPadding() const
{
    return m_rightPadding.value_or(m_padding);
}

void NodeDelegate::setRightPadding(qreal rightPadding)
{
    if (qFuzzyCompare(m_rightPadding.value_or(m_padding), rightPadding))
        return;

    m_padding = rightPadding;
    emit rightPaddingChanged();
    emit changed();
}

qreal NodeDelegate::bottomPadding() const
{
    return m_bottomPadding.value_or(m_padding);
}

void NodeDelegate::setBottomPadding(qreal bottomPadding)
{
    if (qFuzzyCompare(m_bottomPadding.value_or(m_padding), bottomPadding))
        return;

    m_padding = bottomPadding;
    emit bottomPaddingChanged();
    emit changed();
}

QRectF NodeDelegate::nodeRect(const QModelIndex& index, NodeItem* item) const
{
    const qreal scale = item->nodeScale();
    const QRectF rect(QPointF(0, 0), item->nodeRect(index.row(), index.column()).size());
    return rect.adjusted(scale * leftPadding(),
                         scale * topPadding(),
                         scale * -rightPadding(),
                         scale * -bottomPadding());
}

AbstractImageDelegate::AbstractImageDelegate(QObject* parent)
    : NodeDelegate(parent)
{}

QSGNode* AbstractImageDelegate::createNode(NodeItem* item)
{
    QSGImageNode* imageNode = item->window()->createImageNode();
    imageNode->setOwnsTexture(true);
    return imageNode;
}

void AbstractImageDelegate::updateNode(QSGNode* node, const QModelIndex& index, NodeItem* item)
{
    QSGImageNode* imageNode = static_cast<QSGImageNode*>(node);
    QImage image = nodeImage(index, item);
    QSGTexture* texture = item->window()->createTextureFromImage(image);
    imageNode->setTexture(texture);
}

AbstractRectDelegate::AbstractRectDelegate(QObject* parent)
    : NodeDelegate(parent)
{}

QSGNode* AbstractRectDelegate::createNode(NodeItem* item)
{
    QQuickItemPrivate* d = QQuickItemPrivate::get(item);
    QSGInternalRectangleNode* rectNode = d->sceneGraphContext()->createInternalRectangleNode();
    rectNode->setAntialiasing(true);
    return rectNode;
}

void AbstractRectDelegate::updateNode(QSGNode* node, const QModelIndex& index, NodeItem* item)
{
    QSGInternalRectangleNode* rectNode = static_cast<QSGInternalRectangleNode*>(node);
    rectNode->setRect(nodeRect(index, item));
    rectNode->setRadius(nodeRadius(index, item));
    if (QGradientStops* stops = nodeGradientStops(index, item)) {
        rectNode->setGradientStops(*stops);
        rectNode->setGradientVertical(nodeGradientOrientation(index, item) == Qt::Vertical);
    } else {
        rectNode->setGradientStops(QGradientStops());
        rectNode->setColor(nodeColor(index, item));
    }
    rectNode->setPenColor(nodeBorderColor(index, item));
    rectNode->setPenWidth(nodeBorderWidth(index, item));
    rectNode->update();
}

RectDelegate::RectDelegate(QObject* parent)
    : AbstractRectDelegate(parent)
{}

qreal RectDelegate::radius() const
{
    return m_radius;
}

void RectDelegate::setRadius(qreal radius)
{
    if (qFuzzyCompare(m_radius, radius))
        return;

    m_radius = radius;
    emit radiusChanged();
    emit changed();
}

QColor RectDelegate::color() const
{
    return m_color;
}

void RectDelegate::setColor(const QColor& color)
{
    if (m_color == color)
        return;

    m_color = color;
    emit colorChanged();
    emit changed();
}

void RectDelegate::resetColor()
{
    setColor(QColor());
}

QColor RectDelegate::currentColor() const
{
    return m_currentColor;
}

void RectDelegate::setCurrentColor(const QColor& currentColor)
{
    if (m_currentColor == currentColor)
        return;

    m_currentColor = currentColor;
    emit currentColorChanged();
    emit changed();
}

void RectDelegate::resetCurrentColor()
{
    setCurrentColor(QColor());
}

QColor RectDelegate::selectedColor() const
{
    return m_selectedColor;
}

void RectDelegate::setSelectedColor(const QColor& selectedColor)
{
    if (m_selectedColor == selectedColor)
        return;

    m_selectedColor = selectedColor;
    emit selectedColorChanged();
    emit changed();
}

void RectDelegate::resetSelectedColor()
{
    setSelectedColor(QColor());
}

QColor RectDelegate::disabledColor() const
{
    return m_disabledColor;
}

void RectDelegate::setDisabledColor(const QColor& disabledColor)
{
    if (m_disabledColor == disabledColor)
        return;

    m_disabledColor = disabledColor;
    emit disabledColorChanged();
    emit changed();
}

void RectDelegate::resetDisabledColor()
{
    setDisabledColor(QColor());
}

qreal RectDelegate::borderWidth() const
{
    return m_borderWidth;
}

void RectDelegate::setBorderWidth(qreal borderWidth)
{
    if (qFuzzyCompare(m_borderWidth, borderWidth))
        return;

    m_borderWidth = borderWidth;
    emit borderWidthChanged();
    emit changed();
}

qreal RectDelegate::currentBorderWidth() const
{
    return m_currentBorderWidth;
}

void RectDelegate::setCurrentBorderWidth(qreal currentBorderWidth)
{
    if (qFuzzyCompare(m_currentBorderWidth, currentBorderWidth))
        return;

    m_currentBorderWidth = currentBorderWidth;
    emit currentBorderWidthChanged();
    emit changed();
}

qreal RectDelegate::selectedBorderWidth() const
{
    return m_selectedBorderWidth;
}

void RectDelegate::setSelectedBorderWidth(qreal selectedBorderWidth)
{
    if (qFuzzyCompare(m_selectedBorderWidth, selectedBorderWidth))
        return;

    m_selectedBorderWidth = selectedBorderWidth;
    emit selectedBorderWidthChanged();
    emit changed();
}

qreal RectDelegate::disabledBorderWidth() const
{
    return m_disabledBorderWidth;
}

void RectDelegate::setDisabledBorderWidth(qreal disabledBorderWidth)
{
    if (qFuzzyCompare(m_disabledBorderWidth, disabledBorderWidth))
        return;

    m_disabledBorderWidth = disabledBorderWidth;
    emit disabledBorderWidthChanged();
    emit changed();
}

QColor RectDelegate::borderColor() const
{
    return m_borderColor;
}

void RectDelegate::setBorderColor(const QColor& borderColor)
{
    if (m_borderColor == borderColor)
        return;

    m_borderColor = borderColor;
    emit borderColorChanged();
    emit changed();
}

void RectDelegate::resetBorderColor()
{
    setBorderColor(QColor());
}

QColor RectDelegate::currentBorderColor() const
{
    return m_currentBorderColor;
}

void RectDelegate::setCurrentBorderColor(const QColor& currentBorderColor)
{
    if (m_currentBorderColor == currentBorderColor)
        return;

    m_currentBorderColor = currentBorderColor;
    emit currentBorderColorChanged();
    emit changed();
}

void RectDelegate::resetCurrentBorderColor()
{
    setCurrentBorderColor(QColor());
}

QColor RectDelegate::selectedBorderColor() const
{
    return m_selectedBorderColor;
}

QColor RectDelegate::disabledBorderColor() const
{
    return m_disabledBorderColor;
}

void RectDelegate::setDisabledBorderColor(const QColor& disabledBorderColor)
{
    if (m_disabledBorderColor == disabledBorderColor)
        return;

    m_disabledBorderColor = disabledBorderColor;
    emit disabledBorderColorChanged();
    emit changed();
}

void RectDelegate::resetDisabledBorderColor()
{
    setDisabledBorderColor(QColor());
}

void RectDelegate::setSelectedBorderColor(const QColor& selectedBorderColor)
{
    if (m_selectedBorderColor == selectedBorderColor)
        return;

    m_selectedBorderColor = selectedBorderColor;
    emit selectedBorderColorChanged();
    emit changed();
}

void RectDelegate::resetSelectedBorderColor()
{
    setSelectedBorderColor(QColor());
}

qreal RectDelegate::nodeRadius(const QModelIndex& index, NodeItem* item) const
{
    Q_UNUSED(index)
    qreal radius = m_radius * item->nodeScale();
    if (radius <= 1.0)
        return 0.0;
    return radius;
}

QColor RectDelegate::nodeColor(const QModelIndex& index, NodeItem* item) const
{
    if (m_disabledColor.isValid() && !item->isEnabled(index))
        return m_disabledColor;
    if (m_selectedColor.isValid() && item->isSelected(index))
        return m_selectedColor;
    if (m_currentColor.isValid() && item->isCurrent(index))
        return m_currentColor;
    if (m_color.isValid())
        return m_color;
    return Qt::transparent;
}

QGradientStops* RectDelegate::nodeGradientStops(const QModelIndex&, NodeItem*) const
{
    return nullptr;
}

Qt::Orientation RectDelegate::nodeGradientOrientation(const QModelIndex&, NodeItem*) const
{
    return Qt::Vertical;
}

QColor RectDelegate::nodeBorderColor(const QModelIndex& index, NodeItem* item) const
{
    if (m_disabledBorderColor.isValid() && !item->isEnabled(index))
        return m_disabledBorderColor;
    if (m_selectedBorderColor.isValid() && item->isSelected(index))
        return m_selectedBorderColor;
    if (m_currentBorderColor.isValid() && item->isCurrent(index))
        return m_currentBorderColor;
    if (m_borderColor.isValid())
        return m_borderColor;
    return Qt::transparent;
}

qreal RectDelegate::nodeBorderWidth(const QModelIndex& index, NodeItem* item) const
{
    qreal borderWidth = 0;
    if (m_disabledBorderWidth >= 0 && !item->isEnabled(index))
        borderWidth = m_disabledBorderWidth;
    else if (m_selectedBorderWidth >= 0 && item->isSelected(index))
        borderWidth = m_selectedBorderWidth;
    else if (m_currentBorderWidth >= 0 && item->isCurrent(index))
        borderWidth = m_currentBorderWidth;
    else if (m_borderWidth >= 0)
        borderWidth = m_borderWidth;
    return borderWidth * item->nodeScale();
}

AbstractTextDelegate::AbstractTextDelegate(QObject* parent)
    : NodeDelegate(parent)
{}

QSGNode* AbstractTextDelegate::createNode(NodeItem* item)
{
    return new QQuickTextNode(item);
}

static qreal alignedY(qreal geometryHeight, qreal lineHeight, Qt::Alignment alignment)
{
    if (alignment & Qt::AlignVCenter)
        return (geometryHeight - lineHeight) / 2;
    if (alignment & Qt::AlignBottom)
        return geometryHeight - lineHeight;
    return 0;
}

void AbstractTextDelegate::updateNode(QSGNode* node, const QModelIndex& index, NodeItem* item)
{
    QQuickTextNode* textNode = static_cast<QQuickTextNode*>(node);
    textNode->deleteContent();

    QRectF rect = nodeRect(index, item);
    QTextLayout layout(nodeText(index, item), nodeFont(index, item));
    Qt::Alignment alignment = nodeAlignment(index, item);
    layout.setTextOption(QTextOption(alignment));
    layout.beginLayout();
    QTextLine line = layout.createLine();
    line.setLineWidth(rect.width());
    line.setPosition(QPointF(0, alignedY(rect.height(), line.height(), alignment)));
    textNode->addTextLayout(rect.topLeft(), &layout, nodeColor(index, item));
}

TextDelegate::TextDelegate(QObject* parent)
    : AbstractTextDelegate(parent)
{}

int TextDelegate::textRole() const
{
    return m_textRole;
}

void TextDelegate::setTextRole(int textRole)
{
    if (m_textRole == textRole)
        return;

    m_textRole = textRole;
    emit textRoleChanged();
    emit changed();
}

QColor TextDelegate::color() const
{
    return m_color;
}

void TextDelegate::setColor(const QColor& color)
{
    if (m_color == color)
        return;

    m_color = color;
    emit colorChanged();
    emit changed();
}

QColor TextDelegate::currentColor() const
{
    return m_currentColor;
}

void TextDelegate::setCurrentColor(const QColor& currentColor)
{
    if (m_currentColor == currentColor)
        return;

    m_currentColor = currentColor;
    emit currentColorChanged();
    emit changed();
}

QColor TextDelegate::selectedColor() const
{
    return m_selectedColor;
}

void TextDelegate::setSelectedColor(const QColor& selectedColor)
{
    if (m_selectedColor == selectedColor)
        return;

    m_selectedColor = selectedColor;
    emit selectedColorChanged();
    emit changed();
}

QColor TextDelegate::disabledColor() const
{
    return m_disabledColor;
}

void TextDelegate::setDisabledColor(const QColor& disabledColor)
{
    if (m_disabledColor == disabledColor)
        return;

    m_disabledColor = disabledColor;
    emit disabledColorChanged();
    emit changed();
}

QFont TextDelegate::font() const
{
    return m_font;
}

void TextDelegate::setFont(const QFont& font)
{
    if (m_font == font)
        return;

    m_font = font;
    emit fontChanged();
    emit changed();
}

QFont TextDelegate::currentFont() const
{
    return m_currentFont.value_or(m_font);
}

void TextDelegate::setCurrentFont(const QFont& currentFont)
{
    if (m_currentFont == currentFont)
        return;

    m_currentFont = currentFont;
    emit currentFontChanged();
    emit changed();
}

QFont TextDelegate::selectedFont() const
{
    return m_selectedFont.value_or(m_font);
}

void TextDelegate::setSelectedFont(const QFont& selectedFont)
{
    if (m_selectedFont == selectedFont)
        return;

    m_selectedFont = selectedFont;
    emit selectedFontChanged();
    emit changed();
}

QFont TextDelegate::disabledFont() const
{
    return m_disabledFont.value_or(m_font);
}

void TextDelegate::setDisabledFont(const QFont& disabledFont)
{
    if (m_disabledFont == disabledFont)
        return;

    m_disabledFont = disabledFont;
    emit disabledFontChanged();
    emit changed();
}

Qt::Alignment TextDelegate::alignment() const
{
    return m_alignment;
}

void TextDelegate::setAlignment(Qt::Alignment alignment)
{
    if (m_alignment == alignment)
        return;

    m_alignment = alignment;
    emit alignmentChanged();
    emit changed();
}

QString TextDelegate::nodeText(const QModelIndex& index, NodeItem* item) const
{
    Q_UNUSED(item);
    return index.data(m_textRole).toString();
}

QColor TextDelegate::nodeColor(const QModelIndex& index, NodeItem* item) const
{
    if (m_disabledColor.isValid() && !item->isEnabled(index))
        return m_disabledColor;
    if (m_selectedColor.isValid() && item->isSelected(index))
        return m_selectedColor;
    if (m_currentColor.isValid() && item->isCurrent(index))
        return m_currentColor;
    return m_color;
}

static bool isValidFont(std::optional<QFont> font)
{
    return font.has_value();
}

QFont TextDelegate::nodeFont(const QModelIndex& index, NodeItem* item) const
{
    QFont font = m_font;
    if (isValidFont(m_disabledFont) && !item->isEnabled(index))
        font = m_disabledFont.value().resolve(font);
    if (isValidFont(m_selectedFont) && item->isSelected(index))
        font = m_selectedFont.value().resolve(font);
    if (isValidFont(m_currentFont) && item->isCurrent(index))
        font = m_currentFont.value().resolve(font);
    font.setPixelSize(font.pixelSize() * item->nodeScale());
    return font;
}

Qt::Alignment TextDelegate::nodeAlignment(const QModelIndex& index, NodeItem* item) const
{
    Q_UNUSED(index)
    Q_UNUSED(item)
    return m_alignment;
}

HeaderDelegate::HeaderDelegate(QObject* parent)
    : TextDelegate(parent)
{}

Qt::Orientation HeaderDelegate::orientation() const
{
    return m_orientation;
}

void HeaderDelegate::setOrientation(Qt::Orientation orientation)
{
    if (m_orientation == orientation)
        return;

    m_orientation = orientation;
    emit orientationChanged();
    emit changed();
}

QString HeaderDelegate::nodeText(const QModelIndex& index, NodeItem* item) const
{
    Q_UNUSED(item);
    const QAbstractItemModel* model = index.model();
    int section = m_orientation == Qt::Horizontal ? index.column() : index.row();
    return model->headerData(section, m_orientation, textRole()).toString();
}

AbstractOpacityDelegate::AbstractOpacityDelegate(QObject* parent)
    : NodeDelegate(parent)
{}

QSGNode* AbstractOpacityDelegate::createNode(NodeItem* item)
{
    Q_UNUSED(item);
    QSGOpacityNode* opacityNode = new QSGOpacityNode;
    return opacityNode;
}

void AbstractOpacityDelegate::updateNode(QSGNode* node, const QModelIndex& index, NodeItem* item)
{
    QSGOpacityNode* opacityNode = static_cast<QSGOpacityNode*>(node);
    opacityNode->setOpacity(nodeOpacity(index, item));
}

OpacityDelegate::OpacityDelegate(QObject* parent)
    : AbstractOpacityDelegate(parent)
{}

qreal OpacityDelegate::opacity() const
{
    return m_opacity;
}

void OpacityDelegate::setOpacity(qreal opacity)
{
    if (qFuzzyCompare(m_opacity, opacity))
        return;

    m_opacity = opacity;
    emit opacityChanged();
    emit changed();
}

qreal OpacityDelegate::currentOpacity() const
{
    return m_currentOpacity;
}

void OpacityDelegate::setCurrentOpacity(qreal currentOpacity)
{
    if (qFuzzyCompare(m_currentOpacity, currentOpacity))
        return;

    m_currentOpacity = currentOpacity;
    emit currentOpacityChanged();
    emit changed();
}

qreal OpacityDelegate::selectedOpacity() const
{
    return m_selectedOpacity;
}

void OpacityDelegate::setSelectedOpacity(qreal selectedOpacity)
{
    if (qFuzzyCompare(m_selectedOpacity, selectedOpacity))
        return;

    m_selectedOpacity = selectedOpacity;
    emit selectedOpacityChanged();
    emit changed();
}

qreal OpacityDelegate::disabledOpacity() const
{
    return m_disabledOpacity;
}

void OpacityDelegate::setDisabledOpacity(qreal disabledOpacity)
{
    if (qFuzzyCompare(m_disabledOpacity, disabledOpacity))
        return;

    m_disabledOpacity = disabledOpacity;
    emit disabledOpacityChanged();
    emit changed();
}

int OpacityDelegate::opacityRole() const
{
    return m_opacityRole;
}

void OpacityDelegate::setOpacityRole(int opacityRole)
{
    if (m_opacityRole == opacityRole)
        return;

    m_opacityRole = opacityRole;
    emit opacityRoleChanged();
    emit changed();
}

static bool isValidOpacity(qreal opacity)
{
    return qFuzzyIsNull(opacity) || opacity > 0;
}

qreal OpacityDelegate::nodeOpacity(const QModelIndex& index, NodeItem* item) const
{
    if (m_opacityRole != -1) {
        bool ok = false;
        qreal opacity = index.data(m_opacityRole).toReal(&ok);
        if (ok && isValidOpacity(opacity))
            return opacity;
    }
    if (isValidOpacity(m_disabledOpacity) && !item->isEnabled(index))
        return m_disabledOpacity;
    if (isValidOpacity(m_selectedOpacity) && item->isSelected(index))
        return m_selectedOpacity;
    if (isValidOpacity(m_currentOpacity) && item->isCurrent(index))
        return m_currentOpacity;
    return m_opacity;
}

AbstractScaleDelegate::AbstractScaleDelegate(QObject* parent)
    : NodeDelegate(parent)
{}

QSGNode* AbstractScaleDelegate::createNode(NodeItem* item)
{
    Q_UNUSED(item);
    QSGTransformNode* scaleNode = new QSGTransformNode;
    return scaleNode;
}

void AbstractScaleDelegate::updateNode(QSGNode* node, const QModelIndex& index, NodeItem* item)
{
    QSGTransformNode* scaleNode = static_cast<QSGTransformNode*>(node);
    QRectF rect = nodeRect(index, item);
    QMatrix4x4 matrix;
    matrix.translate(rect.width() / 2.0, rect.height() / 2.0);
    matrix.scale(nodeScale(index, item));
    matrix.translate(-rect.width() / 2.0, -rect.height() / 2.0);
    scaleNode->setMatrix(matrix);
}

ScaleDelegate::ScaleDelegate(QObject* parent)
    : AbstractScaleDelegate(parent)
{}

qreal ScaleDelegate::scale() const
{
    return m_scale;
}

void ScaleDelegate::setScale(qreal scale)
{
    if (qFuzzyCompare(m_scale, scale))
        return;

    m_scale = scale;
    emit scaleChanged();
    emit changed();
}

qreal ScaleDelegate::currentScale() const
{
    return m_currentScale;
}

void ScaleDelegate::setCurrentScale(qreal currentScale)
{
    if (qFuzzyCompare(m_currentScale, currentScale))
        return;

    m_currentScale = currentScale;
    emit currentScaleChanged();
    emit changed();
}

qreal ScaleDelegate::selectedScale() const
{
    return m_selectedScale;
}

void ScaleDelegate::setSelectedScale(qreal selectedScale)
{
    if (qFuzzyCompare(m_selectedScale, selectedScale))
        return;

    m_selectedScale = selectedScale;
    emit selectedScaleChanged();
    emit changed();
}

qreal ScaleDelegate::disabledScale() const
{
    return m_disabledScale;
}

void ScaleDelegate::setDisabledScale(qreal disabledScale)
{
    if (qFuzzyCompare(m_disabledScale, disabledScale))
        return;

    m_disabledScale = disabledScale;
    emit disabledScaleChanged();
    emit changed();
}

int ScaleDelegate::scaleRole() const
{
    return m_scaleRole;
}

void ScaleDelegate::setScaleRole(int scaleRole)
{
    if (m_scaleRole == scaleRole)
        return;

    m_scaleRole = scaleRole;
    emit scaleRoleChanged();
    emit changed();
}

static bool isValidScale(qreal scale)
{
    return qFuzzyIsNull(scale) || scale >= 0;
}

qreal ScaleDelegate::nodeScale(const QModelIndex& index, NodeItem* item) const
{
    if (m_scaleRole != -1) {
        bool ok = false;
        qreal scale = index.data(m_scaleRole).toReal(&ok);
        if (ok && isValidScale(scale))
            return scale;
    }
    if (isValidScale(m_disabledScale) && !item->isEnabled(index))
        return m_disabledScale;
    if (isValidScale(m_selectedScale) && item->isSelected(index))
        return m_selectedScale;
    if (isValidScale(m_currentScale) && item->isCurrent(index))
        return m_currentScale;
    return m_scale;
}

ProgressDelegate::ProgressDelegate(QObject* parent)
    : RectDelegate(parent)
{}

int ProgressDelegate::colorRole() const
{
    return m_colorRole;
}

void ProgressDelegate::setColorRole(int colorRole)
{
    if (m_colorRole == colorRole)
        return;

    m_colorRole = colorRole;
    emit colorRoleChanged();
    emit changed();
}

int ProgressDelegate::progressRole() const
{
    return m_progressRole;
}

void ProgressDelegate::setProgressRole(int progressRole)
{
    if (m_progressRole == progressRole)
        return;

    m_progressRole = progressRole;
    emit progressRoleChanged();
    emit changed();
}

Qt::Orientation ProgressDelegate::orientation() const
{
    return m_orientation;
}

void ProgressDelegate::setOrientation(Qt::Orientation orientation)
{
    if (m_orientation == orientation)
        return;

    m_orientation = orientation;
    emit orientationChanged();
    emit changed();
}

Qt::LayoutDirection ProgressDelegate::layoutDirection() const
{
    return m_layoutDirection;
}

void ProgressDelegate::setLayoutDirection(Qt::LayoutDirection layoutDirection)
{
    if (m_layoutDirection == layoutDirection)
        return;

    m_layoutDirection = layoutDirection;
    emit layoutDirectionChanged();
    emit changed();
}

QColor ProgressDelegate::progressColor(const QModelIndex& index, NodeItem* item) const
{
    Q_UNUSED(item);
    if (m_colorRole != -1) {
        QColor color = index.data(m_colorRole).value<QColor>();
        if (color.isValid())
            return color;
    }
    return Qt::transparent;
}

QGradientStops* ProgressDelegate::nodeGradientStops(const QModelIndex& index, NodeItem* item) const
{
    bool ok = false;
    qreal progress = std::clamp(index.data(m_progressRole).toReal(&ok), 0.0, 1.0);
    if (!ok || progress == 0)
        return nullptr;

    QColor color1 = progressColor(index, item);
    QColor color2 = nodeColor(index, item);
    if (m_orientation == Qt::Vertical || m_layoutDirection == Qt::RightToLeft) {
        progress = 1.0 - progress;
        std::swap(color1, color2);
    }

    static QCache<QVector<uint>, QGradientStops> cache;
    uint p = static_cast<uint>(std::lround(progress * 1000));
    QVector<uint> key = {p, color1.rgba(), color2.rgba()};
    if (!cache.contains(key)) {
        QGradientStops* stops = new QGradientStops;
        stops->append(qMakePair(0.0, color1));
        stops->append(qMakePair(progress, color1));
        stops->append(qMakePair(progress, color2));
        stops->append(qMakePair(1.0, color2));
        cache.insert(key, stops);
    }
    return cache[key];
}

Qt::Orientation ProgressDelegate::nodeGradientOrientation(const QModelIndex& index, NodeItem* item) const
{
    Q_UNUSED(index)
    Q_UNUSED(item)
    return m_orientation;
}
