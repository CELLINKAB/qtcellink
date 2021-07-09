#ifndef COMBOBOX_H
#define COMBOBOX_H

#include "cellinkwidgets_global.h"
#include <QComboBox>
#include <memory>

class ComboBoxPrivate;

class CELLINKWIDGETS_EXPORT ComboBox : public QComboBox
{
    Q_OBJECT
    Q_PROPERTY(QString placeholderText READ placeholderText WRITE setPlaceholderText NOTIFY placeholderTextChanged)
public:
    explicit ComboBox(QWidget *parent = nullptr);
    ~ComboBox() override;

    // If Qt >= 5.15 placeholderText is included in QComboBox so this can be replaced
    // Note that currentText() won't work for currentIndex = -1 for this widget
    void setPlaceholderText(QString text);
    QString placeholderText() const;
    void setBorderColor(const QColor borderColor);

signals:
    void placeholderTextChanged(QString text);

protected:
    void paintEvent(QPaintEvent *event) override;
private:
    Q_DECLARE_PRIVATE(ComboBox)
    std::unique_ptr<ComboBoxPrivate> d_ptr;
};

#endif // COMBOBOX_H
