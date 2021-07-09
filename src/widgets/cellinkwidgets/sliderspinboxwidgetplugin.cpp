#include "cellinkwidgets_stable.h"
#include "cellinkwidgets_global.h"

#include "cellinkwidgets/sliderspinboxwidget.h"

class SliderSpinBoxWidgetPlugin : public QObject, public QDesignerCustomWidgetInterface
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)


public:
    SliderSpinBoxWidgetPlugin(QObject *parent = 0);

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
    bool m_initialized;
};

SliderSpinBoxWidgetPlugin::SliderSpinBoxWidgetPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void SliderSpinBoxWidgetPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool SliderSpinBoxWidgetPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *SliderSpinBoxWidgetPlugin::createWidget(QWidget *parent)
{
    return new SliderSpinBoxWidget(parent);
}

QString SliderSpinBoxWidgetPlugin::name() const
{
    return QStringLiteral("ToggleSwitch");
}

QString SliderSpinBoxWidgetPlugin::group() const
{
    return QStringLiteral("Cellink Widgets");
}

QIcon SliderSpinBoxWidgetPlugin::icon() const
{
    return QIcon();
}

QString SliderSpinBoxWidgetPlugin::toolTip() const
{
    return QStringLiteral("");
}

QString SliderSpinBoxWidgetPlugin::whatsThis() const
{
    return QStringLiteral("");
}

bool SliderSpinBoxWidgetPlugin::isContainer() const
{
    return false;
}

QString SliderSpinBoxWidgetPlugin::domXml() const
{
    return QStringLiteral("<widget class=\"SliderSpinBoxWidget\" name=\"sliderSpinBoxWidget\">\n</widget>\n");
}

QString SliderSpinBoxWidgetPlugin::includeFile() const
{
    return QStringLiteral("cellinkwidgets/sliderspinboxwidget.h");
}

#include "sliderspinboxwidgetplugin.moc"
