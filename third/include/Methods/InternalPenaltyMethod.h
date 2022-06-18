#pragma once

#include <Methods/CoordDescentMethod.h>
#include <Methods/IMethod.h>

#include <StateBuilder.h>

#include <cstddef>

/* TODO: remove */
#include <iostream>
#include <thread>
#include <chrono>

class InternalPenaltyMethod : public IMethod
{
public:
	explicit InternalPenaltyMethod(Settings& settings)
		: IMethod(settings)
		, g(settings.g)
		, ggrad(settings.ggrad)
	{
		B = std::function<double(Vector2d)>([&](Vector2d p) -> double
		{
			auto val = std::min(0.0, g(p));
			return 1.0 / (val * val);
			/* return -1.0 / val; */
		});

		gradB = std::function<Vector2d(Vector2d)>([&](Vector2d p) -> Vector2d
		{
			auto val = g(p);
			auto gradVal = ggrad(p);

			return gradVal / (val*val);
			/* return -1.0 / g(p); */
		});
	}

	using AbsoluteMethodType = CoordDescentMethod;

	std::string GetName() const override
	{
		return { "Internal penalty method" };
	}
	std::vector<std::string> GetColumnNames() const override
	{
		return { "c_x", "c_y" };
	}

	void Init(const Vector2d& start) override
	{
		center = start;
		Bcenter = B(start);
	}

	void FastIterate() override
	{
		auto phi = Function<double, Vector2d>([&](Vector2d p) -> double
		{
			return f(p) + t * B(p);
		});

		auto dphi = Function<Vector2d, Vector2d>([&](Vector2d p) -> Vector2d
		{
			return grad(p) + t * gradB(p);
		});

		auto method = std::make_unique<AbsoluteMethodType>(precision,
				eps, phi, dphi);
		method->Init(center);

		center = method->Run();
		Bcenter = B(center);

		t /= 10.0;
	}

	bool IsEnded() const override
	{
		return t * Bcenter <= eps;
	}

	Vector2d GetResult() const override
	{
		return center;
	}

	std::vector<std::string> GetState() override
	{
		StateBuilder builder{precision, eps};

		builder.Add(center);

		return builder.GetState();
		/* return {}; */
	}

private:
	Vector2d center;
	double Bcenter;

	Function<double, Vector2d> g;
	Function<Vector2d, Vector2d> ggrad;

	Function<double, Vector2d> B;
	Function<Vector2d, Vector2d> gradB;

	double t = 1;
};

