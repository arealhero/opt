#pragma once

#include <States/IMethodState.h>

class PassiveSearchState : public IMethodState
{
public:
	PassiveSearchState(double x, double y, double minX, double minY)
		: x(x)
		, y(y)
		, minX(minX)
		, minY(minY)
	{}

	std::vector<double> GetValues() const override
	{
		return { x, y, minX, minY };
	}

	double x;
	double y;
	double minX;
	double minY;
};

