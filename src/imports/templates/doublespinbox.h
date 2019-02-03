/****************************************************************************
**
** Copyright (C) 2019 CELLINK AB <info@cellink.com>
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

#ifndef DOUBLESPINBOX_H
#define DOUBLESPINBOX_H

#include <QtQuickTemplates2/private/qquickcontrol_p.h>
#include <QtQml/qjsvalue.h>

class QValidator;
class DoubleSpinButton;
class DoubleSpinButtonPrivate;
class DoubleSpinBoxPrivate;

class DoubleSpinBox : public QQuickControl
{
    Q_OBJECT
    Q_PROPERTY(qreal from READ from WRITE setFrom NOTIFY fromChanged FINAL)
    Q_PROPERTY(qreal to READ to WRITE setTo NOTIFY toChanged FINAL)
    Q_PROPERTY(qreal value READ value WRITE setValue NOTIFY valueChanged FINAL)
    Q_PROPERTY(qreal stepSize READ stepSize WRITE setStepSize NOTIFY stepSizeChanged FINAL)
    Q_PROPERTY(qreal pageStepSize READ pageStepSize WRITE setPageStepSize NOTIFY pageStepSizeChanged FINAL)
    Q_PROPERTY(bool editable READ isEditable WRITE setEditable NOTIFY editableChanged FINAL)
    Q_PROPERTY(QValidator *validator READ validator WRITE setValidator NOTIFY validatorChanged FINAL)
    Q_PROPERTY(QJSValue textFromValue READ textFromValue WRITE setTextFromValue NOTIFY textFromValueChanged FINAL)
    Q_PROPERTY(QJSValue valueFromText READ valueFromText WRITE setValueFromText NOTIFY valueFromTextChanged FINAL)
    Q_PROPERTY(DoubleSpinButton *up READ up CONSTANT FINAL)
    Q_PROPERTY(DoubleSpinButton *down READ down CONSTANT FINAL)
    Q_PROPERTY(Qt::InputMethodHints inputMethodHints READ inputMethodHints WRITE setInputMethodHints NOTIFY inputMethodHintsChanged FINAL)
    Q_PROPERTY(bool inputMethodComposing READ isInputMethodComposing NOTIFY inputMethodComposingChanged FINAL)
    Q_PROPERTY(bool wrap READ wrap WRITE setWrap NOTIFY wrapChanged FINAL)
    Q_PROPERTY(QString displayText READ displayText WRITE setDisplayText RESET resetDisplayText NOTIFY displayTextChanged FINAL)
    Q_PROPERTY(int decimals READ decimals WRITE setDecimals NOTIFY decimalsChanged FINAL)
    Q_PROPERTY(QString prefix READ prefix WRITE setPrefix NOTIFY prefixChanged FINAL)
    Q_PROPERTY(QString suffix READ suffix WRITE setSuffix NOTIFY suffixChanged FINAL)

public:
    explicit DoubleSpinBox(QQuickItem *parent = nullptr);

    qreal from() const;
    void setFrom(qreal from);

    qreal to() const;
    void setTo(qreal to);

    qreal value() const;
    void setValue(qreal value);

    qreal stepSize() const;
    void setStepSize(qreal step);

    qreal pageStepSize() const;
    void setPageStepSize(qreal step);

    bool isEditable() const;
    void setEditable(bool editable);

    QValidator *validator() const;
    void setValidator(QValidator *validator);

    QJSValue textFromValue() const;
    void setTextFromValue(const QJSValue &callback);

    QJSValue valueFromText() const;
    void setValueFromText(const QJSValue &callback);

    DoubleSpinButton *up() const;
    DoubleSpinButton *down() const;

    Qt::InputMethodHints inputMethodHints() const;
    void setInputMethodHints(Qt::InputMethodHints hints);

    bool isInputMethodComposing() const;

    bool wrap() const;
    void setWrap(bool wrap);

    QString displayText() const;
    void setDisplayText(const QString &text);
    void resetDisplayText();

    int decimals() const;
    void setDecimals(int decimals);

    QString prefix() const;
    void setPrefix(const QString &prefix);

    QString suffix() const;
    void setSuffix(const QString &suffix);

public Q_SLOTS:
    void increase();
    void decrease();

Q_SIGNALS:
    void fromChanged();
    void toChanged();
    void valueChanged();
    void stepSizeChanged();
    void pageStepSizeChanged();
    void editableChanged();
    void validatorChanged();
    void textFromValueChanged();
    void valueFromTextChanged();
    void valueModified();
    void inputMethodHintsChanged();
    void inputMethodComposingChanged();
    void wrapChanged();
    void displayTextChanged();
    void decimalsChanged();
    void prefixChanged();
    void suffixChanged();

protected:
    void focusInEvent(QFocusEvent *event) override;
    void hoverEnterEvent(QHoverEvent *event) override;
    void hoverMoveEvent(QHoverEvent *event) override;
    void hoverLeaveEvent(QHoverEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void timerEvent(QTimerEvent *event) override;
#if QT_CONFIG(wheelevent)
    void wheelEvent(QWheelEvent *event) override;
#endif

    void classBegin() override;
    void componentComplete() override;
    void itemChange(ItemChange change, const ItemChangeData &value) override;
    void contentItemChange(QQuickItem *newItem, QQuickItem *oldItem) override;
    void localeChange(const QLocale &newLocale, const QLocale &oldLocale) override;

    QFont defaultFont() const override;
    QPalette defaultPalette() const override;

#if QT_CONFIG(accessibility)
    QAccessible::Role accessibleRole() const override;
    void accessibilityActiveChanged(bool active) override;
#endif

private:
    Q_DISABLE_COPY(DoubleSpinBox)
    Q_DECLARE_PRIVATE(DoubleSpinBox)
};

// ### TODO: re-use QQuickSpinButton
class DoubleSpinButton : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool pressed READ isPressed WRITE setPressed NOTIFY pressedChanged FINAL)
    Q_PROPERTY(QQuickItem *indicator READ indicator WRITE setIndicator NOTIFY indicatorChanged FINAL)
    Q_PROPERTY(bool hovered READ isHovered WRITE setHovered NOTIFY hoveredChanged FINAL)

public:
    explicit DoubleSpinButton(DoubleSpinBox *parent);

    bool isPressed() const;
    void setPressed(bool pressed);

    QQuickItem *indicator() const;
    void setIndicator(QQuickItem *indicator);

    bool isHovered() const;
    void setHovered(bool hovered);

Q_SIGNALS:
    void pressedChanged();
    void indicatorChanged();
    void hoveredChanged();

private:
    Q_DISABLE_COPY(DoubleSpinButton)
    Q_DECLARE_PRIVATE(DoubleSpinButton)
};

QML_DECLARE_TYPE(DoubleSpinBox)

#endif // QQUICKDOUBLESPINBOX_P_H
