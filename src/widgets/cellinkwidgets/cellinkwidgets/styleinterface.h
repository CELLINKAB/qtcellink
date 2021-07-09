#ifndef STYLEINTERFACE_H
#define STYLEINTERFACE_H

#include "cellinkwidgets_global.h"

#include <QtCore/qnamespace.h>
#include <QtCore/QDebug>
#include <QtCore/QMetaEnum>

class QGraphicsDropShadowEffect;

namespace Style {

#if (QT_VERSION >= QT_VERSION_CHECK(5, 14, 0))
Q_NAMESPACE_EXPORT(CELLINKWIDGETS_EXPORT);
#else
 #ifndef Q_MOC_RUN
  #undef Q_NAMESPACE
  // literal impl of Q_NAMESPACE_EXPORT from Qt 5.14
  #define Q_NAMESPACE extern CELLINKWIDGETS_EXPORT const QMetaObject staticMetaObject; QT_ANNOTATE_CLASS(qt_qnamespace, "");
 #endif
Q_NAMESPACE
#endif


enum class Shadow {
    None = -1,
    Default = 0,
    Large,
};

Q_ENUM_NS(Shadow)

}

class CELLINKWIDGETS_EXPORT IStyle
{
public:
    [[nodiscard]] virtual QGraphicsDropShadowEffect* createShadowEffect(Style::Shadow shadowType = Style::Shadow::Default, QWidget* parent = nullptr) const = 0;

    virtual ~IStyle() = default;
};

Q_DECLARE_INTERFACE(IStyle, "com.cellink.cellinkwidgets.IStyle");

inline QDebug& operator<<(QDebug& debug, Style::Shadow value) {
    static const auto metaEnum = QMetaEnum::fromType<Style::Shadow>();
    return debug << metaEnum.valueToKey(int(value));
}

#endif // STYLEINTERFACE_H
