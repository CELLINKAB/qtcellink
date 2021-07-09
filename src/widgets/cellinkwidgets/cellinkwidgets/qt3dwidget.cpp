#include "cellinkwidgets_stable.h"
#include "qt3dwidget.h"

namespace
{
/**
 * @brief The OnTopWindow class is a workaround to show QtWidgets on top of the @c Qt3DWindow
 *
 * taken from https://stackoverflow.com/questions/25466030/make-qwidget-transparent
 * couldn't get 2d layer to work in scene, nor a simple widget on top,
 */
class OnTopWindow : public QWidget
{
public:
    OnTopWindow(QWidget *parent) :
        QWidget(parent, Qt::Window | Qt::FramelessWindowHint)
    {
        setAttribute(Qt::WA_NoSystemBackground);
        setAttribute(Qt::WA_TranslucentBackground);
        setAttribute(Qt::WA_TransparentForMouseEvents);

        setLayout(new QVBoxLayout(this));
    }

    void closeEvent(QCloseEvent *event) override
    {
        parentWidget()->window()->close();         // pass it on
        event->ignore(); // nay!
    }
};

} // end anonymous namespace

class Qt3DWidgetPrivate
{
public:
    Qt3DWidgetPrivate(Qt3DWidget* q) :
        q_ptr(q),
        m_view(new Qt3DExtras::Qt3DWindow()),
        m_container(q->createWindowContainer(m_view, q)),
        m_onTopWindow(new OnTopWindow(m_container))
    {  }

    Qt3DWidget* const q_ptr;
    QPointer<Qt3DExtras::Qt3DWindow> const m_view;
    QPointer<QWidget> const m_container;
    OnTopWindow* const m_onTopWindow;

    void widgetSizeMove()
    {
        auto c = m_container;

        const auto p = c->mapToGlobal(c->pos());

        m_onTopWindow->move(p);
        m_onTopWindow->resize(c->size());

        // make sure window is visible when mainwindow is maximized
        if (c->window()->isVisible()) {
            m_onTopWindow->setWindowOpacity(1);
            m_onTopWindow->show();
            m_onTopWindow->raise();
            m_onTopWindow->update();
        } else {
            m_onTopWindow->setWindowOpacity(0);
            m_onTopWindow->hide();
        }
    }
};

Qt3DWidget::Qt3DWidget(QWidget *parent) :
    QWidget(parent),
    d_ptr(new Qt3DWidgetPrivate(this))
{
}

Qt3DWidget::~Qt3DWidget()
{
    Q_D(Qt3DWidget);
    d->m_container->deleteLater();
    d->m_view->deleteLater();
}

Qt3DExtras::Qt3DWindow* Qt3DWidget::view() const
{
    return d_ptr->m_view;
}

void Qt3DWidget::resizeEvent(QResizeEvent* event)
{
    Q_D(Qt3DWidget);

    QWidget::resizeEvent(event);
    d->m_container->resize(event->size());
    update();
    d->widgetSizeMove();
}

void Qt3DWidget::moveEvent(QMoveEvent *event)
{
    Q_D(Qt3DWidget);

    QWidget::moveEvent(event);
    update();
    d->widgetSizeMove();
}

void Qt3DWidget::showEvent(QShowEvent* event)
{
    Q_D(Qt3DWidget);
    QWidget::showEvent(event);
    QTimer::singleShot(50, this, [d]() { d->widgetSizeMove();} );

    window()->installEventFilter(this);
}

QWidget* Qt3DWidget::onTopWidget() const
{
    return d_ptr->m_onTopWindow;
}

bool Qt3DWidget::eventFilter(QObject* target, QEvent* event)
{
    Q_D(Qt3DWidget);

    if (target == window() && event->type() == QEvent::Move) {
        d->widgetSizeMove();
    }

    return QWidget::eventFilter(target, event);
}

void Qt3DWidget::childEvent(QChildEvent* event)
{
    QWidget::childEvent(event);

    if (children().count() <= 1 || event->child()->metaObject()->className() == QByteArray("QWindowContainer"))
        return; // the window container

    // move new children to on-top-widget instead
    if (event->polished()) {
        if (auto w = qobject_cast<QWidget*>(event->child())) {
            qDebug() << "Moved" << w << "to the onTopWindow";
            d_ptr->m_onTopWindow->layout()->addWidget(w);
            w->setAttribute(Qt::WA_NoSystemBackground);
            w->setAttribute(Qt::WA_TranslucentBackground);
        }
    }
}

