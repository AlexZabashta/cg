#pragma once

#include <cg/primitives/point.h>

namespace cg
{
template <class Scalar>
struct triangle_side
{
    point_2t<Scalar> start, finish;
    triangle_side<Scalar> *next, *prev, *twin;
    bool color;
    triangle_side(point_2t<Scalar> s, point_2t<Scalar> f)
     {
         start = s;
         finish = f;
         twin = NULL;
     }
};
}
