/****************************************************************************
**
** Copyright (C) 2020 CELLINK AB <info@cellink.com>
** Copyright (C) 2017 The Qt Company Ltd.
**
** This file is part of QtCellink (based on the Qt Quick Templates 2 module of Qt).
**
** QtCellink is free software: you can redistribute it and/or modify it
** under the terms of the GNU Lesser General Public License as published
** by the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** QtCellink is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
** GNU Lesser General Public License for more details.
**
** You should have received a copy of the GNU Lesser General Public License
** along with QtCellink. If not, see <https://www.gnu.org/licenses/>.
**
****************************************************************************/

#include "doublespinbox.h"

#include <QtGui/qguiapplication.h>
#include <QtGui/qstylehints.h>
#include <QtQml/private/qqmlengine_p.h>
#include <QtQml/private/qqmllocale_p.h>
#include <QtQml/qqmlinfo.h>
#include <QtQuick/private/qquicktextinput_p.h>
#include <QtQuickTemplates2/private/qquickcontrol_p_p.h>

// copied from qabstractbutton.cpp
static const int AUTO_REPEAT_DELAY = 300;
static const int AUTO_REPEAT_INTERVAL = 100;

class DoubleSpinBoxPrivate : public QQuickControlPrivate
{
    Q_DECLARE_PUBLIC(DoubleSpinBox)

public:
    qreal boundValue(qreal value, bool wrap) const;
    void updateValue();
    bool setValue(qreal value, bool wrap, bool modified);
    bool stepBy(qreal steps, bool modified);
    void stepUp(bool modified);
    void stepDown(bool modified);
    void pageStepUp(bool modified);
    void pageStepDown(bool modified);

    qreal effectiveStepSize(qreal step) const;

    void updateDisplayText();
    void setDisplayText(const QString& displayText);

    bool upEnabled() const;
    void updateUpEnabled();
    bool downEnabled() const;
    void updateDownEnabled();
    void updateHover(const QPointF& pos);

    void startRepeatDelay();
    void startPressRepeat();
    void stopPressRepeat();

    void accept();

    void handlePress(const QPointF& point) override;
    void handleMove(const QPointF& point) override;
    void handleRelease(const QPointF& point) override;
    void handleUngrab() override;

    bool editable = false;
    bool wrap = false;
    bool hasDisplayText = false;
    qreal from = 0;
    qreal to = 100;
    qreal value = 0;
    qreal stepSize = 1;
    qreal pageStepSize = 10;
    int delayTimer = 0;
    int repeatTimer = 0;
    int decimals = 2;
    QString prefix;
    QString suffix;
    QString displayText;
    DoubleSpinButton* up = nullptr;
    DoubleSpinButton* down = nullptr;
    QValidator* validator = nullptr;
    mutable QJSValue textFromValue;
    mutable QJSValue valueFromText;
    Qt::InputMethodHints inputMethodHints = Qt::ImhDigitsOnly | Qt::ImhNoTextHandles;
};

class DoubleSpinButtonPrivate : public QObjectPrivate
{
    Q_DECLARE_PUBLIC(DoubleSpinButton)

public:
    static DoubleSpinButtonPrivate* get(DoubleSpinButton* button) { return button->d_func(); }

    bool pressed = false;
    bool hovered = false;
    QQuickItem* indicator = nullptr;
};

qreal DoubleSpinBoxPrivate::boundValue(qreal value, bool wrap) const
{
    bool inverted = from > to;
    if (!wrap)
        return inverted ? qBound(to, value, from) : qBound(from, value, to);

    qreal f = inverted ? to : from;
    qreal t = inverted ? from : to;
    if (value < f)
        value = t;
    else if (value > t)
        value = f;

    return value;
}

