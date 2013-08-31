#pragma once

#include <cg/operations/orientation.h>
#include <cg/operations/segment_point.h>
#include <cg/operations/segment_segment.h>
#include <cg/operations/contour_point.h>
#include <cg/operations/contour_segment.h>

#include "cg/primitives/point.h"

namespace cg
{
template <class Scalar>
segment_location location_t(contour_2t<Scalar> const & a, contour_2t<Scalar> const & b)
{
    bool out = false, cr = false;
    int n = b.size();

    for (int i = 0; i < n; i++)
    {
        switch(location_t(a, segment_2t<int>(b[i], b[(i + 1) % n])))
        {
        case CG_OUTSIDE:
            out = true;
            break;
        case CG_CROSS:
            cr = true;
            break;
        case CG_INSIDE:
            break;
        }
    }
    if(cr)
        return CG_CROSS;
    return out ? CG_OUTSIDE : CG_INSIDE;
}
}
