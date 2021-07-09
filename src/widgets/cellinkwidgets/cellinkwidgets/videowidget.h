#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H

#include "cellinkwidgets_global.h"

#include <QWidget>
#include <QUrl> // for moc
#include <memory>

class QMediaPlayer;
class VideoWidgetPrivate;

class CELLINKWIDGETS_EXPORT VideoWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(bool fullscreen READ fullscreen WRITE setFullscreen NOTIFY fullscreenStatusChanged);
    Q_PROPERTY(QUrl url READ url WRITE setUrl NOTIFY urlChanged);

public:
    VideoWidget(QWidget *parent = nullptr);
    ~VideoWidget() override;

    void changeVisibility(bool visibility);
    void refreshVideo();

    [[nodiscard]] bool fullscreen() const;
    void setFullscreen(bool fullScreen);

    [[nodiscard]] QUrl url() const;
    void setUrl(const QUrl& host);

signals:
    void fullscreenStatusChanged(bool fullScreen);
    void urlChanged(QUrl);

protected:
    void showEvent(QShowEvent *event) override;
    void hideEvent(QHideEvent *event) override;
    bool eventFilter(QObject* obj, QEvent* event) override;

private:
    Q_DECLARE_PRIVATE(VideoWidget);
    std::unique_ptr<VideoWidgetPrivate> d_ptr;
};

#endif // VIDEOWIDGET_H