void DoubleSpinBoxPrivate::updateValue()
{
    Q_Q(DoubleSpinBox);
    if (contentItem) {
        QVariant text = contentItem->property("text");
        if (text.isValid()) {
            qreal val = 0;
            QQmlEngine* engine = qmlEngine(q);
            if (engine && valueFromText.isCallable()) {
                QV4::ExecutionEngine* v4 = QQmlEnginePrivate::getV4Engine(engine);
                QJSValue loc(v4, QQmlLocale::wrap(v4, locale));
                val = valueFromText.call(QJSValueList() << text.toString() << loc).toInt();
            } else {
                val = locale.toDouble(text.toString());
            }

            setValue(val, /* allowWrap = */ false, /* modified = */ true);
        }
    }
}

bool DoubleSpinBoxPrivate::setValue(qreal newValue, bool allowWrap, bool modified)
{
    Q_Q(DoubleSpinBox);
    if (q->isComponentComplete())
        newValue = boundValue(newValue, allowWrap);

    updateDisplayText();

    if (value == newValue)
        return false;

    value = newValue;

    updateUpEnabled();
    updateDownEnabled();

    emit q->valueChanged();
    if (modified)
        emit q->valueModified();
    return true;
}

bool DoubleSpinBoxPrivate::stepBy(qreal steps, bool modified)
{
    return setValue(value + steps, wrap, modified);
}

void DoubleSpinBoxPrivate::stepUp(bool modified)
{
    setValue(value + effectiveStepSize(stepSize), wrap, modified);
}

void DoubleSpinBoxPrivate::stepDown(bool modified)
{
    setValue(value - effectiveStepSize(stepSize), wrap, modified);
}

void DoubleSpinBoxPrivate::pageStepUp(bool modified)
{
    setValue(value + effectiveStepSize(pageStepSize), wrap, modified);
}

void DoubleSpinBoxPrivate::pageStepDown(bool modified)
{
    setValue(value - effectiveStepSize(pageStepSize), wrap, modified);
}

qreal DoubleSpinBoxPrivate::effectiveStepSize(qreal step) const
{
    return from > to ? -1 * step : step;
}

void DoubleSpinBoxPrivate::updateDisplayText()
{
    Q_Q(DoubleSpinBox);
    if (hasDisplayText)
        return;

    QString text;
    QQmlEngine* engine = qmlEngine(q);
    if (engine && textFromValue.isCallable()) {
        QV4::ExecutionEngine* v4 = QQmlEnginePrivate::getV4Engine(engine);
        QJSValue loc(v4, QQmlLocale::wrap(v4, locale));
        text = textFromValue.call(QJSValueList() << value << loc << decimals).toString();
    } else {
        text = locale.toString(value, 'f', decimals);
    }
    setDisplayText(text);
}

void DoubleSpinBoxPrivate::setDisplayText(const QString& text)
{
    Q_Q(DoubleSpinBox);

    displayText = text;
    emit q->displayTextChanged();
}

bool DoubleSpinBoxPrivate::upEnabled() const
{
    const QQuickItem* upIndicator = up->indicator();
    return upIndicator && upIndicator->isEnabled();
}

void DoubleSpinBoxPrivate::updateUpEnabled()
{
    QQuickItem* upIndicator = up->indicator();
    if (!upIndicator)
        return;

    upIndicator->setEnabled(wrap || (from < to ? value < to : value > to));
}

bool DoubleSpinBoxPrivate::downEnabled() const
{
    const QQuickItem* downIndicator = down->indicator();
    return downIndicator && downIndicator->isEnabled();
}

void DoubleSpinBoxPrivate::updateDownEnabled()
{
    QQuickItem* downIndicator = down->indicator();
    if (!downIndicator)
        return;

    downIndicator->setEnabled(wrap || (from < to ? value > from : value < from));
}

void DoubleSpinBoxPrivate::updateHover(const QPointF& pos)
{
    Q_Q(DoubleSpinBox);
    QQuickItem* ui = up->indicator();
    QQuickItem* di = down->indicator();
    up->setHovered(ui && ui->isEnabled() && ui->contains(q->mapToItem(ui, pos)));
    down->setHovered(di && di->isEnabled() && di->contains(q->mapToItem(di, pos)));
}

void DoubleSpinBoxPrivate::startRepeatDelay()
{
    Q_Q(DoubleSpinBox);
    stopPressRepeat();
    delayTimer = q->startTimer(AUTO_REPEAT_DELAY);
}

