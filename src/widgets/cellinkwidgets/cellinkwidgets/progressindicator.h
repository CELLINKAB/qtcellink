#ifndef PROGRESSINDICATOR_H
#define PROGRESSINDICATOR_H

#include "cellinkwidgets_global.h"

#include <QWidget>
#include <memory>

class ProgressIndicatorPrivate;

/**
 * @brief The ProgressIndicator class
 *
 * Implementation taken and adjusted from:
 * HeartWare/src/3rdparty/qtcellink/src/imports/controls/progressindicator.h
 * HeartWare/src/3rdparty/qtcellink/src/imports/controls/progressindicator.cpp
 */
class CELLINKWIDGETS_EXPORT ProgressIndicator : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor FINAL DESIGNABLE true)
    Q_PROPERTY(int lineWidth READ lineWidth WRITE setLineWidth FINAL DESIGNABLE true)
    Q_PROPERTY(qreal progress READ progress WRITE setProgress FINAL)

public:
    ProgressIndicator(QWidget* parent = nullptr);
    ~ProgressIndicator() override;

    [[nodiscard]] QColor color() const;
    void setColor(QColor color);

    [[nodiscard]] int lineWidth() const;
    void setLineWidth(int width);

    [[nodiscard]] qreal progress() const;
    void setProgress(qreal progress);

public slots:
    /**
     * @brief cycleProgress
     *
     * Runs one full progress animation cycle repeatedly, behaving like a busy indicator.
     *
     * @param refreshRateMs Frequency of external refresh, which is used in progress calculation,
     *                      so for any refresh rate animation runs for the same amount of time.
     *
     */
    void cycleProgress(int refreshRateMs = 1000/60);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    Q_DECLARE_PRIVATE(ProgressIndicator);
    std::unique_ptr<ProgressIndicatorPrivate> d_ptr;
};

#endif // PROGRESSINDICATOR_H
