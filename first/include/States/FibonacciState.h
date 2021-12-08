#pragma once

#include <States/IMethodState.h>

class FibonacciState : public IMethodState
{
public:
	FibonacciState(double a, double b, double c, double d,
			double yc, double yd)
		: a(a)
		, b(b)
		, c(c)
		, d(d)

		, yc(yc)
		, yd(yd)
	{}

	std::vector<double> GetValues() const override
	{
		return { a, b, c, d, yc, yd };
	}

	double a, b, c, d;
	double yc, yd;
};

