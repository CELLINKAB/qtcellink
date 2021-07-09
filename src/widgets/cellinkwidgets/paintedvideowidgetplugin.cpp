#include "cellinkwidgets_stable.h"
#include "cellinkwidgets_global.h"

#include "cellinkwidgets/paintedvideowidget.h"


class PaintedVideoWidgetPlugin : public QObject, public QDesignerCustomWidgetInterface
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
    PaintedVideoWidgetPlugin(QObject *parent = 0);

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

PaintedVideoWidgetPlugin::PaintedVideoWidgetPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void PaintedVideoWidgetPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool PaintedVideoWidgetPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *PaintedVideoWidgetPlugin::createWidget(QWidget *parent)
{
    return new PaintedVideoWidget(parent);
}

QString PaintedVideoWidgetPlugin::name() const
{
    return QStringLiteral("PaintedVideoWidget");
}

QString PaintedVideoWidgetPlugin::group() const
{
    return QStringLiteral("Cellink Widgets");
}

QIcon PaintedVideoWidgetPlugin::icon() const
{
    return QIcon();
}

QString PaintedVideoWidgetPlugin::toolTip() const
{
    return QStringLiteral("");
}

QString PaintedVideoWidgetPlugin::whatsThis() const
{
    return QStringLiteral("");
}

bool PaintedVideoWidgetPlugin::isContainer() const
{
    return false;
}

QString PaintedVideoWidgetPlugin::domXml() const
{
    return QStringLiteral("<widget class=\"PaintedVideoWidget\" name=\"paintedVideoWidget\">\n</widget>\n");
}

QString PaintedVideoWidgetPlugin::includeFile() const
{
    return QStringLiteral("cellinkwidgets/paintedvideowidget.h");
}

#include "paintedvideowidgetplugin.moc"
