#ifndef MENUBUTTON_H
#define MENUBUTTON_H

#include "cellinkwidgets_global.h"
#include <QPushButton>

class CELLINKWIDGETS_EXPORT MenuButton : public QPushButton
{
    Q_OBJECT
    Q_PROPERTY(QString alignment READ alignment WRITE setAlignment NOTIFY alignmentChanged)

public:
    explicit MenuButton(QWidget *parent = nullptr);
    ~MenuButton() override;

    [[nodiscard]] QString alignment() const { return m_alignment; }

public slots:
    void setAlignment(QString alignment);

signals:
    void alignmentChanged(QString value);

private:
    QString m_alignment;
};

#endif // MENUBUTTON_H
