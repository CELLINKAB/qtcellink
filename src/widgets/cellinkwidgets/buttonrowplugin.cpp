#include "cellinkwidgets_stable.h"
#include "cellinkwidgets_global.h"

#include "cellinkwidgets/buttonrow.h"

class ButtonRowPlugin : public QObject, public QDesignerCustomWidgetInterface
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
    ButtonRowPlugin(QObject *parent = 0);

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


ButtonRowPlugin::ButtonRowPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void ButtonRowPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool ButtonRowPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *ButtonRowPlugin::createWidget(QWidget *parent)
{
    auto w = new ButtonRow(parent);
    w->addButtons({"Foo", "Bar"});
    return w;
}

QString ButtonRowPlugin::name() const
{
    return QStringLiteral("ButtonRow");
}

QString ButtonRowPlugin::group() const
{
    return QStringLiteral("Cellink Widgets");
}

QIcon ButtonRowPlugin::icon() const
{
    return QIcon();
}

QString ButtonRowPlugin::toolTip() const
{
    return QStringLiteral("");
}

QString ButtonRowPlugin::whatsThis() const
{
    return QStringLiteral("");
}

bool ButtonRowPlugin::isContainer() const
{
    return false;
}

QString ButtonRowPlugin::domXml() const
{
    return QStringLiteral("<widget class=\"ButtonRow\" name=\"buttonRow\">\n</widget>\n");
}

QString ButtonRowPlugin::includeFile() const
{
    return QStringLiteral("cellinkwidgets/buttonrow.h");
}


#include "buttonrowplugin.moc"
