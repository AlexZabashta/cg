#pragma once

#include <cg/primitives/point.h>
#include <cg/primitives/segment.h>

#include <cg/operations/orientation.h>
#include <cg/operations/segment_point.h>
#include <algorithm>

namespace cg
{
template<class Scalar>
inline bool cross(segment_2t<Scalar> const & a, segment_2t<Scalar> const & b)
{
    orientation_t u = orientation(a[0], a[1], b[0]);
    orientation_t v = orientation(a[0], a[1], b[1]);

    if ((u == CG_LEFT && v == CG_LEFT) || ((u == CG_RIGHT && v == CG_RIGHT)))
        return false;

    if ((u == CG_LEFT && v == CG_RIGHT) || ((u == CG_RIGHT && v == CG_LEFT)))
        return orientation(b[0], b[1], a[0]) == orientation(b[0], b[1], a[1]);

    return contains<Scalar>(a, b[0]) || contains<Scalar>(a, b[1]) ||
           contains<Scalar>(b, a[0]) || contains<Scalar>(b, a[1]);
}
}
