#include "cellinkwidgets_stable.h"
#include "cellinkwidgets/utils.h"

namespace
{
    constexpr auto HEIGHT = 150;
    constexpr auto ARROW_WIDTH = 25;
    constexpr auto ARROW_HEIGHT = 25;
    constexpr auto RADIUS = 6;
}

namespace Utils {

void setMask(QWidget* widget, const QPainterPath& painterPath)
{
    QPixmap pixmap(widget->size());
    QPainter painter(&pixmap);
    painter.fillRect(pixmap.rect(), Qt::white);
    painter.setBrush(Qt::black);
    painter.drawPath(painterPath);
    widget->setMask(pixmap.createMaskFromColor(Qt::white));
}

void setArrowPopupMask(QWidget* widget, int arrowXOffset)
{
    const auto xCenter = widget->width() / 2 - arrowXOffset;
    QPainterPath path;
    path.moveTo(xCenter, 0);
    path.lineTo(xCenter + ARROW_WIDTH / 2, ARROW_HEIGHT);
    path.lineTo(xCenter - ARROW_WIDTH / 2, ARROW_HEIGHT);
    path.lineTo(xCenter, 0);
    path.addRoundRect(widget->rect().adjusted(0, ARROW_HEIGHT, 0, 0), RADIUS, RADIUS);
    setMask(widget, path);
}

void setRoundedMask(QWidget *widget, int radius)
{
    QPainterPath roundRectPath;
    roundRectPath.addRoundedRect(widget->rect(), radius, radius);

    setMask(widget, roundRectPath);
}

void moveWidgetWithMargin(const QWidget *pivotWidget, QWidget *moveWidget, Qt::Alignment alignment, int xMargin, int yMargin)
{
    // horizontal

    auto moveX = xMargin;

    if(alignment & Qt::AlignLeft) {
        // just margin
    } else if(alignment & Qt::AlignRight) {
        moveX += pivotWidget->rect().width();
    } else { // center
        moveX += pivotWidget->rect().width() / 2 - moveWidget->rect().width() / 2;
    }

    auto moveY = yMargin;

    // vertical
    if(alignment & Qt::AlignTop) {
        // just margin
    } else if(alignment & Qt::AlignBottom) {
        moveY += pivotWidget->rect().height();
    } else { // center
        moveY += pivotWidget->rect().height() / 2 - moveWidget->rect().height() / 2;
    }

    auto globalPos = pivotWidget->mapToGlobal(QPoint(moveX, moveY));
    const auto pivotScreen = qApp->screenAt(pivotWidget->mapToGlobal({0,0}));

    // just solve for left/right now, leave top/bottom issues for later
    const auto widgetScreenLeft = qApp->screenAt(globalPos);
    const auto widgetScreenRight = qApp->screenAt({globalPos.x() + moveWidget->width(), globalPos.y()});

    if (pivotScreen != widgetScreenLeft && pivotScreen == widgetScreenRight) {
        globalPos.rx() += moveWidget->width() + pivotWidget->width();
    } else  if (pivotScreen == widgetScreenLeft && pivotScreen != widgetScreenRight) {
        globalPos.rx() -= moveWidget->width() + pivotWidget->width();
    }

    moveWidget->move(globalPos);
}

void keepWidgetBottomVisible(QWidget *moveWidget, int yOffset)
{
    auto screen = qApp->screenAt(moveWidget->pos());
    if (screen) {
        auto maxSize = screen->size();
        maxSize.setHeight(maxSize.height() - yOffset);
        auto movePos = moveWidget->mapToGlobal(moveWidget->rect().bottomLeft());
        if(movePos.y() > maxSize.height()) {
            auto yDiff = maxSize.height() - movePos.y();
            auto globalPos = moveWidget->mapToGlobal(QPoint(moveWidget->rect().left(), yDiff));
            moveWidget->move(globalPos);
        }
    }
    else {
        qWarning() << "No screen available on position" << moveWidget->pos();
        screen = qApp->screens().at(0);
        const auto center = screen->geometry().center();
        auto movePos = moveWidget->mapToGlobal(moveWidget->rect().bottomLeft());
        movePos.setY(center.y() - yOffset);
        moveWidget->move(movePos);
    }
}

QPixmap loadPixmap(const QString &path)
{
    auto pixmap = QPixmap();

    if (QPixmapCache::find(path, &pixmap)) {
        return pixmap;
    }

    if (!pixmap.load(path)) {
        static QSet<QString> s_failedPaths;

        if (!s_failedPaths.contains(path)) {
            qWarning() << "Failed to load" << path;
            s_failedPaths.insert(path);
        }
        return pixmap;
    }

    QPixmapCache::insert(path, pixmap);
    return pixmap;
}

QString computeIntervalString(QVector<int> entries)
{
    if (entries.empty())
        return {};

    if (entries.size() == 1)
        return QString::number(entries.first());

    std::sort(entries.begin(), entries.end());

    QString result;
    result.reserve(64);
    auto spanBegin = entries.first();

    const auto formatSpan = [templ = QStringLiteral("%1-%2")](int begin, int end) {
        if (begin == end)
            return QString::number(begin);
        else
            return templ.arg(begin).arg(end);
    };

    for (auto i = 1; i < entries.size(); i++) {
        const auto entry = entries[i];
        const auto prevEntry = entries[i-1];

        if (entry - prevEntry <= 1) {
            continue;
        }

        result += formatSpan(spanBegin, prevEntry);
        result += ", ";
        spanBegin = entry;
    }

    result += formatSpan(spanBegin, entries.last());

    return result;
}

void retainSizeWhenHidden(QWidget* widget)
{
    QSizePolicy policy = widget->sizePolicy();
    policy.setRetainSizeWhenHidden(true);
    widget->setSizePolicy(policy);
}

void setIgnoreVerticalSizePolicy(QWidget* widget, bool ignore)
{
    auto sizePolicy = widget->sizePolicy();
    sizePolicy.setVerticalPolicy(ignore ? QSizePolicy::Ignored : QSizePolicy::Fixed);
    widget->setSizePolicy(sizePolicy);
}

void setWidgetBackgroundColor(QWidget *widget, const QColor &color)
{
    auto palette = widget->palette();
    palette.setBrush(QPalette::Window, color);
    widget->setPalette(palette);
}

void paintFullScreenMessage(QWidget *widget)
{
    QPainter p;
    p.begin(widget);

    auto font = p.font();
    font.setPixelSize(25);
    p.setFont(font);

    const auto text = widget->tr("Tap to minimize");
    const auto textFlags = Qt::AlignBottom | Qt::AlignHCenter;
    const auto margins = QMargins(15,15,15,15);
    auto textRect = p.boundingRect(widget->rect(), textFlags, text);
    textRect.moveTop(textRect.top() - 50);
    const auto boundingRect = textRect.marginsAdded(margins);

    // draw greay rectangle
    p.setPen(Qt::lightGray);
    p.setBrush(QBrush(Qt::lightGray));
    p.drawRoundedRect(boundingRect, 15, 15);

    // draw text
    p.setPen(Qt::white);
    p.drawText(textRect, textFlags, text);

    p.end();
}

}