void DoubleSpinBoxPrivate::startPressRepeat()
{
    Q_Q(DoubleSpinBox);
    stopPressRepeat();
    repeatTimer = q->startTimer(AUTO_REPEAT_INTERVAL);
}

void DoubleSpinBoxPrivate::stopPressRepeat()
{
    Q_Q(DoubleSpinBox);
    if (delayTimer > 0) {
        q->killTimer(delayTimer);
        delayTimer = 0;
    }
    if (repeatTimer > 0) {
        q->killTimer(repeatTimer);
        repeatTimer = 0;
    }
}

void DoubleSpinBoxPrivate::accept()
{
    Q_Q(DoubleSpinBox);
    updateValue();
    emit q->accepted();
}

void DoubleSpinBoxPrivate::handlePress(const QPointF& point)
{
    Q_Q(DoubleSpinBox);
    QQuickControlPrivate::handlePress(point);
    QQuickItem* ui = up->indicator();
    QQuickItem* di = down->indicator();
    up->setPressed(ui && ui->isEnabled() && ui->contains(ui->mapFromItem(q, point)));
    down->setPressed(di && di->isEnabled() && di->contains(di->mapFromItem(q, point)));

    bool pressed = up->isPressed() || down->isPressed();
    q->setAccessibleProperty("pressed", pressed);
    if (pressed)
        startRepeatDelay();
}

void DoubleSpinBoxPrivate::handleMove(const QPointF& point)
{
    Q_Q(DoubleSpinBox);
    QQuickControlPrivate::handleMove(point);
    QQuickItem* ui = up->indicator();
    QQuickItem* di = down->indicator();
    up->setPressed(ui && ui->isEnabled() && ui->contains(ui->mapFromItem(q, point)));
    down->setPressed(di && di->isEnabled() && di->contains(di->mapFromItem(q, point)));

    bool pressed = up->isPressed() || down->isPressed();
    q->setAccessibleProperty("pressed", pressed);
    if (!pressed)
        stopPressRepeat();
}

void DoubleSpinBoxPrivate::handleRelease(const QPointF& point)
{
    Q_Q(DoubleSpinBox);
    QQuickControlPrivate::handleRelease(point);
    QQuickItem* ui = up->indicator();
    QQuickItem* di = down->indicator();

    qreal oldValue = value;
    if (up->isPressed()) {
        up->setPressed(false);
        if (repeatTimer <= 0 && ui && ui->contains(ui->mapFromItem(q, point)))
            q->increase();
    } else if (down->isPressed()) {
        down->setPressed(false);
        if (repeatTimer <= 0 && di && di->contains(di->mapFromItem(q, point)))
            q->decrease();
    }
    if (value != oldValue)
        emit q->valueModified();

    q->setAccessibleProperty("pressed", false);
    stopPressRepeat();
}

void DoubleSpinBoxPrivate::handleUngrab()
{
    Q_Q(DoubleSpinBox);
    QQuickControlPrivate::handleUngrab();
    up->setPressed(false);
    down->setPressed(false);

    q->setAccessibleProperty("pressed", false);
    stopPressRepeat();
}

DoubleSpinBox::DoubleSpinBox(QQuickItem* parent)
    : QQuickControl(*(new DoubleSpinBoxPrivate), parent)
{
    Q_D(DoubleSpinBox);
    d->up = new DoubleSpinButton(this);
    d->down = new DoubleSpinButton(this);

    setFlag(ItemIsFocusScope);
    setFiltersChildMouseEvents(true);
    setAcceptedMouseButtons(Qt::LeftButton);
#if QT_CONFIG(cursor)
    setCursor(Qt::ArrowCursor);
#endif
}

qreal DoubleSpinBox::from() const
{
    Q_D(const DoubleSpinBox);
    return d->from;
}

void DoubleSpinBox::setFrom(qreal from)
{
    Q_D(DoubleSpinBox);
    if (d->from == from)
        return;

    d->from = from;
    emit fromChanged();
    if (isComponentComplete()) {
        if (!d->setValue(d->value, /* allowWrap = */ false, /* modified = */ false)) {
            d->updateUpEnabled();
            d->updateDownEnabled();
        }
    }
}

