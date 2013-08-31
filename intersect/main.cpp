#include <iostream>
#include <vector>

#include <cg/primitives/segment.h>
#include <cg/primitives/point.h>
#include <cg/primitives/range.h>
#include <cg/primitives/rectangle.h>
#include <cg/primitives/segment.h>
#include <cg/primitives/triangle.h>
#include <cg/primitives/vector.h>
#include <cg/primitives/contour.h>

#include <cg/operations/orientation.h>
#include <cg/operations/segment_point.h>
#include <cg/operations/segment_segment.h>
#include <cg/operations/triangle_point.h>
#include <cg/operations/contour_point.h>
#include <cg/operations/contour_segment.h>
#include <cg/operations/contour_contour.h>



cg::point_2i a, b, c, d, e, f;
std::vector<cg::point_2i> v;

int main()
{
    std::cout << "segment_point" << std::endl;
    a = cg::point_2i(0, 0);
    b = cg::point_2i(2, 2);
    c = cg::point_2i(1, 3);
    if (!cg::contains<int>(cg::segment_2t<int>(a, b), c))
        std::cout << "not ";
    std::cout << "contains" << std::endl << std::endl;


    std::cout << "triangle_point" << std::endl;
    a = cg::point_2i(0, 0);
    b = cg::point_2i(2, 0);
    c = cg::point_2i(1, 2);
    d = cg::point_2i(1, 1);
    if (!cg::contains<int>(cg::triangle_2t<int>(a, b, c), d))
        std::cout << "not ";
    std::cout << "contains" << std::endl << std::endl;


    std::cout << "contour_point" << std::endl;
    v = std::vector<cg::point_2i>();
    v.push_back(cg::point_2i(0, 0));
    v.push_back(cg::point_2i(2, 0));
    v.push_back(cg::point_2i(1, 2));
    if (!cg::contains<int>(cg::contour_2t<int>(v), cg::point_2i(1, 1)))
        std::cout << "not ";
    std::cout << "contains" << std::endl << std::endl;


    std::cout << "segment_segment" << std::endl;
    a = cg::point_2i(0, 0);
    b = cg::point_2i(2, 0);
    c = cg::point_2i(1, 2);
    d = cg::point_2i(1, 1);
    std::cout << (cg::cross(cg::segment_2t<int>(a, c), cg::segment_2t<int>(b, d))) << std::endl << std::endl;

    std::cout << "contour_segment" << std::endl;
    a = cg::point_2i(0, 0);
    b = cg::point_2i(2, 0);
    c = cg::point_2i(1, 2);
    d = cg::point_2i(1, 1);
    e = cg::point_2i(1, 3);
    switch(cg::location_t(cg::contour_2t<int>(cg::triangle_2t<int>(a, b, c)), cg::segment_2t<int>(d, e)))
    {
    case cg::CG_OUTSIDE:
        std::cout << "OUTSIDE" << std::endl << std::endl;
        break;
    case cg::CG_INSIDE:
        std::cout << "INSIDE" << std::endl << std::endl;
        break;
    case cg::CG_CROSS:
        std::cout << "CROSS" << std::endl << std::endl;
    }

    std::cout << "contour_contour" << std::endl;
    a = cg::point_2i(0, 0);
    b = cg::point_2i(2, 0);
    c = cg::point_2i(1, 2);

    d = cg::point_2i(1, 1);
    e = cg::point_2i(1, 3);
    f = cg::point_2i(3, 0);
    switch(cg::location_t(cg::contour_2t<int>(cg::triangle_2t<int>(a, b, c)),
                          cg::contour_2t<int>(cg::triangle_2t<int>(d, e, f))))
    {
    case cg::CG_OUTSIDE:
        std::cout << "OUTSIDE" << std::endl << std::endl;
        break;
    case cg::CG_INSIDE:
        std::cout << "INSIDE" << std::endl << std::endl;
        break;
    case cg::CG_CROSS:
        std::cout << "CROSS" << std::endl << std::endl;
    }

    return 0;
}
