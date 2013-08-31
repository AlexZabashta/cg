#pragma once

#include <cg/operations/orientation.h>
#include <cg/operations/segment_point.h>
#include <cg/operations/segment_segment.h>
#include <cg/operations/contour_point.h>
#include "cg/primitives/point.h"

namespace cg
{
enum segment_location
{
    CG_OUTSIDE = -1,
    CG_CROSS = 0,
    CG_INSIDE = 1
};

template <class Scalar>
segment_location location_t(contour_2t<Scalar> const & con, segment_2t<Scalar> const& seg)
{
    int n = con.size();
    for (int i = 0; i < n; i++)
        if (cross(segment_2t<Scalar>(con[i], con[(i + 1) % n]), seg))
            return CG_CROSS;
    return contains(con, seg[0]) ? CG_INSIDE : CG_OUTSIDE;

}
}