qreal DoubleSpinBox::to() const
{
    Q_D(const DoubleSpinBox);
    return d->to;
}

void DoubleSpinBox::setTo(qreal to)
{
    Q_D(DoubleSpinBox);
    if (d->to == to)
        return;

    d->to = to;
    emit toChanged();
    if (isComponentComplete()) {
        if (!d->setValue(d->value, /* allowWrap = */ false, /* modified = */ false)) {
            d->updateUpEnabled();
            d->updateDownEnabled();
        }
    }
}

qreal DoubleSpinBox::value() const
{
    Q_D(const DoubleSpinBox);
    return d->value;
}

void DoubleSpinBox::setValue(qreal value)
{
    Q_D(DoubleSpinBox);
    d->setValue(value, /* allowWrap = */ false, /* modified = */ false);
}

qreal DoubleSpinBox::stepSize() const
{
    Q_D(const DoubleSpinBox);
    return d->stepSize;
}

void DoubleSpinBox::setStepSize(qreal step)
{
    Q_D(DoubleSpinBox);
    if (d->stepSize == step)
        return;

    d->stepSize = step;
    emit stepSizeChanged();
}

qreal DoubleSpinBox::pageStepSize() const
{
    Q_D(const DoubleSpinBox);
    return d->pageStepSize;
}

void DoubleSpinBox::setPageStepSize(qreal step)
{
    Q_D(DoubleSpinBox);
    if (d->pageStepSize == step)
        return;

    d->pageStepSize = step;
    emit pageStepSizeChanged();
}

bool DoubleSpinBox::isEditable() const
{
    Q_D(const DoubleSpinBox);
    return d->editable;
}

void DoubleSpinBox::setEditable(bool editable)
{
    Q_D(DoubleSpinBox);
    if (d->editable == editable)
        return;

#if QT_CONFIG(cursor)
    if (d->contentItem) {
        if (editable)
            d->contentItem->setCursor(Qt::IBeamCursor);
        else
            d->contentItem->unsetCursor();
    }
#endif

    d->editable = editable;
    setAccessibleProperty("editable", editable);
    emit editableChanged();
}

QValidator* DoubleSpinBox::validator() const
{
    Q_D(const DoubleSpinBox);
    return d->validator;
}

void DoubleSpinBox::setValidator(QValidator* validator)
{
    Q_D(DoubleSpinBox);
    if (d->validator == validator)
        return;

    d->validator = validator;
    if (QQuickTextInput* textInput = qobject_cast<QQuickTextInput*>(contentItem()))
        textInput->setValidator(validator);

    emit validatorChanged();
}

QJSValue DoubleSpinBox::textFromValue() const
{
    Q_D(const DoubleSpinBox);
    if (!d->textFromValue.isCallable()) {
        QQmlEngine* engine = qmlEngine(this);
        if (engine)
            d->textFromValue = engine->evaluate(
                QStringLiteral("(function(value, locale, decimals) { return "
                               "Number(value).toLocaleString(locale, 'f', decimals); })"));
    }
    return d->textFromValue;
}

void DoubleSpinBox::setTextFromValue(const QJSValue& callback)
{
    Q_D(DoubleSpinBox);
    if (!callback.isCallable()) {
        qmlWarning(this) << "textFromValue must be a callable function";
        return;
    }
    d->textFromValue = callback;
    emit textFromValueChanged();
}

QJSValue DoubleSpinBox::valueFromText() const
{
    Q_D(const DoubleSpinBox);
    if (!d->valueFromText.isCallable()) {
        QQmlEngine* engine = qmlEngine(this);
        if (engine)
            d->valueFromText = engine->evaluate(QStringLiteral(
                "function(text, locale) { return Number.fromLocaleString(locale, text); }"));
    }
    return d->valueFromText;
}

