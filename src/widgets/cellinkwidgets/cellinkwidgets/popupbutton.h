#ifndef POPUPBUTTON_H
#define POPUPBUTTON_H

#include "cellinkwidgets_global.h"
#include "injectedptr.h"
#include "cellinkwidgets/paper.h"

#include <memory>

class QtDialogs;
class PopupButtonPrivate;

/** @brief This class represent a button with text and arrow icon. When pressed, a popup will show.
 *
 * @note Note, either set popup (instance) or popup class, not both. (Only the latest set will be used).
 */
class CELLINKWIDGETS_EXPORT PopupButton : public Paper
{
    Q_OBJECT
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged);

public:
    explicit PopupButton(QWidget *parent = nullptr,
                              InjectedPtr<QtDialogs> qtDialogs = {});
    ~PopupButton() override;

    [[nodiscard]] QString text() const;

    /// @brief Set dialog that will show as popup when button is clicked.
    void setPopup(QDialog* popup, Qt::Alignment popupAlignment, int xMargin = 50, int yMargin = 0);
    [[nodiscard]] QDialog* popup() const;

    void setPopupClass(const QMetaObject& meta, Qt::Alignment popupAlignment,
                       int xMargin = 50, int yMargin = 0);

protected:
    void mouseReleaseEvent(QMouseEvent *event) override;

signals:
    void aboutToShowPopup(QDialog* d);
    void selected();

    void textChanged(const QString& value);
    void popupChanged(QDialog* value);
    void popupClassChanged(const QMetaObject* value);

public slots:
    void click();
    void setText(const QString& text);

private:
    Q_DECLARE_PRIVATE(PopupButton)
    std::unique_ptr<PopupButtonPrivate> d_ptr;
};

#endif // POPUPBUTTON_H
