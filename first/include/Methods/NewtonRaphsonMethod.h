#pragma once

#include <Methods/IMethod.h>

#include <States/NewtonRaphsonState.h>

#include <vector>
#include <string>
#include <cmath>

class NewtonRaphsonMethod : public IMethod
{
public:
	using IMethod::IMethod;

	static std::string GetTitle()
	{
		return { "Newton-Raphson" };
	}
	static std::vector<std::string> GetColumnNames()
	{
		return { "x", "f(x)", "f''(x)" };
	}

	void Init() override
	{
		x = a + (b - a) / 2;
		UpdateVariables();
	}

	bool Iterate() override
	{
		if (adx <= eps) return false;

		x = x - dx / ddx;
		UpdateVariables();

		return true;
	}

	double GetResult() override
	{
		return x;
	}

	std::shared_ptr<IMethodState> GetState() const override
	{
		return std::make_shared<NewtonRaphsonState>(x, dx, ddx);
	}

private:
	double x, dx, ddx, adx;

	void UpdateVariables()
	{
		dx = df(x);
		ddx = ddf(x);
		adx = std::abs(dx);
	}
};

