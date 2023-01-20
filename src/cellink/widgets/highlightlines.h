#ifndef HIGHLIGHTLINES_H
#define HIGHLIGHTLINES_H

#include <QtGlobal>

namespace {

struct HighlightLines
{
    int low;
    int high;

    bool operator==(const HighlightLines& other) const
    {
        return low == other.low && high == other.high;
    }

    bool operator!=(const HighlightLines& other) const { return !(*this == other); }
};
Q_DECLARE_METATYPE(HighlightLines)

} // namespace
#endif // HIGHLIGHTLINES_H
