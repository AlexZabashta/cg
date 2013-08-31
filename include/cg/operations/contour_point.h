#pragma once

#include <cg/primitives/point.h>
#include <cg/primitives/contour.h>
#include <algorithm>

namespace cg
{
static const int q_patt[2][2]= { {0,1}, {3,2} };
template<class Scalar>
bool contains(contour_2t<Scalar> c, point_2t<Scalar> p)
{
    if (c.size() < 3)
        return false;


    point_2t<Scalar> pred_pt = *(c.end());
    pred_pt.x -= p.x;
    pred_pt.y -= p.y;

    int pred_q = q_patt[pred_pt.y < 0][pred_pt.x < 0];

    int w = 0;

    for (typename std::vector<point_2t<Scalar> >::const_iterator iter = c.begin(); iter != c.end(); ++iter)
    {
        point_2t<Scalar> cur_pt = *iter;
        cur_pt.x -= p.x;
        cur_pt.y -= p.y;
        int q = q_patt[cur_pt.y < 0][cur_pt.x < 0];

        switch (q - pred_q)
        {
        case -3:
            ++w;
            break;
        case 3:
            --w;
            break;
        case -2:
            if (pred_pt.x * cur_pt.y >= pred_pt.y * cur_pt.x)
                ++w;
            break;
        case 2:
            if (!(pred_pt.x * cur_pt.y >= pred_pt.y * cur_pt.x))
                --w;
            break;
        }

        pred_pt = cur_pt;
        pred_q = q;

    }

    return w == 0;

}
}
