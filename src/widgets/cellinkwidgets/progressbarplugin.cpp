#include "cellinkwidgets_stable.h"
#include "cellinkwidgets_global.h"

#include "cellinkwidgets/progressbar.h"


class ProgressBarPlugin : public QObject, public QDesignerCustomWidgetInterface
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
    ProgressBarPlugin(QObject *parent = 0);

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

ProgressBarPlugin::ProgressBarPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void ProgressBarPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool ProgressBarPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *ProgressBarPlugin::createWidget(QWidget *parent)
{
    return new ProgressBar(parent);
}

QString ProgressBarPlugin::name() const
{
    return QStringLiteral("ProgressBar");
}

QString ProgressBarPlugin::group() const
{
    return QStringLiteral("Cellink Widgets");
}

QIcon ProgressBarPlugin::icon() const
{
    return QIcon();
}

QString ProgressBarPlugin::toolTip() const
{
    return QStringLiteral("");
}

QString ProgressBarPlugin::whatsThis() const
{
    return QStringLiteral("");
}

bool ProgressBarPlugin::isContainer() const
{
    return false;
}

QString ProgressBarPlugin::domXml() const
{
    return QStringLiteral("<widget class=\"ProgressBar\" name=\"progressBar\">\n</widget>\n");
}

QString ProgressBarPlugin::includeFile() const
{
    return QStringLiteral("cellinkwidgets/progressbar.h");
}

#include "progressbarplugin.moc"
