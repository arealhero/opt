#pragma once

#include <GradientMethods/IGradientMethod.h>

class DivergeSeriesMethod : public IGradientMethod
{
public:
	explicit DivergeSeriesMethod(Settings& settings)
		: IGradientMethod(settings)
	{
		k = 1.0;
	}

	static std::string GetTitle()
	{
		return { "Diverge series method" };
	}
	static std::vector<std::string> GetColumnNames()
	{
		return IGradientMethod::GetColumnNames();
	}

	void FindNext() override
	{
		alpha = std::pow(k, -1.3);
		k += 1;

		auto currentGradNormalized = currentGrad / currentGrad.Norm();

		next = current - alpha * currentGradNormalized;
		fnext = f(next);
	}

private:
	double k;
};

