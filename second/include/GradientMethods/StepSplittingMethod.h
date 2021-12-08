#pragma once

#include <GradientMethods/IGradientMethod.h>

#include <string>
#include <vector>

class StepSplittingMethod : public IGradientMethod
{
public:
	using IGradientMethod::IGradientMethod;

	static std::string GetTitle()
	{
		return { "Step splitting method" };
	}
	static std::vector<std::string> GetColumnNames()
	{
		return IGradientMethod::GetColumnNames();
	}

	void Iterate() override
	{
		if (!isSearching)
		{
			current = next;
			fcurrent = fnext;
			currentGrad = nextGrad;
			currentGradNorm = currentGrad.Norm();

			alpha = startAlpha;

			next = current - alpha * currentGrad;
			fnext = f(next);

			isSearching = true;
		}
		else
		{
			auto n = currentGradNorm;
			if (fnext - fcurrent > -alpha * delta * n*n)
			{
				alpha *= lambda;

				next = current - alpha * currentGrad;
				fnext = f(next);
			}
			else
			{
				isSearching = false;

				alpha *= n;
				nextGrad = grad(next);
			}
		}

		/* FindNext(); */
		/* nextGrad = grad(next); */
	}

	bool IsEnded() const override
	{
		return IGradientMethod::IsEnded() && !isSearching;
	}

protected:
	void FindNext() override
	{
		alpha = startAlpha;

		next = current - alpha * currentGrad;
		fnext = f(next);
		auto n = currentGrad.Norm();

		while (fnext - fcurrent > -alpha * delta * n*n)
		{
			alpha *= lambda;

			next = current - alpha * currentGrad;
			fnext = f(next);
		}

		/* next moves in currentGrad direction by alpha*n */
		alpha *= n;
	}

private:
	double delta = 0.5;
	double lambda = 0.5;
	double startAlpha = 1.0;

	double currentGradNorm = 0.0;
	bool isSearching = false;
};

