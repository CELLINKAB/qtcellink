#ifndef ICONBUTTON_H
#define ICONBUTTON_H

#include "cellinkwidgets_global.h"
#include <QPushButton>
#include <memory>

class IconButtonPrivate;

/** @brief This class represent a button with icon to the left with a 16px margin and center alligned text to the right
 */
class CELLINKWIDGETS_EXPORT IconButton : public QPushButton
{
    Q_OBJECT

public:
    explicit IconButton(QWidget *parent = nullptr);
    ~IconButton() override;

    [[nodiscard]] QString text() const;

signals:
    void textChanged(const QString& value);

public slots:
    void setText(const QString& text);
    void setIcon(const QIcon& icon);

private:
    Q_DECLARE_PRIVATE(IconButton)
    std::unique_ptr<IconButtonPrivate> d_ptr;
};

#endif // ICONBUTTON_H
