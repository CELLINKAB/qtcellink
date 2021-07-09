#ifndef QT3DWIDGET_H
#define QT3DWIDGET_H

#include "cellinkwidgets_global.h"

#include <QtWidgets/QWidget>
#include <QtCore/QPointer>
#include <memory>

namespace Qt3DExtras {
class Qt3DWindow;
}

class Qt3DWidgetPrivate;

/** @brief Qt3DWidget puts @c Qt3DWindow into a container in order to make it possible
 * to handle the view inside a widget
 *
 * @see https://stackoverflow.com/questions/35074830/show-qt3d-stuff-inside-qwidget-in-qt5
 *
 * Any added child widgets will be moved to a separate transparent window that tracks this widget
 */
class CELLINKWIDGETS_EXPORT Qt3DWidget : public QWidget
{
    Q_OBJECT
public:
    explicit Qt3DWidget(QWidget *parent = nullptr);
    ~Qt3DWidget() override;

    Qt3DExtras::Qt3DWindow* view() const;
    QWidget* onTopWidget() const;

protected:
    void resizeEvent(QResizeEvent* event) override;
    void moveEvent(QMoveEvent* event) override;
    void showEvent(QShowEvent* event) override;
    void childEvent(QChildEvent* event) override;
    bool eventFilter(QObject* target, QEvent* event) override;

private:
    Q_DECLARE_PRIVATE(Qt3DWidget);
    std::unique_ptr<Qt3DWidgetPrivate> d_ptr;

};

#endif // QT3DWIDGET_H
