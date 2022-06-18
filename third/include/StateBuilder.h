#pragma once

#include <Vector2d.h>

#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <utility>

class StateBuilder
{
public:
	StateBuilder(int precision, double eps)
		: m_precision(precision)
		, m_eps(eps)
	{}

	void Add(const std::string& str)
	{
		m_state.push_back(str);
	}

	void Add(double current)
	{
		auto currentStr = ToString(current);
		m_state.push_back(currentStr);
	}
	void Add(double current, double prev)
	{
		if (prev == current)
		{
			m_state.push_back("-//-");
			return;
		}

		auto prevStr = ToString(prev);
		auto currentStr = ToString(current);

		if (prevStr == currentStr)
		{
			currentStr = ToString(current - prev, true);
		}

		m_state.push_back(currentStr);
	}

	void Add(const Vector2d& current)
	{
		auto xStr = ToString(current.x);
		auto yStr = ToString(current.y);

		m_state.push_back(xStr);
		m_state.push_back(yStr);
	}
	void Add(const Vector2d& current, const Vector2d& prev)
	{
		if (prev == current)
		{
			m_state.push_back("-//-");
			m_state.push_back("-//-");
			return;
		}

		Add(current);
	}

	void Add(std::size_t value)
	{
		auto valueStr = ToString(value);
		m_state.push_back(valueStr);
	}

	std::vector<std::string> GetState() const
	{
		return m_state;
	}

private:
	std::vector<std::string> m_state;

	int m_precision;
	double m_eps;

	std::string ToString(double value, bool isDelta = false) const
	{
		std::stringstream str;

		str << std::setprecision(m_precision) << std::scientific;
		if (isDelta)
		{
			str << std::showpos << "d";
		}

		str << value;

		return str.str();
	}

	std::string ToString(std::size_t value) const
	{
		std::stringstream str;
		str << value;
		return str.str();
	}

	std::string ToString(const Vector2d& v)
	{
		std::stringstream str;
		str << v;
		return str.str();
	}
};

