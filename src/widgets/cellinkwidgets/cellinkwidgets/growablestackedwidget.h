#ifndef GROWABLESTACKEDWIDGET_H
#define GROWABLESTACKEDWIDGET_H

#include "cellinkwidgets_global.h"
#include <QStackedWidget>

/**
 * @brief A QStackedWidget whose size depends on the current pages size
 *
 * Follows the size of it's current page, so the parent (like scroll areas) could adjust
 */
class CELLINKWIDGETS_EXPORT GrowableStackedWidget : public QStackedWidget
{
    Q_OBJECT

public:
    explicit GrowableStackedWidget(QWidget *parent = nullptr);
    ~GrowableStackedWidget() override;

    [[nodiscard]] QSize sizeHint() const override;
    [[nodiscard]] QSize minimumSizeHint() const override;

    void paintEvent(QPaintEvent *event) override;
};

#endif // GROWABLESTACKEDWIDGET_H
