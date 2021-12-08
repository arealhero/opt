#pragma once

#include <Methods/IMethod.h>

#include <States/SecantLinesState.h>

#include <vector>
#include <string>
#include <cmath>

class SecantLinesMethod : public IMethod
{
public:
	using IMethod::IMethod;

	static std::string GetTitle()
	{
		return { "Secant Lines" };
	}
	static std::vector<std::string> GetColumnNames()
	{
		return {
			"x", "f'(x)", "prev_x", "f'(prev_x)"
		};
	}

	void Init() override
	{
		px = a + (b - a) / 4;
		dpx = df(px);

		x = b - (b - a) / 4;
		dx = df(x);

		adx = std::abs(dx);
	}

	bool Iterate() override
	{
		if (adx <= eps) return false;

		nx = x - ((x - px) / (dx - dpx)) * dx;

		px = x;
		dpx = dx;

		x = nx;
		dx = df(x);

		adx = std::abs(dx);

		return true;
	}

	double GetResult() override
	{
		return x;
	}

	std::shared_ptr<IMethodState> GetState() const override
	{
		return std::make_shared<SecantLinesState>(x, dx, px, dpx);
	}

private:
	double x, dx, adx;
	double nx, px, dpx;
};

