#include <iostream>
#include <vector>
#include <cg/primitives/point.h>
#include <cg/triangulation/triangle_side.h>
#include <cg/triangulation/ear_clipping_triangulation.h>
#include <cg/primitives/contour.h>

template <class Scalar>
void print_side(cg::triangle_side<Scalar>* tr_side)
{
    int n = 3;
    while (--n >= 0)
    {

        std::cout << tr_side->start.x << ' ' << tr_side->start.y << std::endl;
        tr_side = tr_side->next;
        tr_side->color = true;
    }
    n = 3;
    while (--n >= 0)
    {
        if (tr_side->twin != NULL && !tr_side->twin->color)
        {
            print_side<Scalar>(tr_side->twin);
        }
        tr_side = tr_side->next;
    }
}

int main()
{
    std::vector<cg::point_2t<int> > v;
    v.push_back(cg::point_2t<int>(0, 0));
    v.push_back(cg::point_2t<int>(2, 1));
    v.push_back(cg::point_2t<int>(2, 3));
    v.push_back(cg::point_2t<int>(0, 4));
    print_side(cg::ear_clipping_triangulation<int>(cg::contour_2t<int>(v)));
    return 0;
}
