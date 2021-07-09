#ifndef PAINTEDVIDEOWIDGET_H
#define PAINTEDVIDEOWIDGET_H

#include "cellinkwidgets_global.h"
#include <QVideoWidget>

/**
 * @brief A QVideoWidget with message on full screen
 *
 * Paints a message on full screen view
 */
class CELLINKWIDGETS_EXPORT PaintedVideoWidget : public QVideoWidget
{
    Q_OBJECT

public:
    explicit PaintedVideoWidget(QWidget *parent = nullptr);
    ~PaintedVideoWidget() override;

    void paintEvent(QPaintEvent *event) override;
};

#endif // PAINTEDVIDEOWIDGET_H
