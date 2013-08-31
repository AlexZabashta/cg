#pragma once

#include <cg/primitives/point.h>
#include <cg/primitives/segment.h>
#include <cg/primitives/triangle.h>
#include <cg/primitives/contour.h>
#include <cg/triangulation/triangle_side.h>
#include <cg/operations/segment_segment.h>
#include <cg/operations/orientation.h>
#include <cg/operations/segment_segment.h>

namespace cg
{
template <class Scalar>
inline bool is_ear(triangle_side<Scalar>* cur_side)
{
    triangle_side<Scalar>* temp_side = cur_side->next;
    if (orientation_t(cur_side->start, cur_side->finish, temp_side->finish) != CG_LEFT)
    {
        return false;
    }
    segment_2t<Scalar> seg(temp_side->finish, cur_side->start);
    temp_side = cur_side->prev;
    cur_side = cur_side->next->next->next;
    while (cur_side != temp_side)
    {
        if (cross(seg, segment_2t<Scalar>(cur_side->start, cur_side->finish)))
        {
            return false;
        }
        cur_side = cur_side->next;
    }
    return true;
}


template <class Scalar>
triangle_side<Scalar>* ear_clipping_triangulation(contour_2t<Scalar> &cont)
{
    int size = cont.size();

    triangle_side<Scalar>* first_side = new triangle_side<Scalar>(cont[0], cont[1]);
    triangle_side<Scalar>* last_side = first_side;
    triangle_side<Scalar>* temp_side;
    for (int i = 1; i < size; i++)
    {
        temp_side = new triangle_side<Scalar>(cont[i], cont[(i + 1) % size]);
        last_side->next = temp_side;
        temp_side->prev = last_side;
        last_side = temp_side;
    }
    last_side->next = first_side;
    first_side->prev = last_side;
    last_side = first_side;
    if (size > 3)
    {
        temp_side = first_side;
        for (int i = 0; i < size; i++)
        {
            temp_side->color = is_ear(temp_side);
            temp_side = temp_side->next;
        }
        while (size > 3)
        {
            if (temp_side->color)
            {
                triangle_side<Scalar>* tr_side = new triangle_side<Scalar>(temp_side->next->finish, temp_side->start);
                triangle_side<Scalar>* con_side = new triangle_side<Scalar>(temp_side->start, temp_side->next->finish);
                tr_side->twin = con_side;
                con_side->twin = tr_side;
                triangle_side<Scalar>* n_side = temp_side->next->next;
                triangle_side<Scalar>* p_side = temp_side->prev;

                n_side->prev = con_side;
                con_side->next = n_side;

                p_side->next = con_side;
                con_side->prev = p_side;

                temp_side->prev = tr_side;
                tr_side->next = temp_side;

                temp_side->next->next = tr_side;
                tr_side->prev = temp_side->next;

                p_side->color = is_ear(p_side);
                con_side->color = is_ear(con_side);

                temp_side->color = false;
                temp_side->color->next = false;
                tr_side->color = false;

                temp_side = p_side;
            }
            else
            {
                temp_side = temp_side->next;
            }
        }
    }
    return first_side;
}
}
