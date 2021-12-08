#pragma once

#include <cstddef>

class TargetFunction
{
public:
	TargetFunction(double (*func)(double))
		: func(func)
		, m_calls(0)
	{}

	double operator()(double x)
	{
		++m_calls;
		return func(x);
	}

	std::size_t GetCalls() const
	{
		return m_calls;
	}

	void ClearCalls()
	{
		m_calls = 0;
	}

private:
	double (*func)(double);
	std::size_t m_calls;
};

