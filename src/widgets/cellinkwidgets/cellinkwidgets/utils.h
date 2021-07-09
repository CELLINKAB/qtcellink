#ifndef UTILS_H
#define UTILS_H

#include "cellinkwidgets_global.h"

class QWidget;
class QPixmap;

/** @brief Collection of helper functions
 */
namespace Utils {

/**
 * @brief setMask uses QWidget::setMask to set a mask for @p widget
 * @param widget widget to set mask on
 * @param region region of the mask
 */
CELLINKWIDGETS_EXPORT void setMask(QWidget* widget, const QPainterPath& path);

/**
 * @brief setArrowPopupMask uses QWidget::setMask to set a mask of rounded popup with up arrow.
 * @param widget widget to set mask on
 * @param arrowXOffset arrow horizontal position offset
 */
CELLINKWIDGETS_EXPORT void setArrowPopupMask(QWidget* widget, int arrowXOffset);

/**
 * @brief setRoundedMask uses QWidget::setMask to set a rounded
 *        mask for @p widget with a @p radius.
 * @param widget
 * @param radius
 */
CELLINKWIDGETS_EXPORT void setRoundedMask(QWidget* widget, int radius = 4);

/**
 * @brief moveWidgetWithMargin moves @p moveWidget
 *        relative to @p pivotWidget according to alignment with @p xOffset and @p yOffset pixels offset.
 *        The center y of the two widgets will match.
 * @param pivotWidget The widget that @p moveWidget till move in relation to.
 * @param moveWidget The widget which will be moved.
 * @param where @p moveWidget will be placed relative to @p pivotWidget (Top, Left, TopRight, BottomLeft etc.)
 * @param xOffset How many pixels to the right or left @p moveWidget will move.
 * @param yOffset How many pixels to the bottom or top @p moveWidget will move.
 */
CELLINKWIDGETS_EXPORT void moveWidgetWithMargin(const QWidget *, QWidget *, Qt::Alignment alignment, int xOffset = 0, int yOffset = 0);

/**
 * @brief keepWidgetBottomVisible moves the
 *        @p moveWidget above the screen bottom line
 * @param moveWidget The widget which will be moved.
 */
CELLINKWIDGETS_EXPORT void keepWidgetBottomVisible(QWidget *moveWidget, int yOffset = 50);

/**
 * @brief loadPixmap loads a pixmap from the given path, and checks whether it exists in the cache already.
 * @param path
 * @return
 */
CELLINKWIDGETS_EXPORT QPixmap loadPixmap(const QString& path);

/**
 * @brief computeIntervalString computes interval string, i.e. 1-3, 5-6 from (1,2,3,5,6)
 * @param entries source data
 * @return string with consecutive entries merged
 */
CELLINKWIDGETS_EXPORT QString computeIntervalString(QVector<int> entries);

/**
 * @brief retainSizeWhenHidden sets the widget's size policy so that it keeps the same size when hidden.
 * @param widget
 */
CELLINKWIDGETS_EXPORT void retainSizeWhenHidden(QWidget* widget);

/**
 * @brief setIgnoreVerticalSizePolicy adjusts the QWidget's vertical size policy
 * @param widget
 * @param ignore
 */
CELLINKWIDGETS_EXPORT void setIgnoreVerticalSizePolicy(QWidget* widget, bool ignore);

/**
 * @brief setWidgetBackgroundColor sets the widget's background color.
 * @param widget
 * @param color
*/
CELLINKWIDGETS_EXPORT void setWidgetBackgroundColor(QWidget* widget, const QColor& color);

/**
 * @brief paint message on full screen
 * @param widget
*/
CELLINKWIDGETS_EXPORT void paintFullScreenMessage(QWidget* widget);

}

#endif // UTILS_H
