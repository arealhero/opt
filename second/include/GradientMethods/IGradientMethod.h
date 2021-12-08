#pragma once

#include <Methods/IMethod.h>
#include <States/GradientState.h>

#include <Settings.h>

#include <vector>
#include <string>

class IGradientMethod : public IMethod
{
public:
	explicit IGradientMethod(Settings& settings)
		: IMethod(settings)
	{ /* Init(settings.start); */ }

	static std::vector<std::string> GetColumnNames()
	{
		return {
			"cur_x", "cur_y", "f(cur)",
				"grad f(cur) x", "grad f(cur) y",
			"next_x", "next_y", "f(next)",
				"grad f(next) x", "grad f(next) y",
			"alpha"
		};
	}

	void Init(const Vector& start) override
	{
		next = start;
		fnext = f(start);
		nextGrad = grad(start);

		current = next;
		fcurrent = fnext;
		currentGrad = nextGrad;
	}
	void FastIterate() override
	{
		current = next;
		fcurrent = fnext;
		currentGrad = nextGrad;

		FindNext();
		nextGrad = grad(next);
	}

	Vector GetResult() const override
	{
		return next;
	}

	bool IsEnded() const override
	{
		auto dp = Vector::Dot(currentGrad, nextGrad);
		return dp < 0 && alpha <= eps;
	}

	std::shared_ptr<IState> GetState() const override
	{
		return std::make_shared<GradientState>(precision, eps,
				current, fcurrent, currentGrad,
				next, fnext, nextGrad,
				alpha);
	}

protected:
	double alpha = 0.0;

	Vector current;
	double fcurrent;
	Vector currentGrad;

	Vector next;
	double fnext;
	Vector nextGrad;

	virtual void FindNext() = 0;
};

