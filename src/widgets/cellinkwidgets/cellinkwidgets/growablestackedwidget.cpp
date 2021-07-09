#include "cellinkwidgets_stable.h"
#include "growablestackedwidget.h"

#include "utils.h"

GrowableStackedWidget::GrowableStackedWidget(QWidget *parent) :
    QStackedWidget(parent)
{
}

GrowableStackedWidget::~GrowableStackedWidget() = default;

QSize GrowableStackedWidget::sizeHint() const
{
    return currentWidget()->sizeHint();
}

QSize GrowableStackedWidget::minimumSizeHint() const
{
    return currentWidget()->minimumSizeHint();
}

void GrowableStackedWidget::paintEvent(QPaintEvent *event)
{
    if (!isFullScreen()) {
        return QWidget::paintEvent(event);
    }

    Utils::paintFullScreenMessage(this);
}
