#pragma once

#include <States/IState.h>

class GradientState : public IState
{
public:
	GradientState(int precision, double eps,
			const Vector& current, double fcurrent,
			const Vector& currentGrad,
			const Vector& next, double fnext,
			const Vector& nextGrad, double alpha)
		: IState(precision, eps)

		, current(current)
		, fcurrent(fcurrent)
		, currentGrad(currentGrad)

		, next(next)
		, fnext(fnext)
		, nextGrad(nextGrad)

		, alpha(alpha)
	{}

	using IState::ToString;

	std::vector<std::string> ToString(
			std::shared_ptr<IState> prevState) const override
	{
		std::shared_ptr<GradientState> prev
			= std::dynamic_pointer_cast<GradientState>(prevState);

		std::vector<std::string> values;
		values.reserve(11);

		if (prevState != nullptr)
		{
			ToString(values, current, prev->current);
			ToString(values, fcurrent, prev->fcurrent);
			ToString(values, currentGrad, prev->currentGrad);

			ToString(values, next, prev->next);
			ToString(values, fnext, prev->fnext);
			ToString(values, nextGrad, prev->nextGrad);

			ToString(values, alpha, prev->alpha);
		}
		else
		{
			ToString(values, current);
			ToString(values, fcurrent);
			ToString(values, currentGrad);

			ToString(values, next);
			ToString(values, fnext);
			ToString(values, nextGrad);

			ToString(values, alpha);
		}

		return values;
	}

private:
	Vector current;
	double fcurrent;
	Vector currentGrad;

	Vector next;
	double fnext;
	Vector nextGrad;

	double alpha;
};