void DoubleSpinBox::setValueFromText(const QJSValue& callback)
{
    Q_D(DoubleSpinBox);
    if (!callback.isCallable()) {
        qmlWarning(this) << "valueFromText must be a callable function";
        return;
    }
    d->valueFromText = callback;
    emit valueFromTextChanged();
}

DoubleSpinButton* DoubleSpinBox::up() const
{
    Q_D(const DoubleSpinBox);
    return d->up;
}

DoubleSpinButton* DoubleSpinBox::down() const
{
    Q_D(const DoubleSpinBox);
    return d->down;
}

Qt::InputMethodHints DoubleSpinBox::inputMethodHints() const
{
    Q_D(const DoubleSpinBox);
    return d->inputMethodHints;
}

void DoubleSpinBox::setInputMethodHints(Qt::InputMethodHints hints)
{
    Q_D(DoubleSpinBox);
    if (d->inputMethodHints == hints)
        return;

    d->inputMethodHints = hints;
    emit inputMethodHintsChanged();
}

bool DoubleSpinBox::isInputMethodComposing() const
{
    Q_D(const DoubleSpinBox);
    return d->contentItem && d->contentItem->property("inputMethodComposing").toBool();
}

bool DoubleSpinBox::wrap() const
{
    Q_D(const DoubleSpinBox);
    return d->wrap;
}

void DoubleSpinBox::setWrap(bool wrap)
{
    Q_D(DoubleSpinBox);
    if (d->wrap == wrap)
        return;

    d->wrap = wrap;
    if (d->value == d->from || d->value == d->to) {
        d->updateUpEnabled();
        d->updateDownEnabled();
    }
    emit wrapChanged();
}

QString DoubleSpinBox::displayText() const
{
    Q_D(const DoubleSpinBox);
    return d->displayText;
}

void DoubleSpinBox::setDisplayText(const QString& text)
{
    Q_D(DoubleSpinBox);
    d->hasDisplayText = true;
    d->setDisplayText(text);
}

void DoubleSpinBox::resetDisplayText()
{
    Q_D(DoubleSpinBox);
    if (!d->hasDisplayText)
        return;

    d->hasDisplayText = false;
    d->updateDisplayText();
}

int DoubleSpinBox::decimals() const
{
    Q_D(const DoubleSpinBox);
    return d->decimals;
}

void DoubleSpinBox::setDecimals(int decimals)
{
    Q_D(DoubleSpinBox);
    if (d->decimals == decimals)
        return;

    d->decimals = decimals;
    d->updateDisplayText();
    emit decimalsChanged();
}

QString DoubleSpinBox::prefix() const
{
    Q_D(const DoubleSpinBox);
    return d->prefix;
}

void DoubleSpinBox::setPrefix(const QString& prefix)
{
    Q_D(DoubleSpinBox);
    if (d->prefix == prefix)
        return;

    d->prefix = prefix;
    emit prefixChanged();
}

QString DoubleSpinBox::suffix() const
{
    Q_D(const DoubleSpinBox);
    return d->suffix;
}

void DoubleSpinBox::setSuffix(const QString& suffix)
{
    Q_D(DoubleSpinBox);
    if (d->suffix == suffix)
        return;

    d->suffix = suffix;
    emit suffixChanged();
}

void DoubleSpinBox::increase()
{
    Q_D(DoubleSpinBox);
    d->stepUp(false);
}

void DoubleSpinBox::decrease()
{
    Q_D(DoubleSpinBox);
    d->stepDown(false);
}

void DoubleSpinBox::focusInEvent(QFocusEvent* event)
{
    Q_D(DoubleSpinBox);
    QQuickControl::focusInEvent(event);

    // When an editable SpinBox gets focus, it must pass on the focus to its editor.
    if (d->editable && d->contentItem && !d->contentItem->hasActiveFocus())
        d->contentItem->forceActiveFocus(event->reason());
}

void DoubleSpinBox::hoverEnterEvent(QHoverEvent* event)
{
    Q_D(DoubleSpinBox);
    QQuickControl::hoverEnterEvent(event);
    d->updateHover(event->posF());
}

