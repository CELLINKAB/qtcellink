#ifndef TOOLTABBUTTONS_H
#define TOOLTABBUTTONS_H

#include "cellinkwidgets_global.h"

#include <QWidget>
#include <memory>

class ToolTabButtonPrivate;
class ToolHead;

class CELLINKWIDGETS_EXPORT ToolTabButton : public QWidget
{
    Q_OBJECT
public:
    enum class State
    {
        Active,
        Inactive,
        Disabled,
        Enabled,
        None
    };
    Q_ENUM(State);

    ToolTabButton(int toolPosition, State state,
                  const QString& labelName = {},
                  QString imagePath = {},
                  const QString& imageName = {},
                  QWidget *parent = nullptr);
    ~ToolTabButton() override;

    void setSelected(bool selected);
    [[nodiscard]] bool isSelected() const;

    void setState(State state);
    [[nodiscard]] State state() const;

    [[nodiscard]] int position() const;

public slots:
    void click() { emit clicked(); }

signals:
    void selectedChanged(bool selected);
    void clicked();
    void stateChanged(State state);

protected:
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    Q_DECLARE_PRIVATE(ToolTabButton);
    std::unique_ptr<ToolTabButtonPrivate> d_ptr;
};

class ToolTabButtonsPrivate;

class CELLINKWIDGETS_EXPORT ToolTabButtons : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(bool underlined READ isUnderlined WRITE setUnderlined NOTIFY underlinedChanged FINAL)

public:
    explicit ToolTabButtons(QWidget *parent = nullptr);
    ~ToolTabButtons() override;

    [[nodiscard]] ToolTabButton* addButton(const ToolHead* toolHead,
                                           const ToolTabButton::State state,
                                           const QString labelName = {},
                                           const QString imagePath = {},
                                           QString imageName = {});

    [[nodiscard]] ToolTabButton* addButton(const int toolPosition,
                                           const ToolTabButton::State state,
                                           const QString labelName = {},
                                           const QString imagePath = {},
                                           const QString imageName = {});

    void removeButton(int position);

    bool selectNextButton();
    [[nodiscard]] int buttonCount();

    void setUnderlined(bool underlined);
    [[nodiscard]] bool isUnderlined() const;

    void refreshButtonWidth();

signals:
    void underlinedChanged(bool underlined);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    Q_DECLARE_PRIVATE(ToolTabButtons);
    std::unique_ptr<ToolTabButtonsPrivate> d_ptr;
};

#endif // TOOLTABBUTTONS_H
