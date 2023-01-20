#pragma once

#include <QtCore/QMetaType>

namespace cellink {

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

} // namespace cellink

Q_DECLARE_METATYPE(cellink::HighlightLines)
