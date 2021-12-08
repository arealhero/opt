#pragma once

#include <TargetFunction.h>

#include <memory>

struct Settings
{
	Settings(double a, double b, int precision,
			double (*f)(double),
			double (*df)(double),
			double (*ddf)(double))
		: a(a)
		, b(b)
		, eps(std::pow(10, -(precision)))
		, precision(precision)

		, f(f)
		, df(df)
		, ddf(ddf)
	{}

	void ClearCalls()
	{
		f.ClearCalls();
		df.ClearCalls();
		ddf.ClearCalls();
	}

	double a, b, eps;
	int precision;
	TargetFunction f, df, ddf;
};

