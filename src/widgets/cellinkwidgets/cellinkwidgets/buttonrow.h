#ifndef BUTTONROW_H
#define BUTTONROW_H

#include "cellinkwidgets_global.h"

#include <QWidget>
#include <QToolButton>
#include <memory>

class ButtonRowPrivate;

class CELLINKWIDGETS_EXPORT ButtonRow : public QWidget
{
    Q_OBJECT
public:
    explicit ButtonRow(QWidget *parent = nullptr);
    ~ButtonRow() override;

    [[nodiscard]] int count() const;
    [[nodiscard]] int currentIndex() const;

    void addButton(const QString& text, bool enabled = true);
    void addButtons(const QStringList& texts);
    void updateButton(const int index, const QString& text);
    void updateSelectedColor(const int index, QColor selectedColor);
    void showButton(const QString& text, bool show);

    [[nodiscard]] QString currentText() const;
    [[nodiscard]] QString text(int index) const;

signals:
    void currentIndexChanged(int newIndex);

public slots:
    void setCurrentIndex(int index);
    void setButtonEnabled(int index, bool enabled);

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    Q_DECLARE_PRIVATE(ButtonRow)
    std::unique_ptr<ButtonRowPrivate> d_ptr;
};


class RowButtonPrivate;

class CELLINKWIDGETS_EXPORT RowButton : public QToolButton
{
    Q_OBJECT
public:
    explicit RowButton(QWidget *parent = nullptr);
    ~RowButton() override;

    void setIndex(int index);
    [[nodiscard]] int index() const;

signals:
    void indexChanged();

public slots:

protected:
    void paintEvent(QPaintEvent *event) override;
    [[nodiscard]] QSize minimumSizeHint() const override;

private:
    Q_DECLARE_PRIVATE(RowButton)
    std::unique_ptr<RowButtonPrivate> d_ptr;
};


#endif // BUTTONROW_H
