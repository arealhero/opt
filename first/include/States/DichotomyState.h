#pragma once

#include <States/IMethodState.h>

class DichotomyState : public IMethodState
{
public:
	DichotomyState(double a, double b, double mid, double c, double d,
			double yc, double yd)
		: a(a)
		, b(b)

		, mid(mid)
		, c(c)
		, d(d)

		, yc(yc)
		, yd(yd)
	{}

	std::vector<double> GetValues() const override
	{
		return { a, b, mid, c, d, yc, yd };
	}

	double a, b;
	double mid, c, d;
	double yc, yd;
};

