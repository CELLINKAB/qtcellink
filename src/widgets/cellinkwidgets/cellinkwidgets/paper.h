#ifndef PAPER_H
#define PAPER_H

#include "cellinkwidgets_global.h"
#include "styleinterface.h"

#include <QWidget>
#include <QPen>
#include <memory>

class PaperPrivate;

/** @brief This class is a widget container with a certain style.
 * It looks similar to a paper sheet on the UI, hence the name.
 *
 * @details The features of Paper are:
 *  - Background is white
 *  - Rounded edges
 *  - Optional Shadow defined by a given Style::Shadow
 *  - Optional border defined by a given QPen
*/
class CELLINKWIDGETS_EXPORT Paper : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QPen borderPen READ borderPen WRITE setBorderPen NOTIFY borderPenChanged);
    Q_PROPERTY(bool borderEnabled READ isBorderEnabled WRITE setBorderEnabled NOTIFY borderEnabledChanged);
    Q_PROPERTY(bool clickable READ isClickable WRITE setClickable);

public:
    explicit Paper(QWidget* parent = nullptr, Style::Shadow shadowType = Style::Shadow::Default);
    ~Paper() override;

    [[nodiscard]] QPen borderPen() const;
    [[nodiscard]] bool isBorderEnabled() const;
    [[nodiscard]] bool isClickable() const;

signals:
    void borderEnabledChanged(bool value);
    void borderPenChanged(const QPen& value);
    void clicked();

public slots:
    void setBorderEnabled(bool enabled);
    void setBorderPen(QPen borderPen);
    void setClickable(bool clickable);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

private:
    Q_DECLARE_PRIVATE(Paper)
    std::unique_ptr<PaperPrivate> d_ptr;
};

#endif // PAPER_H
