#include "cellinkwidgets_stable.h"
#include "cellinkwidgets_global.h"

namespace {

QObject* createQObjectFromClassName(const char* className, QObject* parent)
{
    const auto type = QMetaType::type(className);
    const auto metatype = QMetaType(type);
    if (!metatype.isValid()) {
        qCritical() << className << "is not a registered QMetaType class ?!";
        return nullptr;
    }

    const auto metaobject = metatype.metaObject();
    if (!metaobject) {
        qCritical() << className << "is not a QObject class?!";
        return nullptr;
    }

    const auto object = metaobject->newInstance(Q_ARG(QObject*, parent));
    if (!object) {
        qCritical() << className << "needs Q_INVOKABLE constructor!";
        return nullptr;
    }

    return object;
}

}

class CELLINKWIDGETS_EXPORT CellinkWidgetsPlugin :
        public QObject,
        public QDesignerCustomWidgetCollectionInterface
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetCollectionInterface)
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QDesignerCustomWidgetCollectionInterface")

public:
    explicit CellinkWidgetsPlugin(QObject *parent = nullptr) :
        QObject(parent)
    {
        for (auto pluginClass : {
             "ToggleSwitchPlugin", "ButtonRowPlugin",
             "CollapseBoxPlugin", "SpinBoxPlugin",
             "DoubleSpinBoxPlugin", "Qt3DWidgetPlugin",
             "PaperPlugin"})
        {
            const auto object = createQObjectFromClassName(pluginClass, this);
            if (!object) {
                continue;
            }

            const auto plugin = qobject_cast<QDesignerCustomWidgetInterface*>(object);
            if (!plugin) {
                qCritical() << object << "was not a QDesignerCustomWidgetInterface";
                delete object;
                continue;
            }

            m_widgets.append(plugin);
        }
    }

    QList<QDesignerCustomWidgetInterface*> customWidgets() const override
    {
        return m_widgets;
    }

private:
    QList<QDesignerCustomWidgetInterface*> m_widgets;
};

#include "cellinkwidgetsplugin.moc"
