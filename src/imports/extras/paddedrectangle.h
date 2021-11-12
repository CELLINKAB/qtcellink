/****************************************************************************
**
** Copyright (C) 2020 CELLINK AB <info@cellink.com>
** Copyright (C) 2017 The Qt Company Ltd.
**
** This file is part of QtCellink (based on the Qt Quick Controls 2 module of Qt).
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

#ifndef PADDEDRECTANGLE_H
#define PADDEDRECTANGLE_H

#include <QtQuick/private/qquickrectangle_p.h>

class PaddedRectangle : public QQuickRectangle
{
    Q_OBJECT
    Q_PROPERTY(
        qreal padding READ padding WRITE setPadding RESET resetPadding NOTIFY paddingChanged FINAL)
    Q_PROPERTY(qreal topPadding READ topPadding WRITE setTopPadding RESET resetTopPadding NOTIFY
                   topPaddingChanged FINAL)
    Q_PROPERTY(qreal leftPadding READ leftPadding WRITE setLeftPadding RESET resetLeftPadding NOTIFY
                   leftPaddingChanged FINAL)
    Q_PROPERTY(qreal rightPadding READ rightPadding WRITE setRightPadding RESET resetRightPadding
                   NOTIFY rightPaddingChanged FINAL)
    Q_PROPERTY(qreal bottomPadding READ bottomPadding WRITE setBottomPadding RESET
                   resetBottomPadding NOTIFY bottomPaddingChanged FINAL)

public:
    explicit PaddedRectangle(QQuickItem* parent = nullptr);

    qreal padding() const;
    void setPadding(qreal padding);
    void resetPadding();

    qreal topPadding() const;
    void setTopPadding(qreal padding);
    void resetTopPadding();

    qreal leftPadding() const;
    void setLeftPadding(qreal padding);
    void resetLeftPadding();

    qreal rightPadding() const;
    void setRightPadding(qreal padding);
    void resetRightPadding();

    qreal bottomPadding() const;
    void setBottomPadding(qreal padding);
    void resetBottomPadding();

Q_SIGNALS:
    void paddingChanged();
    void topPaddingChanged();
    void leftPaddingChanged();
    void rightPaddingChanged();
    void bottomPaddingChanged();

protected:
    QSGNode* updatePaintNode(QSGNode*, UpdatePaintNodeData*) override;

private:
    void setTopPadding(qreal padding, bool has);
    void setLeftPadding(qreal padding, bool has);
    void setRightPadding(qreal padding, bool has);
    void setBottomPadding(qreal padding, bool has);

    qreal m_padding = 0;
    qreal m_topPadding = 0;
    qreal m_leftPadding = 0;
    qreal m_rightPadding = 0;
    qreal m_bottomPadding = 0;
    bool m_hasTopPadding = false;
    bool m_hasLeftPadding = false;
    bool m_hasRightPadding = false;
    bool m_hasBottomPadding = false;
};

QML_DECLARE_TYPE(PaddedRectangle)

#endif // PADDEDRECTANGLE_H
