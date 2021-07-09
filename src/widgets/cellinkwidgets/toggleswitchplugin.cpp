#include "cellinkwidgets_stable.h"
#include "cellinkwidgets_global.h"

#include "cellinkwidgets/toggleswitch.h"

class ToggleSwitchPlugin : public QObject, public QDesignerCustomWidgetInterface
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)


public:
    ToggleSwitchPlugin(QObject *parent = 0);

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

ToggleSwitchPlugin::ToggleSwitchPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void ToggleSwitchPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool ToggleSwitchPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *ToggleSwitchPlugin::createWidget(QWidget *parent)
{
    return new ToggleSwitch(parent);
}

QString ToggleSwitchPlugin::name() const
{
    return QStringLiteral("ToggleSwitch");
}

QString ToggleSwitchPlugin::group() const
{
    return QStringLiteral("Cellink Widgets");
}

QIcon ToggleSwitchPlugin::icon() const
{
    return QIcon();
}

QString ToggleSwitchPlugin::toolTip() const
{
    return QStringLiteral("");
}

QString ToggleSwitchPlugin::whatsThis() const
{
    return QStringLiteral("");
}

bool ToggleSwitchPlugin::isContainer() const
{
    return false;
}

QString ToggleSwitchPlugin::domXml() const
{
    return QStringLiteral("<widget class=\"ToggleSwitch\" name=\"toggleSwitch\">\n</widget>\n");
}

QString ToggleSwitchPlugin::includeFile() const
{
    return QStringLiteral("cellinkwidgets/toggleswitch.h");
}

#include "toggleswitchplugin.moc"
