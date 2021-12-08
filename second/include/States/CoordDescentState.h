#pragma once

#include <Vector.h>

#include <string>
#include <vector>
#include <memory>

class CoordDescentState : public IState
{
public:
	CoordDescentState(int precision, double eps,
			bool dir, const Vector& center, double fcenter,
			const Vector& next, double fnext,
			double hx, double hy)
		: IState(precision, eps)
		, dir(dir)

		, center(center)
		, fcenter(fcenter)

		, next(next)
		, fnext(fnext)

		, hx(hx)
		, hy(hy)
	{}

	std::vector<std::string> ToString(
			std::shared_ptr<IState> prevState) const override
	{
		std::shared_ptr<CoordDescentState> prev
			= std::dynamic_pointer_cast<CoordDescentState>(prevState);

		std::vector<std::string> values;
		values.reserve(9);

		values.push_back(dir ? "x" : "y");

		if (prevState != nullptr)
		{
			IState::ToString(values, center, prev->center);
			IState::ToString(values, fcenter, prev->fcenter);

			IState::ToString(values, next, prev->next);
			IState::ToString(values, fnext, prev->fnext);

			IState::ToString(values, hx, prev->hx);
			IState::ToString(values, hy, prev->hy);
		}
		else
		{
			IState::ToString(values, center);
			IState::ToString(values, fcenter);

			IState::ToString(values, next);
			IState::ToString(values, fnext);

			IState::ToString(values, hx);
			IState::ToString(values, hy);
		}

		return values;
	}

private:
	bool dir;

	Vector center;
	double fcenter;

	Vector next;
	double fnext;

	double hx, hy;
};

