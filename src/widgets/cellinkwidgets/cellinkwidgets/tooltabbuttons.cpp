#include "cellinkwidgets_stable.h"
#include "tooltabbuttons.h"

#include "ui_tooltabbuttons.h"
#include "ui_tooltabbutton.h"
#include "misc.h"
#include "tools/tool2.h"

Q_LOGGING_CATEGORY(lcTtb, "cellink.ui.ToolTabButtons", QtDebugMsg);

namespace
{
    constexpr auto PRINTHEAD_ICON_PATH = ":/images/printerutilities/head_tab/%1/%2.svg";
    constexpr auto PRINTHEAD_DEFAULT_IMAGE = "printheads.svg";
    constexpr auto DISABLED_ICON_SUBPATH = "disabled";
    constexpr auto ACTIVE_ICON_SUBPATH = "selected";
    constexpr auto INACTIVE_ICON_SUBPATH = "completed";
    constexpr auto ENABLED_ICON_SUBPATH = "enabled";
    constexpr auto LABEL_NAME = "Tool %0";

    const QColor INACTIVE_LABEL_COLOR = {145, 178, 228}; // color taken from icon image so it is the same

    auto getIconPath(ToolTabButton::State state, QString imagePath, QString imageName)
    {
        const auto iconPath = imagePath.isEmpty() ? QString(PRINTHEAD_ICON_PATH) : imagePath;
        const auto iconName = imageName.isEmpty() ? QString(PRINTHEAD_DEFAULT_IMAGE) : imageName;

        switch (state) {
        case ToolTabButton::State::Active:
            return iconPath.arg(ACTIVE_ICON_SUBPATH, iconName);
        case ToolTabButton::State::Inactive:
            return iconPath.arg(INACTIVE_ICON_SUBPATH, iconName);
        case ToolTabButton::State::Enabled:
            return iconPath.arg(ENABLED_ICON_SUBPATH, iconName);
        case ToolTabButton::State::Disabled:
        default:
            return iconPath.arg(DISABLED_ICON_SUBPATH, iconName);
        }
    }

    QColor getLabelColor(const QPalette& palette, ToolTabButton::State state)
    {
        switch (state) {
        case ToolTabButton::State::Active:
            return palette.color(QPalette::Highlight);
        case ToolTabButton::State::Inactive:
            return INACTIVE_LABEL_COLOR;
        case ToolTabButton::State::Enabled:
            return palette.color(QPalette::ButtonText);
        case ToolTabButton::State::Disabled:
        default:
            return palette.color(QPalette::Button);
        }
    }
}

class ToolTabButtonPrivate
{
public:

    void setState(ToolTabButton::State state)
    {
        m_state = state;
        m_ui.icon->load(getIconPath(state, m_imagePath, m_imageName).replace(".svg.svg", ".svg"));
        auto labelPalette = m_ui.label->palette();
        labelPalette.setColor(QPalette::WindowText, getLabelColor(labelPalette, state));
        m_ui.label->setPalette(labelPalette);
    }

    const int m_toolPosition;

    Ui::ToolTabButton m_ui{};
    ToolTabButton::State m_state{ToolTabButton::State::None};
    bool m_selected = false;
    QString m_imagePath{};
    QString m_imageName{};
};

ToolTabButton::ToolTabButton(int toolPosition, State state, const QString& labelName,
                             QString imagePath, const QString& imageName, QWidget *parent) :
    QWidget(parent),
    d_ptr(new ToolTabButtonPrivate{toolPosition})
{
    Q_D(ToolTabButton);


    d->m_ui.setupUi(this);
    d->m_imagePath = imagePath;
    d->m_imageName = imageName;

    auto text = (labelName.isEmpty() ? tr(LABEL_NAME) : labelName);
    if (QRegularExpression("%\\d+").match(text).hasMatch()) {
        text = text.arg(toolPosition);
    }
    d->m_ui.label->setText(text);
    setState(state);
    setFixedSize(70, 70);
    setObjectName(QString("ToolTabButton pos %1").arg(toolPosition));
    setProperty("position", toolPosition);
}

ToolTabButton::~ToolTabButton() = default;

void ToolTabButton::mouseReleaseEvent(QMouseEvent *event)
{
    QWidget::mouseReleaseEvent(event);
    emit clicked();
}

void ToolTabButton::setSelected(bool selected)
{
    Q_D(ToolTabButton);

    if(d->m_selected != selected) {
        d->m_selected = selected;
        emit selectedChanged(selected);
    }
}

bool ToolTabButton::isSelected() const
{
    return d_ptr->m_selected;
}

ToolTabButton::State ToolTabButton::state() const
{
    return d_ptr->m_state;
}

void ToolTabButton::setState(State state)
{
    Q_D(ToolTabButton);    

    if (d->m_state == state)
        return;

    d->setState(state);
    setEnabled(state != State::Disabled);
    emit stateChanged(state);
}

