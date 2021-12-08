#pragma once

#include <States/IMethodState.h>

class NewtonRaphsonState : public IMethodState
{
public:
	NewtonRaphsonState(double x, double dx, double ddx)
		: x(x)
		, dx(dx)
		, ddx(ddx)
	{}

	std::vector<double> GetValues() const override
	{
		return { x, dx, ddx };
	}

	double x, dx, ddx;
};

