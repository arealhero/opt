#pragma once

#include <States/IMethodState.h>

class SecantLinesState : public IMethodState
{
public:
	SecantLinesState(double x, double dx, double px, double dpx)
		: x(x)
		, dx(dx)
		, px(px)
		, dpx(dpx)
	{}

	std::vector<double> GetValues() const override
	{
		return { x, dx, px, dpx };
	}

	double x, dx;
	double px, dpx;
};

