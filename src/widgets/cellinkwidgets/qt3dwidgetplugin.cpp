#include "cellinkwidgets_stable.h"
#include "cellinkwidgets_global.h"

#include "cellinkwidgets/qt3dwidget.h"

class Qt3DWidgetPlugin : public QObject, public QDesignerCustomWidgetInterface
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
    Qt3DWidgetPlugin(QObject *parent = 0);

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


Qt3DWidgetPlugin::Qt3DWidgetPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void Qt3DWidgetPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool Qt3DWidgetPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *Qt3DWidgetPlugin::createWidget(QWidget *parent)
{
    return new Qt3DWidget(parent);
}

QString Qt3DWidgetPlugin::name() const
{
    return QStringLiteral("Qt3DWidget");
}

QString Qt3DWidgetPlugin::group() const
{
    return QStringLiteral("Cellink Widgets");
}

QIcon Qt3DWidgetPlugin::icon() const
{
    return QIcon();
}

QString Qt3DWidgetPlugin::toolTip() const
{
    return QStringLiteral("");
}

QString Qt3DWidgetPlugin::whatsThis() const
{
    return QStringLiteral("");
}

bool Qt3DWidgetPlugin::isContainer() const
{
    return false;
}

QString Qt3DWidgetPlugin::domXml() const
{
    return QStringLiteral("<widget class=\"Qt3DWidget\" name=\"qt3dwidget\">\n</widget>\n");
}

QString Qt3DWidgetPlugin::includeFile() const
{
    return QStringLiteral("cellinkwidgets/qt3dwidget.h");
}

#include "qt3dwidgetplugin.moc"
