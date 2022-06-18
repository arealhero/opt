#pragma once

#include <Methods/CoordDescentMethod.h>
#include <Methods/IMethod.h>

#include <StateBuilder.h>

#include <cstddef>

/* TODO: remove */
#include <iostream>
#include <thread>
#include <chrono>

struct ExternalPenaltyState
{
	Vector2d center;
	double hcenter;
	double r;
};

class ExternalPenaltyMethod : public IMethod
{
public:
	explicit ExternalPenaltyMethod(Settings& settings)
		: IMethod(settings)
		, g(settings.g)
		, ggrad(settings.ggrad)
	{
		H = std::function<double(Vector2d)>([&](Vector2d p) -> double
		{
			auto val = std::max(0.0, g(p));
			return val * val;
		});

		gradH = std::function<Vector2d(Vector2d)>([&](Vector2d p) -> Vector2d
		{
			return 2.0 * ggrad(p) * std::max(0.0, g(p));
		});
	}

	using AbsoluteMethodType = CoordDescentMethod;

	std::string GetName() const override
	{
		return { "External penalty method" };
	}
	std::vector<std::string> GetColumnNames() const override
	{
		return { "c_x", "c_y", "H(c)", "r",

			"dir", "c_x", "c_y", "f(c)",
			"n_x", "n_y", "f(n)",
			"hx", "hy"
		};
	}

	void Init(const Vector2d& start) override
	{
		center = start;
		hcenter = H(start);
	}

	void FastIterate() override
	{
		const double r = std::pow(10.0, k);
		k += 1;

		auto phi = Function<double, Vector2d>([&](Vector2d p) -> double
		{
			return f(p) + r * H(p);
		});

		auto dphi = Function<Vector2d, Vector2d>([&](Vector2d p) -> Vector2d
		{
			return grad(p) + r * gradH(p);
		});

		auto method = std::make_unique<AbsoluteMethodType>(precision,
				eps, phi, dphi);
		method->Init(center);

		center = method->Run();
		hcenter = H(center);
	}
	void Iterate() override
	{
		if (m_method == nullptr)
		{
			phi = Function<double, Vector2d>([&](Vector2d p) -> double
			{
				return f(p) + r * H(p);
			});

			gradPhi = Function<Vector2d, Vector2d>([&](Vector2d p) -> Vector2d
			{
				return grad(p) + r * gradH(p);
			});

			m_method = std::make_unique<AbsoluteMethodType>(precision,
					eps, phi, gradPhi);
			m_method->Init(center);
		}
		else
		{
			m_method->Iterate();

			if (m_method->IsEnded())
			{
				center = m_method->GetResult();
				hcenter = H(center);

				r = std::pow(10.0, k);
				k += 1;

				m_method = nullptr;
			}
		}
	}

	bool IsEnded() const override
	{
		return m_method == nullptr && hcenter <= eps;
	}

	Vector2d GetResult() const override
	{
		return center;
	}

	std::vector<std::string> GetState() override
	{
		StateBuilder builder{precision, eps};

		if (m_prevState == nullptr)
		{
			m_prevState = std::make_unique<ExternalPenaltyState>();

			builder.Add(center);
			m_prevState->center = center;

			builder.Add(hcenter);
			m_prevState->hcenter = hcenter;

			builder.Add(r);
			m_prevState->r = r;
		}
		else
		{
			builder.Add(center, m_prevState->center);
			m_prevState->center = center;

			builder.Add(hcenter, m_prevState->hcenter);
			m_prevState->hcenter = hcenter;

			builder.Add(r, m_prevState->r);
			m_prevState->r = r;
		}

		auto state = builder.GetState();
		std::vector<std::string> substate = {
			"-", "-", "-", "-", "-", "-",
			"-", "-", "-"
		};

		if (m_method != nullptr)
		{
			substate = m_method->GetState();
		}

		state.insert(state.end(),
				substate.begin(), substate.end());

		return state;
	}

private:
	Vector2d center;
	double hcenter;

	double r = 1;
	double k = 1;

	Function<double, Vector2d> g;
	Function<Vector2d, Vector2d> ggrad;

	Function<double, Vector2d> H;
	Function<Vector2d, Vector2d> gradH;

	Function<double, Vector2d> phi;
	Function<Vector2d, Vector2d> gradPhi;

	std::unique_ptr<AbsoluteMethodType> m_method = nullptr;
	std::unique_ptr<ExternalPenaltyState> m_prevState = nullptr;
};

