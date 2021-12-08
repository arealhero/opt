#pragma once

#include <GradientMethods/IGradientMethod.h>

#include <States/ConstStepState.h>

class ConstStepMethod : public IGradientMethod
{
public:
	explicit ConstStepMethod(Settings& settings)
		: IGradientMethod(settings)
	{
		alpha = eps;
	}

	static std::string GetTitle()
	{
		return { "Const step method" };
	}

	static std::vector<std::string> GetColumnNames()
	{
		return {
			"cur_x", "cur_y", "grad f(cur) x", "grad f(cur) y",
			"next_x", "next_y", "grad f(next) x", "grad f(next) y",
		};
		/* return IGradientMethod::GetColumnNames(); */
	}

	void Init(const Vector& start) override
	{
		next = start;
		fnext = 0.0; /* unused */
		nextGrad = grad(start);

		current = next;
		fcurrent = 0.0; /* unused */
		currentGrad = nextGrad;
	}

	void FindNext() override
	{
		auto currentGradNormalized = currentGrad / currentGrad.Norm();

		next = current - alpha * currentGradNormalized;
		/* fnext = f(next); */
	}

	std::shared_ptr<IState> GetState() const override
	{
		return std::make_shared<ConstStepState>(precision, eps,
				current, currentGrad, next, nextGrad);
	}
};

