#ifndef MENUTABBUTTONS_H
#define MENUTABBUTTONS_H

#include <QWidget>
#include <memory>

#include "cellinkwidgets_global.h"

class MenuTabButtonsPrivate;
class QPushButton;

class CELLINKWIDGETS_EXPORT MenuTabButtons : public QWidget
{
    Q_OBJECT

public:
    explicit MenuTabButtons(QWidget *parent = nullptr);
    ~MenuTabButtons() override;

    [[nodiscard]] QPushButton* addButton(const QString enablePath,
                                         const QString selectedPath,
                                         const QString imageName);
    void showSelection(bool show, const int index = -1);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    Q_DECLARE_PRIVATE(MenuTabButtons);
    std::unique_ptr<MenuTabButtonsPrivate> d_ptr;

};

#endif // MENUTABBUTTONS_H
