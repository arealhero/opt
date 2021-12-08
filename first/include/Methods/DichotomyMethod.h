#pragma once

#include <Methods/IMethod.h>

#include <States/DichotomyState.h>

#include <vector>
#include <string>

class DichotomyMethod : public IMethod
{
public:
	using IMethod::IMethod;

	static std::string GetTitle()
	{
		return { "Dichotomy" };
	}
	static std::vector<std::string> GetColumnNames()
	{
		return { "a", "b", "mid", "c", "d", "f(c)", "f(d)"};
	}

	void Init() override
	{
		UpdateVariables();
	}

	bool Iterate() override
	{
		if ((b - a) / 2 <= eps)
			return false;

		if (yc <= yd)
			b = d;
		else
			a = c;

		UpdateVariables();

		return true;
	}

	double GetResult() override
	{
		return mid;
	}

	std::shared_ptr<IMethodState> GetState() const override
	{
		return std::make_shared<DichotomyState>(a, b, mid, c, d, yc, yd);
	}

private:
	double c, d, mid;
	double yc, yd;

	void UpdateVariables()
	{
		mid = a + (b - a) / 2;
		c = mid - eps / 2;
		d = mid + eps / 2;

		yc = f(c);
		yd = f(d);
	}
};