void DoubleSpinBox::hoverMoveEvent(QHoverEvent* event)
{
    Q_D(DoubleSpinBox);
    QQuickControl::hoverMoveEvent(event);
    d->updateHover(event->posF());
}

void DoubleSpinBox::hoverLeaveEvent(QHoverEvent* event)
{
    Q_D(DoubleSpinBox);
    QQuickControl::hoverLeaveEvent(event);
    d->down->setHovered(false);
    d->up->setHovered(false);
}

void DoubleSpinBox::keyPressEvent(QKeyEvent* event)
{
    Q_D(DoubleSpinBox);
    QQuickControl::keyPressEvent(event);

    int key = event->key();
    if (d->editable
        && (key == Qt::Key_Enter || key == Qt::Key_Return || key == Qt::Key_Up
            || key == Qt::Key_Down || key == Qt::Key_PageUp || key == Qt::Key_PageDown))
        d->updateValue();

    switch (key) {
    case Qt::Key_Up:
        if (d->upEnabled()) {
            d->stepUp(true);
            d->up->setPressed(true);
            event->accept();
        }
        break;

    case Qt::Key_Down:
        if (d->downEnabled()) {
            d->stepDown(true);
            d->down->setPressed(true);
            event->accept();
        }
        break;

    case Qt::Key_PageUp:
        if (d->upEnabled()) {
            d->pageStepUp(true);
            d->up->setPressed(true);
            event->accept();
        }
        break;

    case Qt::Key_PageDown:
        if (d->downEnabled()) {
            d->pageStepDown(true);
            d->down->setPressed(true);
            event->accept();
        }
        break;

    default:
        break;
    }

    setAccessibleProperty("pressed", d->up->isPressed() || d->down->isPressed());
}

void DoubleSpinBox::keyReleaseEvent(QKeyEvent* event)
{
    Q_D(DoubleSpinBox);
    QQuickControl::keyReleaseEvent(event);

    d->up->setPressed(false);
    d->down->setPressed(false);
    setAccessibleProperty("pressed", false);
}

void DoubleSpinBox::timerEvent(QTimerEvent* event)
{
    Q_D(DoubleSpinBox);
    QQuickControl::timerEvent(event);
    if (event->timerId() == d->delayTimer) {
        d->startPressRepeat();
    } else if (event->timerId() == d->repeatTimer) {
        if (d->up->isPressed())
            d->stepUp(true);
        else if (d->down->isPressed())
            d->stepDown(true);
    }
}

#if QT_CONFIG(wheelevent)
void DoubleSpinBox::wheelEvent(QWheelEvent* event)
{
    Q_D(DoubleSpinBox);
    QQuickControl::wheelEvent(event);
    if (d->wheelEnabled) {
        const QPointF angle = event->angleDelta();
        const qreal delta = (qFuzzyIsNull(angle.y()) ? angle.x() : angle.y())
                            / QWheelEvent::DefaultDeltasPerStep;
        d->stepBy(d->effectiveStepSize(d->stepSize) * delta, true);
    }
}
#endif

void DoubleSpinBox::classBegin()
{
    Q_D(DoubleSpinBox);
    QQuickControl::classBegin();

    QQmlContext* context = qmlContext(this);
    if (context) {
        QQmlEngine::setContextForObject(d->up, context);
        QQmlEngine::setContextForObject(d->down, context);
    }
}

void DoubleSpinBox::componentComplete()
{
    Q_D(DoubleSpinBox);
    QQuickControl::componentComplete();
    if (!d->setValue(d->value, /* allowWrap = */ false, /* modified = */ false)) {
        d->updateDisplayText();
        d->updateUpEnabled();
        d->updateDownEnabled();
    }
}

void DoubleSpinBox::itemChange(ItemChange change, const ItemChangeData& value)
{
    Q_D(DoubleSpinBox);
    QQuickControl::itemChange(change, value);
    if (d->editable && change == ItemActiveFocusHasChanged) {
        if (!value.boolValue)
            d->updateValue();
        else if (d->contentItem)
            QMetaObject::invokeMethod(d->contentItem, "selectAll");
    }
}

