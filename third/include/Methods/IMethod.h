#pragma once

#include <Settings.h>

#include <string>
#include <vector>

class IMethod
{
public:
	explicit IMethod(Settings& settings)
		: precision(settings.precision)
		, eps(settings.eps)
		, f(settings.f)
		, grad(settings.grad)
	{}
	IMethod(int precision, double eps,
		Function<double, Vector2d>& f,
		Function<Vector2d, Vector2d>& grad)
		: precision(precision)
		, eps(eps)
		, f(f)
		, grad(grad)
	{}

	virtual ~IMethod() = default;

	virtual std::string GetName() const = 0;
	virtual std::vector<std::string> GetColumnNames() const = 0;

	virtual void Init(const Vector2d& start) = 0;

	Vector2d Run()
	{
		do
		{
			FastIterate();
		}
		while (!IsEnded());

		return GetResult();
	}
	virtual void FastIterate() = 0;
	virtual void Iterate()
	{
		FastIterate();
	}

	virtual bool IsEnded() const = 0;

	virtual Vector2d GetResult() const = 0;
	virtual std::vector<std::string> GetState() = 0;

protected:
	int precision;
	double eps;

	Function<double, Vector2d>& f;
	Function<Vector2d, Vector2d>& grad;
};

