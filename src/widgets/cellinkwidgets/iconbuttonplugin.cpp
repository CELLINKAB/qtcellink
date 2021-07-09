#include "cellinkwidgets_stable.h"
#include "cellinkwidgets_global.h"

#include "cellinkwidgets/iconbutton.h"

class IconButtonPlugin : public QObject, public QDesignerCustomWidgetInterface
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
    explicit IconButtonPlugin(QObject *parent = 0);
    ~IconButtonPlugin();

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


IconButtonPlugin::IconButtonPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void IconButtonPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

IconButtonPlugin::~IconButtonPlugin() = default;

bool IconButtonPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *IconButtonPlugin::createWidget(QWidget *parent)
{
    return new IconButton(parent);
}

QString IconButtonPlugin::name() const
{
    return QStringLiteral("IconButton");
}

QString IconButtonPlugin::group() const
{
    return QStringLiteral("Cellink Widgets");
}

QIcon IconButtonPlugin::icon() const
{
    return QIcon();
}

QString IconButtonPlugin::toolTip() const
{
    return QStringLiteral("");
}

QString IconButtonPlugin::whatsThis() const
{
    return QStringLiteral("");
}

bool IconButtonPlugin::isContainer() const
{
    return false;
}

QString IconButtonPlugin::domXml() const
{
    return QStringLiteral("<widget class=\"IconButton\" name=\"iconButton\">\n</widget>\n");
}

QString IconButtonPlugin::includeFile() const
{
    return QStringLiteral("cellinkwidgets/iconbutton.h");
}

#include "iconbuttonplugin.moc"
