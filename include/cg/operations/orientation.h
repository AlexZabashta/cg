#pragma once

#include "cg/primitives/point.h"
#include <boost/numeric/interval.hpp>
#include <boost/optional.hpp>
#include <limits>

namespace cg
{
	enum orientation_t
	{
		CG_RIGHT = -1,
		CG_COLLINEAR = 0,
		CG_LEFT = 1
	};

	template <class Scalar>
	orientation_t orientation(point_2t<Scalar> const & a, point_2t<Scalar> const & b, point_2t<Scalar> const & c)
	{
		Scalar area = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
		Scalar eps = std::numeric_limits<Scalar>::epsilon() * 12345678;
		if (area > eps)
			return CG_LEFT;

		if (area < -eps)
			return CG_RIGHT;

		return CG_COLLINEAR;
	}

	inline bool opposite(orientation_t a, orientation_t b)
	{
		if (a == CG_COLLINEAR || b == CG_COLLINEAR)
		return false;

		return a == -b;
	}
}
