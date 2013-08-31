#include <iostream>
#include <ctime>
#include "cg/io/point.h"
#include "cg/operations/orientation.h"
#include <boost/random/linear_congruential.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/uniform_real.hpp>
#include <boost/random/variate_generator.hpp>

namespace cg
{
template <class Scalar>
orientation_t bad_orientation(point_2t<Scalar> const & a, point_2t<Scalar> const & b, point_2t<Scalar> const & c)
{
    Scalar area = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    if (area > 0)
        return CG_LEFT;

    if (area < 0)
        return CG_RIGHT;

    return CG_COLLINEAR;
}
}
int main()
{
    boost::minstd_rand generator(static_cast<unsigned int>(std::time(0)));
    boost::uniform_real<> uni_dist(0,1);
    boost::variate_generator<boost::minstd_rand&, boost::uniform_real<> > uni(generator, uni_dist);
    int n = 0;
    while (n++ < 10000000)
    {
        cg::point_2t<double> a(0, 0);
        cg::point_2t<double> b(uni(),  uni());
        cg::point_2t<double> c(b.x / 137, b.y / 137);
        if (cg::bad_orientation<double>(a, b, c) != cg::CG_COLLINEAR)
        {
            std::cout << a.x << ' ' << a.y << std::endl;
            std::cout << b.x << ' ' << b.y << std::endl;
            std::cout << c.x << ' ' << c.y << std::endl;
            break;
        }
    }
    return 0;
}

