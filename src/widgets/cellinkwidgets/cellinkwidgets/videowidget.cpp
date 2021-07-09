#include "cellinkwidgets_stable.h"

#include "videowidget.h"
#include "ui_videowidget.h"

#include <QMediaPlayer>
#include <QVideoWidget>

#include "printers/connectionfeature.h"
#include "cellinkstyles/style.h"
#include "misc.h"

namespace Ui {
class VideoWidget;
}

namespace {
constexpr auto noLabelSize = QSize(120, 100);
constexpr auto maxNoLabelSize = QSize(900, 750);
constexpr auto noLabelPath{":/cellinkwidgets/images/video-slash.svg"};
}

class VideoWidgetPrivate
{
    Q_DECLARE_PUBLIC(VideoWidget);

public:
    [[nodiscard]] QString saveDir() const;

    void setFullscreen(bool status);
    void setSaveDir(const QString& dir);
    void setUrl(const QUrl &url);
    void updateCurrentWidget();
    void changeVisibility(bool state);
    void updateFullSizeWidget();

    VideoWidget* const q_ptr;

    Ui::VideoWidget m_ui {};
    QMediaPlayer m_mediaPlayer {q_ptr, QMediaPlayer::VideoSurface};
    QUrl m_url {};
    QTimer m_loadingTimer {};
    bool m_fullscreen = false;
};

VideoWidget::VideoWidget(QWidget *parent) :
    QWidget(parent), d_ptr{new VideoWidgetPrivate{this}}
{
    Q_D(VideoWidget);
    d->m_ui.setupUi(this);

    d->m_loadingTimer.setInterval(1000/60);
    d->m_ui.loadingIndicator->setColor(Style::mainBlue);

    d->m_mediaPlayer.setMedia(d->m_url);
    d->m_mediaPlayer.setVideoOutput(d->m_ui.videoWidget);

    d->m_ui.noVideoLabel->setMaximumSize(noLabelSize);

    d->m_ui.loadingPage->installEventFilter(this);
    d->m_ui.videoWidget->installEventFilter(this);
    d->m_ui.noVideoLabel->installEventFilter(this);
    d->m_ui.errorPage->installEventFilter(this);
    d->m_ui.stackedWidget->installEventFilter(this);
    d->m_ui.videoLayout->addWidget(d->m_ui.videoWidget);

    connect(&d->m_mediaPlayer, QOverload<QMediaPlayer::Error>::of(&QMediaPlayer::error), this, [this, d] (auto error) {
        qWarning() << "Media player error" << d->m_mediaPlayer.errorString() << error;
        d->m_ui.errorMessageLabel->setText(d->m_mediaPlayer.errorString());

        if (error == QMediaPlayer::ResourceError) {
            d->m_mediaPlayer.stop();

            QTimer::singleShot(1000, this, [d]() {
                d->m_mediaPlayer.play();
                d->updateFullSizeWidget();
            });
        }
    });

    const auto updateCurrentWidget = [d]() { d->updateCurrentWidget(); };
    connect(&d->m_mediaPlayer, &QMediaPlayer::stateChanged, this, updateCurrentWidget);
    connect(&d->m_mediaPlayer, &QMediaPlayer::mediaStatusChanged, this, updateCurrentWidget);
    connect(&d->m_mediaPlayer, &QMediaPlayer::videoAvailableChanged, this, updateCurrentWidget);
    updateCurrentWidget();

    connect(&d->m_loadingTimer, &QTimer::timeout, this, [d]() { d->m_ui.loadingIndicator->cycleProgress(); });
}

VideoWidget::~VideoWidget() = default;

void VideoWidget::changeVisibility(bool state)
{
    d_ptr->changeVisibility(state);
    state ? show() : hide();
    update();
}

bool VideoWidget::fullscreen() const
{
    return d_ptr->m_fullscreen;
}

void VideoWidget::setFullscreen(bool status)
{
    Q_D(VideoWidget);
    d->setFullscreen(status);
}

QUrl VideoWidget::url() const
{
    return d_ptr->m_url;
}

void VideoWidget::setUrl(const QUrl &url)
{
    d_ptr->setUrl(url);
}

