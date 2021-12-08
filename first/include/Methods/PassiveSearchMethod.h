#pragma once

#include <Methods/IMethod.h>

#include <States/PassiveSearchState.h>

#include <string>
#include <vector>

class PassiveSearchMethod : public IMethod
{
public:
	using IMethod::IMethod;

	static std::string GetTitle()
	{
		return { "Passive search" };
	}
	static std::vector<std::string> GetColumnNames()
	{
		return { "x", "f(x)", "min x", "min f(x)" };
	}

	void Init() override
	{
		x = a;
		y = f(x);
		minX = x;
		minY = y;
	}
	
	bool Iterate() override
	{
		x += eps;
		if (x > b) return false;

		y = f(x);
		if (y < minY)
		{
			minX = x;
			minY = y;
		}
		else
		{
			return false;
		}

		return true;
	}

	double GetResult() override
	{
		return minX;
	}

	std::shared_ptr<IMethodState> GetState() const override
	{
		return std::make_shared<PassiveSearchState>(x, y, minX, minY);
	}

private:
	double x, y;
	double minX, minY;
};

