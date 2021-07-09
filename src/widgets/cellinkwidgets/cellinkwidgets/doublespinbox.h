#ifndef DOUBLESPINBOX_H
#define DOUBLESPINBOX_H

#include "cellinkwidgets_global.h"
#include <QDoubleSpinBox>

class CELLINKWIDGETS_EXPORT DoubleSpinBox : public QDoubleSpinBox
{
    Q_OBJECT
    Q_PROPERTY(QString prefixColor READ prefixColor WRITE setPrefixColor NOTIFY prefixColorChanged)

public:
    explicit DoubleSpinBox(QWidget *parent = nullptr);
    ~DoubleSpinBox() override;

    [[nodiscard]] const QString& prefixColor() const { return m_prefixColor; }

signals:
    void doubleValueChanged(double value);
    void prefixColorChanged(const QString& prefixColor);

protected:
    QValidator::State validate(QString &input, int &pos) const override;

public slots:
    void setPrefixColor(QString prefixColor);

private:
    void fixInputDecimal(QString &input) const;

    QString m_prefixColor = "black";

};

#endif // DOUBLESPINBOX_H