int ToolTabButton::position() const
{
    return d_ptr->m_toolPosition;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class ToolTabButtonsPrivate
{
public:
    std::optional<ToolTabButton*> getSelectedButton()
    {
        const auto found = std::find_if(std::cbegin(m_buttons), std::cend(m_buttons), [](const auto button){
            return button->isSelected();
        });

        return found != std::cend(m_buttons) ? std::optional(*found) : std::nullopt;
    }

    bool selectNextButton()
    {
        constexpr auto DEBUG_BUTTONS = false;

        if (m_buttons.empty()) {
            if constexpr (DEBUG_BUTTONS)
                qCInfo(lcTtb) << "No buttons?!";

            return false;
        }

        const auto it = std::find_if(std::begin(m_buttons), std::end(m_buttons), [](const auto b) {
            return b->isSelected();
        });

        if (it == std::cend(m_buttons)) {
            if constexpr (DEBUG_BUTTONS)
                qCInfo(lcTtb) << "Select first" << m_buttons.front();

            m_buttons.front()->setSelected(true);
            return true;
        }

        const auto next = std::next(it);
        if (next != std::cend(m_buttons)) {
            if constexpr (DEBUG_BUTTONS)
                qCInfo(lcTtb) << "Select next" << *next;

            (*next)->setSelected(true);
            return true;
        }

        if constexpr (DEBUG_BUTTONS)
            qCInfo(lcTtb) << "At end!";

        return false;
    }


    Ui::ToolTabButtons m_ui{};
    QVector<ToolTabButton*> m_buttons;
    bool m_underlined{true};
};

ToolTabButtons::ToolTabButtons(QWidget *parent) :
    QWidget(parent),
    d_ptr(new ToolTabButtonsPrivate)
{
    Q_D(ToolTabButtons);

    d->m_ui.setupUi(this);
}

ToolTabButtons::~ToolTabButtons() = default;

void ToolTabButtons::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    const auto rectangle = rect();
    QPen pen(palette().color(QPalette::Button), 5);
    painter.setPen(pen);

    Q_D(ToolTabButtons);

    if (!d->m_underlined) {
        return;
    }

    painter.drawLine(rectangle.bottomLeft(), rectangle.bottomRight());

    if (const auto maybeButton = d->getSelectedButton()) {
        const auto button = *maybeButton;
        const auto position = button->pos().x();
        const auto width = button->width();
        pen.setColor(palette().color(QPalette::Highlight));
        painter.setPen(pen);
        painter.drawLine(position, rectangle.bottom(), position + width, rectangle.bottom());
    }
}

ToolTabButton* ToolTabButtons::addButton(const ToolHead* tool, const ToolTabButton::State state,
                                         const QString labelName,
                                         const QString imagePath, QString imageName)
{
    auto toolPosition = tool->position();
    if (imageName.isEmpty()) {
        // TODO: Add image filename as separate property to JSON / ToolInfo2 or via plugin
        imageName = tool->info().productName()
                .replace("HD Camera", "Camera")
                .replace("Syringe Pump 2.5ml", "Syringe Pump")
                .toLower()
                .replace(" ", "_");
    }

    return addButton(toolPosition, state, labelName, imagePath, imageName);
}

ToolTabButton* ToolTabButtons::addButton(const int toolPosition, const ToolTabButton::State state,
                                         const QString labelName,
                                         const QString imagePath, const QString imageName)
{
    Q_D(ToolTabButtons);

    const auto button = new ToolTabButton(toolPosition, state, labelName, imagePath, imageName, this);
    auto index = d->m_ui.buttonsContainer->count();

    for (auto i = 0; i < d->m_ui.buttonsContainer->count(); ++i) {
        if (auto ttb = safe_cast<ToolTabButton*>(d->m_ui.buttonsContainer->itemAt(i)->widget())) {
            if (toolPosition < ttb->position()) {
                index = i;
                break;
            }
        }
    }

    d->m_ui.buttonsContainer->insertWidget(index, button);
    d->m_buttons.insert(d->m_buttons.begin() + index, button);
    refreshButtonWidth();
    connect(button, &ToolTabButton::selectedChanged, [this, d, button](bool selected) {
        if (!selected) {
            qCInfo(lcTtb) << "Button" << button << "deselected.";
            return;
        }

        qCInfo(lcTtb) << "Button" << button << "selected. Deselecting others.";

        // deselect all other buttons
        for (auto b : d->m_buttons) {
            if (b != button) {
                b->setSelected(false);
            }
        }

        update();
    });

    return button;
}

void ToolTabButtons::removeButton(int position)
{
    Q_D(ToolTabButtons);
    const auto it = std::find_if(d->m_buttons.begin(), d->m_buttons.end(), [position](auto button) {
        return button->position() == position;
    });

    if (it == d->m_buttons.end()) {
        qWarning() << "No button at pos" << position << "found";
        return;
    }

    const auto button = *it;
    d->m_buttons.erase(it);
    button->setParent(nullptr);
    button->deleteLater();

    if (button->state() == ToolTabButton::State::Active) {
        selectNextButton();
    }
    refreshButtonWidth();
}

bool ToolTabButtons::selectNextButton()
{
    return d_ptr->selectNextButton();
}

int ToolTabButtons::buttonCount()
{
    Q_D(ToolTabButtons);
    return d->m_buttons.count();
}

void ToolTabButtons::setUnderlined(bool underlined)
{
    Misc::updateProperty(this, underlined, d_ptr->m_underlined, &ToolTabButtons::underlinedChanged);
}

bool ToolTabButtons::isUnderlined() const
{
    return d_ptr->m_underlined;
}

void ToolTabButtons::refreshButtonWidth()
{
    Q_D(ToolTabButtons);

    auto dynamicButtonWidth = 0;
    if (d->m_ui.buttonsContainer->count() > 4){
       dynamicButtonWidth = 60;
    } else {
       dynamicButtonWidth = 70;
    }

    for (auto i = 0; i < d->m_ui.buttonsContainer->count(); ++i) {
        if (auto ttb = safe_cast<ToolTabButton*>(d->m_ui.buttonsContainer->itemAt(i)->widget())) {
            ttb->setFixedSize(dynamicButtonWidth, 70);
        }
    }

}
