#pragma once

#include <Methods/IMethod.h>

#include <StateBuilder.h>

#include <memory>

struct CoordDescentState
{
	Vector2d center;
	double fcenter;

	Vector2d next;
	double fnext;

	double hx;
	double hy;
};

class CoordDescentMethod : public IMethod
{
public:
	using IMethod::IMethod;

	std::string GetName() const override
	{
		return { "Coordinate descent method" };
	}
	std::vector<std::string> GetColumnNames() const override
	{
		return {
			"dir", "c_x", "c_y", "f(c)",
				"n_x", "n_y", "f(n)",
				"hx", "hy"
		};
	}

	void Init(const Vector2d& start) override
	{
		center = start;
		fcenter = f(start);

		next = center;
		fnext = fcenter;
	}

	void FastIterate() override
	{
		/* TODO: reimplement
		 *
		 * MoveTriad();
		 * DecStep();
		 * dir = !dir;
		 * */
		Iterate();
	}

	void Iterate() override
	{
		if (shouldReverse)
		{
			FlipStepDirection();
			shouldReverse = false;

			next = center;
			fnext = fcenter;
		}
		else if (!delay)
		{
			center = next;
			fcenter = fnext;
		}

		if (delay)
		{
			delay = false;
			going = false;
			stepDirFlipped = false;

			DecStep();
			dir = !dir;

			next = center;
			fnext = fcenter;
		}

		Inc(next);
		fnext = f(next);

		if (fnext >= fcenter)
		{
			if (!stepDirFlipped && !going)
			{
				stepDirFlipped = true;
				shouldReverse = true;
				return;
			}

			delay = true;
			return;
		}

		going = true;
	}

	bool IsEnded() const override
	{
		return std::max(std::abs(hx), std::abs(hy)) <= eps;
		/* return std::abs(hx) + std::abs(hy) <= eps; */
	}

	Vector2d GetResult() const override
	{
		return center;
	}

	std::vector<std::string> GetState() override
	{
		StateBuilder builder{precision, eps};

		builder.Add(dir ? "x" : "y");

		if (m_prevState == nullptr)
		{
			m_prevState = std::make_unique<CoordDescentState>();

			builder.Add(center);
			m_prevState->center = center;
			builder.Add(fcenter);
			m_prevState->fcenter = fcenter;

			builder.Add(next);
			m_prevState->next = next;
			builder.Add(fnext);
			m_prevState->fnext = fnext;

			builder.Add(hx);
			m_prevState->hx = hx;
			builder.Add(hy);
			m_prevState->hy = hy;
		}
		else
		{
			builder.Add(center, m_prevState->center);
			m_prevState->center = center;
			builder.Add(fcenter, m_prevState->fcenter);
			m_prevState->fcenter = fcenter;

			builder.Add(next, m_prevState->next);
			m_prevState->next = next;
			builder.Add(fnext, m_prevState->fnext);
			m_prevState->fnext = fnext;

			builder.Add(hx, m_prevState->hx);
			m_prevState->hx = hx;
			builder.Add(hy, m_prevState->hy);
			m_prevState->hy = hy;
		}

		return builder.GetState();
	}

private:
	std::unique_ptr<CoordDescentState> m_prevState = nullptr;

	Vector2d center;
	double fcenter; /* TODO: rename */

	Vector2d next;
	double fnext; /* TODO: rename */

	double hx = 2.0;
	double hy = 2.0;

	bool dir = true; /* true -- x, false -- y */
	bool stepDirFlipped = false;
	bool shouldReverse = false;
	bool delay = false;
	bool going = false;

	void Inc(Vector2d& v)
	{
		dir
			? v.x += hx
			: v.y += hy;
	}

	const double m_stepDecRate = 2.0 + eps;
	void DecStep()
	{
		dir
			? hx /= m_stepDecRate
			: hy /= m_stepDecRate;
	}

	void FlipStepDirection()
	{
		dir
			? hx = -hx
			: hy = -hy;
	}
};

