#include "cellinkwidgets_stable.h"
#include "cellinkwidgets_global.h"

#include "cellinkwidgets/numberoffsetwidget.h"


class NumberOffsetWidgetPlugin : public QObject, public QDesignerCustomWidgetInterface
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
    NumberOffsetWidgetPlugin(QObject *parent = 0);

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

NumberOffsetWidgetPlugin::NumberOffsetWidgetPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void NumberOffsetWidgetPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool NumberOffsetWidgetPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *NumberOffsetWidgetPlugin::createWidget(QWidget *parent)
{
    return new NumberOffsetWidget(parent);
}

QString NumberOffsetWidgetPlugin::name() const
{
    return QStringLiteral("NumberOffsetWidget");
}

QString NumberOffsetWidgetPlugin::group() const
{
    return QStringLiteral("Cellink Widgets");
}

QIcon NumberOffsetWidgetPlugin::icon() const
{
    return QIcon();
}

QString NumberOffsetWidgetPlugin::toolTip() const
{
    return QStringLiteral("");
}

QString NumberOffsetWidgetPlugin::whatsThis() const
{
    return QStringLiteral("");
}

bool NumberOffsetWidgetPlugin::isContainer() const
{
    return false;
}

QString NumberOffsetWidgetPlugin::domXml() const
{
    return QStringLiteral("<widget class=\"NumberOffsetWidget\" name=\"numberOffsetWidget\">\n</widget>\n");
}

QString NumberOffsetWidgetPlugin::includeFile() const
{
    return QStringLiteral("cellinkwidgets/numberoffsetwidget.h");
}

#include "numberoffsetwidgetplugin.moc"
