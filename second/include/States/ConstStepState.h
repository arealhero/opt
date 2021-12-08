#pragma once

#include <States/IState.h>

class ConstStepState : public IState
{
public:
	ConstStepState(int precision, double eps,
			const Vector& current, const Vector& currentGrad,
			const Vector& next, const Vector& nextGrad)
		: IState(precision, eps)

		, current(current)
		, currentGrad(currentGrad)

		, next(next)
		, nextGrad(nextGrad)
	{}

	using IState::ToString;

	std::vector<std::string> ToString(
			std::shared_ptr<IState> prevState) const override
	{
		std::shared_ptr<ConstStepState> prev
			= std::dynamic_pointer_cast<ConstStepState>(prevState);

		std::vector<std::string> values;
		values.reserve(8);

		if (prevState != nullptr)
		{
			ToString(values, current, prev->current);
			ToString(values, currentGrad, prev->currentGrad);

			ToString(values, next, prev->next);
			ToString(values, nextGrad, prev->nextGrad);
		}
		else
		{
			ToString(values, current);
			ToString(values, currentGrad);

			ToString(values, next);
			ToString(values, nextGrad);
		}

		return values;
	}

private:
	Vector current;
	Vector currentGrad;

	Vector next;
	Vector nextGrad;
};

