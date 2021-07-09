#include "cellinkwidgets_stable.h"
#include "cellinkwidgets_global.h"

#include "cellinkwidgets/doublespinbox.h"

class DoubleSpinBoxPlugin : public QObject, public QDesignerCustomWidgetInterface
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)


public:
    explicit DoubleSpinBoxPlugin(QObject *parent = 0);
    ~DoubleSpinBoxPlugin() override;

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

DoubleSpinBoxPlugin::DoubleSpinBoxPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void DoubleSpinBoxPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

DoubleSpinBoxPlugin::~DoubleSpinBoxPlugin() = default;

bool DoubleSpinBoxPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *DoubleSpinBoxPlugin::createWidget(QWidget *parent)
{
    return new DoubleSpinBox(parent);
}

QString DoubleSpinBoxPlugin::name() const
{
    return QStringLiteral("SpinBox");
}

QString DoubleSpinBoxPlugin::group() const
{
    return QStringLiteral("Cellink Widgets");
}

QIcon DoubleSpinBoxPlugin::icon() const
{
    return QIcon();
}

QString DoubleSpinBoxPlugin::toolTip() const
{
    return QStringLiteral("");
}

QString DoubleSpinBoxPlugin::whatsThis() const
{
    return QStringLiteral("");
}

bool DoubleSpinBoxPlugin::isContainer() const
{
    return false;
}

QString DoubleSpinBoxPlugin::domXml() const
{
    return QStringLiteral("<widget class=\"DoubleSpinBox\" name=\"doubleSpinBox\">\n</widget>\n");
}

QString DoubleSpinBoxPlugin::includeFile() const
{
    return QStringLiteral("cellinkwidgets/doublespinbox.h");
}

#include "doublespinboxplugin.moc"
