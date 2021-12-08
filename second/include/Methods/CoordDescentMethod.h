#pragma once

#include <Methods/IMethod.h>
#include <States/CoordDescentState.h>

#include <iostream>
#include <vector>
#include <string>
#include <cmath>

class CoordDescentMethod : public IMethod
{
public:
	explicit CoordDescentMethod(Settings& settings)
		: IMethod(settings)
		, hx(2.0)
		, hy(2.0)
		, dir(true)
	{}

	static std::string GetTitle()
	{
		return { "Coordinate descent method" };
	}
	static std::vector<std::string> GetColumnNames()
	{
		return {
			"dir", "c_x", "c_y", "f(c)",
				"n_x", "n_y", "f(n)",
				"h_x", "h_y",
		};
	}

	void Init(const Vector& start) override
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

	Vector GetResult() const override
	{
		return center;
	}

	std::shared_ptr<IState> GetState() const override
	{
		return std::make_shared<CoordDescentState>(precision, eps,
				dir, center, fcenter,
				next, fnext, hx, hy);
	}

private:
	Vector center;
	double fcenter; /* TODO: rename */

	Vector next;
	double fnext;

	double hx;
	double hy;

	bool dir; /* true -- x, false -- y */
	bool stepDirFlipped = false;
	bool shouldReverse = false;
	bool delay = false;
	bool going = false;

	void Inc(Vector& vec)
	{
		dir
			? vec.x += hx
			: vec.y += hy;
	}
	void DecStep()
	{
		dir
			? hx /= (2.0 + eps)
			: hy /= (2.0 + eps);
	}

	void FlipStepDirection()
	{
		dir
			? hx = -hx
			: hy = -hy;
	}
};

