#pragma once

#include <cg/primitives/point.h>
#include <cg/primitives/segment.h>
#include <cg/primitives/range.h>

#include <cg/operations/orientation.h>

namespace cg
{
template<class Scalar>
bool contains(segment_2t<Scalar> const & s, point_2t<Scalar> const & p)
{
    if (orientation(s[0], s[1], p) != CG_COLLINEAR)
        return false;
    return (s[0] <= p && p <= s[1]) || (s[1] <= p && p <= s[0]);
}
}
