#ifndef SLIDERSPINBOXWIDGET_H
#define SLIDERSPINBOXWIDGET_H

#include "cellinkwidgets_global.h"
#include <QWidget>
#include <memory>

class SliderSpinBoxWidgetPrivate;

class CELLINKWIDGETS_EXPORT SliderSpinBoxWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SliderSpinBoxWidget(QWidget *parent = nullptr);
    ~SliderSpinBoxWidget();

    int value() const;
    void setValue(const int value);

    bool isChecked() const;
    void setChecked(const bool check);

signals:
    void valueChanged(const int intensity);
    void checkChanged(const bool enable);

private:
    Q_DECLARE_PRIVATE(SliderSpinBoxWidget)
    std::unique_ptr<SliderSpinBoxWidgetPrivate> d_ptr;
};

#endif // SLIDERSPINBOXWIDGET_H
