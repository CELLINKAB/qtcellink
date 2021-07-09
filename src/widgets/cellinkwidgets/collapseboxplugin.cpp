#include "cellinkwidgets_stable.h"
#include "cellinkwidgets_global.h"

#include "cellinkwidgets/collapsebox.h"

class CollapseBoxPlugin : public QObject, public QDesignerCustomWidgetInterface
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)


public:
    CollapseBoxPlugin(QObject *parent = 0);

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

CollapseBoxPlugin::CollapseBoxPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void CollapseBoxPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool CollapseBoxPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *CollapseBoxPlugin::createWidget(QWidget *parent)
{
    return new CollapseBox(parent);
}

QString CollapseBoxPlugin::name() const
{
    return QStringLiteral("CollapseBox");
}

QString CollapseBoxPlugin::group() const
{
    return QStringLiteral("Cellink Widgets");
}

QIcon CollapseBoxPlugin::icon() const
{
    return QIcon();
}

QString CollapseBoxPlugin::toolTip() const
{
    return QStringLiteral("");
}

QString CollapseBoxPlugin::whatsThis() const
{
    return QStringLiteral("");
}

bool CollapseBoxPlugin::isContainer() const
{
    return true;
}

QString CollapseBoxPlugin::domXml() const
{
    return QStringLiteral("<widget class=\"CollapseBox\" name=\"collapseBox\">\n</widget>\n");
}

QString CollapseBoxPlugin::includeFile() const
{
    return QStringLiteral("cellinkwidgets/collapsebox.h");
}

#include "collapseboxplugin.moc"
