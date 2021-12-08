#pragma once

#include <States/IMethodState.h>

class TangentState : public IMethodState
{
public:
	TangentState(double a, double fa, double da,
			double b, double fb, double db,
			double c, double dc)
		: a(a)
		, fa(fa)
		, da(da)

		, b(b)
		, fb(fb)
		, db(db)

		, c(c)
		, dc(dc)
	{}

	std::vector<double> GetValues() const override
	{
		return { a, fa, da, b, fb, db, c, dc };
	}

	double a, fa, da;
	double b, fb, db;
	double c, dc;
};

