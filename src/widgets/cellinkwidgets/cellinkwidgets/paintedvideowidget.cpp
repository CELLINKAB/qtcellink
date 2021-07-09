#include "cellinkwidgets_stable.h"
#include "paintedvideowidget.h"

#include "utils.h"

PaintedVideoWidget::PaintedVideoWidget(QWidget *parent) :
    QVideoWidget(parent)
{
}

PaintedVideoWidget::~PaintedVideoWidget() = default;

void PaintedVideoWidget::paintEvent(QPaintEvent *event)
{
    QVideoWidget::paintEvent(event);
    if (!isFullScreen()) {
        return;
    }

    Utils::paintFullScreenMessage(this);
}
