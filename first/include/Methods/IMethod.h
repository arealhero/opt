#pragma once

#include <Settings.h>

#include <States/IMethodState.h>

class IMethod
{
public:
	IMethod(std::shared_ptr<Settings> settings)
		: a(settings->a)
		, b(settings->b)
		, eps(settings->eps)

		, f(settings->f)
		, df(settings->df)
		, ddf(settings->ddf)
	{}

	virtual void Init() = 0;
	virtual bool Iterate() = 0;
	virtual double GetResult() = 0;

	virtual std::shared_ptr<IMethodState> GetState() const = 0;

protected:
	double a, b, eps;
	TargetFunction& f, & df, & ddf;
};

