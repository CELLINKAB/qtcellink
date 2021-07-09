#ifndef COLLAPSEBOX_H
#define COLLAPSEBOX_H

#include "cellinkwidgets_global.h"
#include <QGroupBox>
#include <memory>

class CollapseBoxPrivate;

/**
 * @brief A QGroupBox whose contents is hidden when it is not checked
 *
 * It is also checkable (but not checked) and flat by default.
 */
class CELLINKWIDGETS_EXPORT CollapseBox : public QGroupBox
{
    Q_OBJECT
    Q_PROPERTY(bool collapsed READ isCollapsed WRITE setCollapsed NOTIFY collapsedChanged)
    Q_PROPERTY(CheckboxType checkboxType READ checkboxType WRITE setCheckboxType NOTIFY checkboxTypeChanged)
    Q_PROPERTY(bool collapseDisablesFeature READ collapseDisablesFeature WRITE setCollapseDisablesFeature FINAL DESIGNABLE true)

public:
    enum CheckboxType
    {
        Toggle,
        Arrow
    };

    explicit CollapseBox(QWidget *parent = nullptr);
    ~CollapseBox() override;

    [[nodiscard]] QSize minimumSizeHint() const override;
    [[nodiscard]] bool isCollapsed() const { return !isChecked(); }
    [[nodiscard]] bool collapseDisablesFeature() const;

    [[nodiscard]] CheckboxType checkboxType() const;

public slots:
    void setCollapsed(bool value) { setChecked(!value); }
    void setCheckboxType(CheckboxType value);
    void setCollapseDisablesFeature(bool disable);

signals:
    void collapsedChanged(bool value);
    void checkboxTypeChanged(CheckboxType value);

protected:
    void childEvent(QChildEvent* event) override;
    void showEvent(QShowEvent* event) override;

private:
    Q_DECLARE_PRIVATE(CollapseBox);
    std::unique_ptr<CollapseBoxPrivate> d_ptr;
};

#endif // COLLAPSEBOX_H
