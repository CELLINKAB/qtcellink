#include "cellinkwidgets_stable.h"
#include "cellinkwidgets_global.h"

#include "cellinkwidgets/spinbox.h"

class SpinBoxPlugin : public QObject, public QDesignerCustomWidgetInterface
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)


public:
    explicit SpinBoxPlugin(QObject *parent = 0);
    ~SpinBoxPlugin() override;

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

SpinBoxPlugin::SpinBoxPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void SpinBoxPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

SpinBoxPlugin::~SpinBoxPlugin() = default;

bool SpinBoxPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *SpinBoxPlugin::createWidget(QWidget *parent)
{
    return new SpinBox(parent);
}

QString SpinBoxPlugin::name() const
{
    return QStringLiteral("SpinBox");
}

QString SpinBoxPlugin::group() const
{
    return QStringLiteral("Cellink Widgets");
}

QIcon SpinBoxPlugin::icon() const
{
    return QIcon();
}

QString SpinBoxPlugin::toolTip() const
{
    return QStringLiteral("");
}

QString SpinBoxPlugin::whatsThis() const
{
    return QStringLiteral("");
}

bool SpinBoxPlugin::isContainer() const
{
    return false;
}

QString SpinBoxPlugin::domXml() const
{
    return QStringLiteral("<widget class=\"SpinBox\" name=\"spinBox\">\n</widget>\n");
}

QString SpinBoxPlugin::includeFile() const
{
    return QStringLiteral("cellinkwidgets/spinbox.h");
}

#include "spinboxplugin.moc"