void VideoWidget::showEvent(QShowEvent *event)
{
    Q_D(VideoWidget);

    QWidget::showEvent(event);
    d->m_loadingTimer.start();

    if (d->m_mediaPlayer.state() != QMediaPlayer::PlayingState) {
        refreshVideo();
    }
}

void VideoWidget::refreshVideo()
{
    Q_D(VideoWidget);
    d->m_mediaPlayer.stop();
    d->changeVisibility(true);
    d->updateCurrentWidget();
}

void VideoWidget::hideEvent(QHideEvent *event)
{
    Q_D(VideoWidget);

    QWidget::hideEvent(event);
    d->m_loadingTimer.stop();
    d->changeVisibility(false);
}

bool VideoWidget::eventFilter(QObject *obj, QEvent *event)
{
    Q_D(VideoWidget);
    if (!d->m_fullscreen) {
        return QObject::eventFilter(obj, event);
    }

    if(event->type() == QEvent::KeyPress || event->type() == QEvent::MouseButtonPress)
    {
        d->setFullscreen(false);
        return true;
    }
    return QObject::eventFilter(obj, event);
}

void VideoWidgetPrivate::setFullscreen(bool fullscreen)
{
    Q_Q(VideoWidget);

    if (Misc::updateProperty(q, fullscreen, m_fullscreen, &VideoWidget::fullscreenStatusChanged)) {
        m_ui.stackedWidget->setWindowFlag(Qt::Window, m_fullscreen);
        const auto labelSize = m_fullscreen ? maxNoLabelSize : noLabelSize;
        m_ui.noVideoLabel->setPixmap(QPixmap(noLabelPath).scaled(labelSize));
        m_ui.noVideoLabel->setMaximumSize(labelSize);
    }
    updateFullSizeWidget();
}

void VideoWidgetPrivate::setUrl(const QUrl &url)
{
    Q_Q(VideoWidget);
    CI_ASSERT(!url.isEmpty());

    if (Misc::updateProperty(q, url, m_url, &VideoWidget::urlChanged))
    {
        changeVisibility(false);
        m_mediaPlayer.setVideoOutput(m_ui.videoWidget);
        changeVisibility(true);
    }
}

void VideoWidgetPrivate::changeVisibility(bool visibility)
{
    if (visibility) {
        m_mediaPlayer.setMedia(m_url);
        m_mediaPlayer.play();
    }
    else {
        m_mediaPlayer.stop();
        m_mediaPlayer.setMedia({});
    }

    m_ui.videoWidget->update();
}

void VideoWidgetPrivate::updateCurrentWidget()
{
    Q_Q(VideoWidget);

    // adapted from BxCameraLoader.qml, hence the weird booleans

    const auto& media = m_mediaPlayer;
    qDebug() << "Media player:     " << media.mediaStatus() << media.state();

    const auto isPlaying = media.state() == QMediaPlayer::PlayingState;
    const auto isLoading = media.mediaStatus() == QMediaPlayer::LoadingMedia ||
                           media.mediaStatus() == QMediaPlayer::BufferingMedia;
    const auto noVideo = !isPlaying && !isLoading;

    const auto stack = m_ui.stackedWidget;

    auto newPage = m_ui.loadingPage;

    if (noVideo || media.mediaStatus() == QMediaPlayer::EndOfMedia) {
        newPage = m_ui.noVideoPage;
    }
    else if (media.mediaStatus() == QMediaPlayer::InvalidMedia) {
        newPage = m_ui.errorPage;
    }
    else if (!isLoading && isPlaying && media.isVideoAvailable()) {
        newPage = m_ui.videoPage;
    }

    qDebug() << "Changing page:" << stack->currentWidget();
    stack->setCurrentWidget(newPage);
    newPage == m_ui.videoPage && q->isVisible() ? m_ui.videoWidget->show() : m_ui.videoWidget->hide();
    if (q->isVisible()) {
        updateFullSizeWidget();
    }
}

void VideoWidgetPrivate::updateFullSizeWidget()
{
    m_fullscreen ? m_ui.stackedWidget->showFullScreen() :
                   m_ui.stackedWidget->show();
    if (m_ui.stackedWidget->currentWidget() == m_ui.videoPage) {
        m_ui.videoWidget->setFullScreen(m_fullscreen);
    }
}
