#pragma once

#include <Methods/IMethod.h>

#include <States/GoldenRatioState.h>

#include <vector>
#include <string>
#include <cmath>

class GoldenRatioMethod : public IMethod
{
public:
	using IMethod::IMethod;

	static std::string GetTitle()
	{
		return { "Golden Ratio" };
	}
	static std::vector<std::string> GetColumnNames()
	{
		return { "a", "b", "c", "d", "f(c)", "f(d)"};
	}

	void Init() override
	{
		c = firstConst * (b - a) + a;
		d = secondConst * (b - a) + a;

		yc = f(c);
		yd = f(d);
	}

	bool Iterate() override
	{
		if ((b - a) / 2 <= eps)
			return false;

		if (yc <= yd)
		{
			b = d;
			d = c;
			c = firstConst * (b - a) + a;

			yd = yc;
			yc = f(c);
		}
		else
		{
			a = c;
			c = d;
			d = secondConst * (b - a) + a;

			yc = yd;
			yd = f(d);
		}

		return true;
	}

	double GetResult() override
	{
		return a + (b - a) / 2;
	}

	std::shared_ptr<IMethodState> GetState() const override
	{
		return std::make_shared<GoldenRatioState>(a, b, c, d, yc, yd);
	}

private:
	double c, d;
	double yc, yd;

	static constexpr double firstConst = (3 - std::sqrt(5)) / 2;
	static constexpr double secondConst = (std::sqrt(5) - 1) / 2;
};