void DoubleSpinBox::contentItemChange(QQuickItem* newItem, QQuickItem* oldItem)
{
    Q_D(DoubleSpinBox);
    if (QQuickTextInput* oldInput = qobject_cast<QQuickTextInput*>(oldItem)) {
        QObjectPrivate::disconnect(oldInput,
                                   &QQuickTextInput::accepted,
                                   d,
                                   &DoubleSpinBoxPrivate::accept);
        disconnect(oldInput,
                   &QQuickTextInput::inputMethodComposingChanged,
                   this,
                   &DoubleSpinBox::inputMethodComposingChanged);
    }

    if (newItem) {
        newItem->setActiveFocusOnTab(true);
        if (d->activeFocus)
            newItem->forceActiveFocus(d->focusReason);
#if QT_CONFIG(cursor)
        if (d->editable)
            newItem->setCursor(Qt::IBeamCursor);
#endif

        if (QQuickTextInput* newInput = qobject_cast<QQuickTextInput*>(newItem)) {
            QObjectPrivate::connect(newInput,
                                    &QQuickTextInput::accepted,
                                    d,
                                    &DoubleSpinBoxPrivate::accept);
            connect(newInput,
                    &QQuickTextInput::inputMethodComposingChanged,
                    this,
                    &DoubleSpinBox::inputMethodComposingChanged);

            newInput->setValidator(d->validator);
        }
    }
}

void DoubleSpinBox::localeChange(const QLocale& newLocale, const QLocale& oldLocale)
{
    Q_D(DoubleSpinBox);
    QQuickControl::localeChange(newLocale, oldLocale);
    d->updateDisplayText();
}

QFont DoubleSpinBox::defaultFont() const
{
#if (QT_VERSION < QT_VERSION_CHECK(5, 12, 0))
    return QQuickControlPrivate::themeFont(QPlatformTheme::EditorFont);
#else
    return QQuickTheme::font(QQuickTheme::SpinBox);
#endif
}

QPalette DoubleSpinBox::defaultPalette() const
{
#if (QT_VERSION < QT_VERSION_CHECK(5, 12, 0))
    return QQuickControlPrivate::themePalette(QPlatformTheme::TextLineEditPalette);
#else
    return QQuickTheme::palette(QQuickTheme::SpinBox);
#endif
}

#if QT_CONFIG(accessibility)
QAccessible::Role DoubleSpinBox::accessibleRole() const
{
    return QAccessible::SpinBox;
}

void DoubleSpinBox::accessibilityActiveChanged(bool active)
{
    Q_D(DoubleSpinBox);
    QQuickControl::accessibilityActiveChanged(active);

    if (active)
        setAccessibleProperty("editable", d->editable);
}
#endif

DoubleSpinButton::DoubleSpinButton(DoubleSpinBox* parent)
    : QObject(*(new DoubleSpinButtonPrivate), parent)
{}

bool DoubleSpinButton::isPressed() const
{
    Q_D(const DoubleSpinButton);
    return d->pressed;
}

void DoubleSpinButton::setPressed(bool pressed)
{
    Q_D(DoubleSpinButton);
    if (d->pressed == pressed)
        return;

    d->pressed = pressed;
    emit pressedChanged();
}

QQuickItem* DoubleSpinButton::indicator() const
{
    Q_D(const DoubleSpinButton);
    return d->indicator;
}

void DoubleSpinButton::setIndicator(QQuickItem* indicator)
{
    Q_D(DoubleSpinButton);
    if (d->indicator == indicator)
        return;

    delete d->indicator;
    d->indicator = indicator;

    if (indicator) {
        if (!indicator->parentItem())
            indicator->setParentItem(static_cast<QQuickItem*>(parent()));
    }
    emit indicatorChanged();
}

bool DoubleSpinButton::isHovered() const
{
    Q_D(const DoubleSpinButton);
    return d->hovered;
}

void DoubleSpinButton::setHovered(bool hovered)
{
    Q_D(DoubleSpinButton);
    if (d->hovered == hovered)
        return;

    d->hovered = hovered;
    emit hoveredChanged();
}
