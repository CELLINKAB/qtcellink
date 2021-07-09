#ifndef TABBUTTONS_H
#define TABBUTTONS_H

#include "cellinkwidgets_global.h"
#include "heartware2_global.h"
#include <QWidget>
#include <memory>

using PrintType = heartware2::PrintType;
class TabButtonPrivate;

class CELLINKWIDGETS_EXPORT TabButton : public QWidget
{
    Q_OBJECT

public:
    explicit TabButton(QString text, const QString& size, const QString& iconPath, QWidget *parent = nullptr);
    ~TabButton() override;

    [[nodiscard]] QSize sizeHint() const override;

    [[nodiscard]] bool isSelected() const;

signals:
    void selectedChanged();
    void buttonSelected(TabButton* which);
    void clicked();

public slots:
    void click();
    void setSelected(bool selected);

protected:
    explicit TabButton(QString text, const QString& size, const QString& iconPath, QWidget *parent, TabButtonPrivate* data);

    void mouseReleaseEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

    Q_DECLARE_PRIVATE(TabButton)
    std::unique_ptr<TabButtonPrivate> d_ptr;
};

using SurfaceTabButton = TabButton;

class DropletTabButtonPrivate;
class CELLINKWIDGETS_EXPORT DropletTabButton : public TabButton
{
    Q_OBJECT
    Q_PROPERTY(PrintType type READ type CONSTANT);

public:
    explicit DropletTabButton(PrintType type, const QString& size, const QString& iconPath, QWidget *parent = nullptr);
    ~DropletTabButton() override;

    [[nodiscard]] PrintType type() const;

private:
    Q_DECLARE_PRIVATE(DropletTabButton);

};

#endif // TABBUTTONS_H
