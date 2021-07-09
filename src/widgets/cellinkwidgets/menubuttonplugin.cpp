#include "cellinkwidgets_stable.h"
#include "cellinkwidgets_global.h"

#include "cellinkwidgets/menubutton.h"

class MenuButtonPlugin : public QObject, public QDesignerCustomWidgetInterface
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
    explicit MenuButtonPlugin(QObject *parent = 0);
    ~MenuButtonPlugin();

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


MenuButtonPlugin::MenuButtonPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void MenuButtonPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

MenuButtonPlugin::~MenuButtonPlugin() = default;

bool MenuButtonPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *MenuButtonPlugin::createWidget(QWidget *parent)
{
    return new MenuButton(parent);
}

QString MenuButtonPlugin::name() const
{
    return QStringLiteral("MenuButton");
}

QString MenuButtonPlugin::group() const
{
    return QStringLiteral("Cellink Widgets");
}

QIcon MenuButtonPlugin::icon() const
{
    return QIcon();
}

QString MenuButtonPlugin::toolTip() const
{
    return QStringLiteral("");
}

QString MenuButtonPlugin::whatsThis() const
{
    return QStringLiteral("");
}

bool MenuButtonPlugin::isContainer() const
{
    return false;
}

QString MenuButtonPlugin::domXml() const
{
    return QStringLiteral("<widget class=\"MenuButton\" name=\"menuButton\">\n</widget>\n");
}

QString MenuButtonPlugin::includeFile() const
{
    return QStringLiteral("cellinkwidgets/menubutton.h");
}

#include "menubuttonplugin.moc"
