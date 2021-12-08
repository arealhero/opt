#pragma once

#include <Methods/IMethod.h>

#include <States/TangentState.h>

#include <vector>
#include <string>
#include <cmath>

class TangentMethod : public IMethod
{
public:
	using IMethod::IMethod;

	static std::string GetTitle()
	{
		return { "Tangent" };
	}
	static std::vector<std::string> GetColumnNames()
	{
		return { "a", "f(a)", "f'(a)",
			"b", "f(b)", "f'(b)",
			"c", "f'(c)"
		};
	}

	void Init() override
	{
		fa = f(a);
		da = df(a);

		fb = f(b);
		db = df(b);

		c = CalculateIntersectionPoint(a, fa, da, b, fb, db);
		dc = df(c);
		adc = std::abs(dc);
	}

	bool Iterate() override
	{
		if (adc <= eps) return false;

		if (dc > 0)
		{
			b = c;
			fb = f(b);
			db = dc;
		}
		else if (dc < 0)
		{
			a = c;
			fa = f(a);
			da = dc;
		}
		else
		{
			return false;
		}

		c = CalculateIntersectionPoint(a, fa, da, b, fb, db);
		dc = df(c);
		adc = std::abs(dc);

		return true;
	}

	double GetResult() override
	{
		if (dc == 0)
			return c;
		else
			return a + (b - a) / 2;
	}

	std::shared_ptr<IMethodState> GetState() const override
	{
		return std::make_shared<TangentState>(a, fa, da, b, fb, db, c, dc);
	}

private:
	double fa, da;
	double fb, db;
	double c, dc, adc;

	static double CalculateIntersectionPoint(double x0,
			double fx0, double dx0, double x1,
			double fx1, double dx1)
	{
		return (fx1 - dx1 * x1 - fx0 + dx0 * x0)
			/ (dx0 - dx1);
	}
};

