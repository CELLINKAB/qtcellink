#ifndef ROUNDEDPOPUP_H
#define ROUNDEDPOPUP_H

#include "cellinkwidgets_global.h"
#include <QDialog>
#include <memory>

class RoundedPopupPrivate;

class CELLINKWIDGETS_EXPORT RoundedPopup : public QDialog
{
    Q_OBJECT
public:

    enum ResizeFlag {
        NoResize = 0x0000,
        TopLeft = 0x0001,
        TopRight = 0x0002,
        BottomRight = 0x0004,
        BottomLeft = 0x0008
    };

    Q_DECLARE_FLAGS(ResizeFlags, ResizeFlag)
    Q_FLAGS(ResizeFlags)
    Q_ENUM(ResizeFlag)    

    explicit RoundedPopup(QWidget* parent = nullptr);
    explicit RoundedPopup(ResizeFlags resize, QWidget* parent = nullptr);
    ~RoundedPopup() override;

    void resizeEvent(QResizeEvent *event) override;
    void showEvent(QShowEvent *event) override;

    [[nodiscard]] QWidget* getContentWidget() const;

private:
    Q_DECLARE_PRIVATE(RoundedPopup);
    std::unique_ptr<RoundedPopupPrivate> d_ptr;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(RoundedPopup::ResizeFlags)

#endif // ROUNDEDPOPUP_H
