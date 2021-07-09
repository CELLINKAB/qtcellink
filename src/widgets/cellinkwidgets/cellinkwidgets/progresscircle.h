#pragma once
#include "cellinkwidgets_global.h"
#include <QWidget>
#include <QPropertyAnimation>

class CELLINKWIDGETS_EXPORT ProgressCircle : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int value READ value WRITE setValue NOTIFY valueChanged)
    Q_PROPERTY(int maximum READ maximum WRITE setMaximum NOTIFY maximumChanged)
    Q_PROPERTY(qreal innerRadius READ innerRadius WRITE setInnerRadius)
    Q_PROPERTY(qreal outerRadius READ outerRadius WRITE setOuterRadius)
    Q_PROPERTY(QColor color READ color WRITE setColor)

    //private
    Q_PROPERTY(qreal infiniteAnimationValue READ infiniteAnimationValue WRITE setInfiniteAnimationValue)
    Q_PROPERTY(int visibleValue READ visibleValue WRITE setVisibleValue)

public:
    explicit ProgressCircle(QWidget *parent = nullptr);
    ~ProgressCircle() override;

    int value() const;
    int maximum() const;
    qreal innerRadius() const;
    qreal outerRadius() const;
    QColor color() const;

public slots:
    void setValue(int value);
    void setMaximum(int maximum);
    void setInnerRadius(qreal innerRadius);
    void setOuterRadius(qreal outerRadius);
    void setColor(QColor color);
    void setTextColor(QColor color);

signals:
    void valueChanged(int);
    void maximumChanged(int);

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void setInfiniteAnimationValue(qreal value);
    void setVisibleValue(int value);

private:
    QString key() const;
    QPixmap generatePixmap() const;
    qreal infiniteAnimationValue() const;
    int visibleValue() const;
    QFont textFont();

private:
    //actual current value
    int m_value;
    int m_maximum;
    qreal m_innerRadius;
    qreal m_outerRadius;
    QColor m_color;
    QColor m_textColor;

    //value visible to user
    int m_visibleValue;
    QPropertyAnimation m_valueAnimation;
    QPropertyAnimation m_infiniteAnimation;
    qreal m_infiniteAnimationValue;
};
