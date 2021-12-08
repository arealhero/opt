#pragma once

#include <Methods/IMethod.h>

#include <States/FibonacciState.h>

#include <vector>
#include <string>
#include <cmath>

class FibonacciMethod : public IMethod
{
public:
	using IMethod::IMethod;

	static std::string GetTitle()
	{
		return { "Fibonacci" };
	}
	static std::vector<std::string> GetColumnNames()
	{
		return { "a", "b", "c", "d", "f(c)", "f(d)"};
	}

	void Init() override
	{
		n = 0;
		while (Fib(n + 2) < (b - a) / eps)
		{
			++n;
		}
		
		i = 1;
		c = a + (b - a) * (Fib(n) / Fib(n + 2));
		d = a + (b - a) * (Fib(n + 1) / Fib(n + 2));

		yc = f(c);
		yd = f(d);
	}

	bool Iterate() override
	{
		if (i >= n) return false;

		if (yc <= yd)
		{
			b = d;
			d = c;
			c = a + (b - a) * (Fib(n - i) / Fib(n + 2 - i));

			yd = yc;
			yc = f(c);
		}
		else
		{
			a = c;
			c = d;
			d = a + (b - a) * (Fib(n + 1 - i) / Fib(n + 2 - i));

			yc = yd;
			yd = f(d);
		}

		++i;

		return true;
	}

	double GetResult() override
	{
		return a + (b - a) / 2;
	}

	std::shared_ptr<IMethodState> GetState() const override
	{
		return std::make_shared<FibonacciState>(a, b, c, d, yc, yd);
	}

private:
	int i, n;

	double c, d;
	double yc, yd;

	static double Fib(int n)
	{
		static std::vector<double> memoize = { 1, 1 };

		if (n - 1 < memoize.size())
		{
			return memoize[n - 1];
		}
		else
		{
			return memoize.emplace_back(Fib(n - 1) + Fib(n - 2));
		}
	}
};

