#pragma once

#include <Settings.h>
#include <States/IState.h>

#include <memory>

class IMethod
{
public:
	explicit IMethod(Settings& settings)
		: precision(settings.precision)
		, eps(settings.eps)
		, f(settings.f)
		, grad(settings.grad)
	{}

	virtual ~IMethod() = default;

	virtual void Init(const Vector& start) = 0;

	virtual void FastIterate() = 0;
	virtual void Iterate()
	{
		FastIterate();
	}

	virtual bool IsEnded() const = 0;

	virtual Vector GetResult() const = 0;
	virtual std::shared_ptr<IState> GetState() const = 0;

protected:
	int precision;
	double eps;

	Function<double, Vector>& f;
	Function<Vector, Vector>& grad;

};

