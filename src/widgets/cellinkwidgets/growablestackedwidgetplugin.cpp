#include "cellinkwidgets_stable.h"
#include "cellinkwidgets_global.h"

#include "cellinkwidgets/growablestackedwidget.h"

class CELLINKWIDGETS_EXPORT GrowableStackedWidgetPlugin : public QObject, public QDesignerCustomWidgetInterface
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
    GrowableStackedWidgetPlugin(QObject *parent = 0);

    bool isContainer() const;
    bool isInitialized() const;
    QIcon icon() const;
    QString domXml() const;
    QString group() const;
    QString includeFile() const;
    QString name() const;
    QString toolTip() const;
    QString whatsThis() const;
    QWidget *createWidget(QWidget *parent);
    void initialize(QDesignerFormEditorInterface *core);

private:
    bool m_initialized = false;
};


GrowableStackedWidgetPlugin::GrowableStackedWidgetPlugin(QObject *parent) :
    QObject(parent)
{
    m_initialized = false;
}

void GrowableStackedWidgetPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool GrowableStackedWidgetPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *GrowableStackedWidgetPlugin::createWidget(QWidget *parent)
{
    auto * w = new GrowableStackedWidget(parent);
    return w;
}

QString GrowableStackedWidgetPlugin::name() const
{
    return QStringLiteral("Stacked Widget");
}

QString GrowableStackedWidgetPlugin::group() const
{
    return QStringLiteral("Cellink Widgets");
}

QIcon GrowableStackedWidgetPlugin::icon() const
{
    return QIcon();
}

QString GrowableStackedWidgetPlugin::toolTip() const
{
    return QStringLiteral("");
}

QString GrowableStackedWidgetPlugin::whatsThis() const
{
    return QStringLiteral("");
}

bool GrowableStackedWidgetPlugin::isContainer() const
{
    return false;
}

QString GrowableStackedWidgetPlugin::domXml() const
{
    return QStringLiteral("<widget class=\"StackedWidget\" name=\"stackedWidget\">\n</widget>\n");
}

QString GrowableStackedWidgetPlugin::includeFile() const
{
    return QStringLiteral("cellinkwidgets/stackedwidget.h");
}

#include "growablestackedwidgetplugin.moc"
