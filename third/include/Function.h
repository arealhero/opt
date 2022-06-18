#pragma once

#include <functional>

template <typename RetType, typename ArgType>
class Function
{
public:
	Function() = default;
	Function(const std::function<RetType(ArgType)>& func)
		: m_func(func)
		, m_calls(0)
	{}

	RetType operator()(ArgType arg)
	{
		++m_calls;
		return m_func(arg);
	}

	std::size_t GetCalls() const
	{
		return m_calls;
	}

	void ResetCalls()
	{
		m_calls = 0;
	}

private:
	std::function<RetType(ArgType)> m_func;
	/* RetT (*m_func)(ArgT); */
	std::size_t m_calls;
};

