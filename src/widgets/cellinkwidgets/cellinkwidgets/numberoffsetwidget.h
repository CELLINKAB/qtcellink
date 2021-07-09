#ifndef NUMBEROFFSETWIDGET_H
#define NUMBEROFFSETWIDGET_H

#include "cellinkwidgets_global.h"
#include <QWidget>
#include <memory>

class NumberOffsetWidgetPrivate;
class QDoubleSpinBox;

class CELLINKWIDGETS_EXPORT NumberOffsetWidget : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(double min READ minimum WRITE setMinimum)
    Q_PROPERTY(double max READ maximum WRITE setMaximum)
    Q_PROPERTY(int decimals READ decimals WRITE setDecimals)
    Q_PROPERTY(QString suffix READ suffix WRITE setSuffix)
    Q_PROPERTY(double offset1 READ offset1 WRITE setOffset1)
    Q_PROPERTY(double offset2 READ offset2 WRITE setOffset2)
    Q_PROPERTY(double offset3 READ offset3 WRITE setOffset3)
    Q_PROPERTY(QString pixmap READ pixmap WRITE setPixmap)
    Q_PROPERTY(bool visibleOffset READ isVisibleOffset WRITE setVisibleOffset)
    Q_PROPERTY(double value READ value WRITE setValue NOTIFY valueChanged)

public:
    explicit NumberOffsetWidget(QWidget *parent = nullptr);
    virtual ~NumberOffsetWidget() override;

    void setAlwaysHidden();
    [[nodiscard]] double minimum() const;
    [[nodiscard]] double maximum() const;
    [[nodiscard]] int decimals() const;
    [[nodiscard]] QString suffix() const;
    [[nodiscard]] double offset1() const;
    [[nodiscard]] double offset2() const;
    [[nodiscard]] double offset3() const;
    [[nodiscard]] QString pixmap() const;
    [[nodiscard]] double currentOffset() const;
    [[nodiscard]] QDoubleSpinBox* spinbox() const;
    [[nodiscard]] bool isVisibleOffset() const;
    [[nodiscard]] double value() const;

signals:
    void valueChanged(double value);
    void alwaysHidden();

public slots:
    void setVisibleOffset(bool visible);
    void setValue(double value);
    void setMinimum(double min);
    void setMaximum(double max);
    void setDecimals(int decimals);
    void setSuffix(QString suffix);
    void setOffset1(double offset1);
    void setOffset2(double offset2);
    void setOffset3(double offset3);
    void setPixmap(QString pixmap);

protected:
    void paintEvent(QPaintEvent *event) override;
    void showEvent(QShowEvent *event) override;

private:
    Q_DECLARE_PRIVATE(NumberOffsetWidget);
    std::unique_ptr<NumberOffsetWidgetPrivate> d_ptr;
};

#endif // NUMBEROFFSETWIDGET_H
