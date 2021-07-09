#include "cellinkwidgets_stable.h"
#include "cellinkwidgets_global.h"

#include "cellinkwidgets/videowidget.h"

class CELLINKWIDGETS_EXPORT VideoWidgetPlugin : public QObject, public QDesignerCustomWidgetInterface
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)
public:
    VideoWidgetPlugin(QObject *parent = 0);

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

VideoWidgetPlugin::VideoWidgetPlugin(QObject *parent) :
    QObject(parent)
{
    m_initialized = false;
}

void VideoWidgetPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here
    m_initialized = true;
}

bool VideoWidgetPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *VideoWidgetPlugin::createWidget(QWidget *parent)
{
    return new VideoWidget(parent);
}

QString VideoWidgetPlugin::name() const
{
    return QStringLiteral("VideoWidget");
}

QString VideoWidgetPlugin::group() const
{
    return QStringLiteral("Cellink Widgets");
}

QIcon VideoWidgetPlugin::icon() const
{
    return QIcon();
}

QString VideoWidgetPlugin::toolTip() const
{
    return QStringLiteral("");
}

QString VideoWidgetPlugin::whatsThis() const
{
    return QStringLiteral("");
}

bool VideoWidgetPlugin::isContainer() const
{
    return false;
}

QString VideoWidgetPlugin::domXml() const
{
    return QStringLiteral("<widget class=\"VideoWidget\" name=\"videoWidget\">\n</widget>\n");
}

QString VideoWidgetPlugin::includeFile() const
{
    return QStringLiteral("cellinkwidgets/videowidget.h");
}

#include "videowidgetplugin.moc"
