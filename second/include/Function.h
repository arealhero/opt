#pragma once

#include <cstdint>

template<typename RetT, typename ArgT>
class Function
{
public:
	Function(RetT (*func)(ArgT))
		: m_func(func)
		, m_calls(0)
	{}

	RetT operator()(ArgT p)
	{
		++m_calls;
		return m_func(p);
	}

	std::size_t GetCalls() const
	{
		return m_calls;
	}

	void Reset()
	{
		m_calls = 0;
	}

private:
	RetT (*m_func)(ArgT);
	std::size_t m_calls;
};

