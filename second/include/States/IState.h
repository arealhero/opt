#pragma once

#include <Settings.h>
#include <Vector.h>

#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <memory>
#include <string>

class IState
{
public:
	explicit IState(int precision, double eps)
		: precision(precision)
		, eps(eps)
	{}

	virtual std::vector<std::string> ToString(
			std::shared_ptr<IState> prevState) const = 0;

protected:
	int precision;
	double eps;

	void ToString(std::vector<std::string>& values,
			const Vector& vec) const
	{
		ToString(values, vec.x);
		ToString(values, vec.y);
	}
	void ToString(std::vector<std::string>& values,
			double number) const
	{
		auto current = ConvertToString(number);
		values.push_back(current);
	}

	void ToString(std::vector<std::string>& values,
			const Vector& vec, const Vector& prev) const
	{
		if (vec.x == prev.x && vec.y == prev.y)
		{
			values.push_back("-//-");
			values.push_back("-//-");
		}
		else
		{
			ToString(values, vec.x, prev.x);
			ToString(values, vec.y, prev.y);
		}
	}

	void ToString(std::vector<std::string>& values,
			double number, double prevNumber) const
	{
		if (number == prevNumber)
		{
			values.push_back("-//-");
			return;
		}

		auto current = ConvertToString(number);
		auto prev = ConvertToString(prevNumber);

		if (current == prev)
		{
			current = ConvertToString(prevNumber - number, true);
		}

		values.push_back(current);
	}

	std::string ConvertToString(double number,
			bool isDelta = false) const
	{
		std::stringstream str;

		if (isDelta)
			str << std::showpos << "d";
		str << std::setprecision(precision) << std::scientific
			<< number;

		return str.str();
	}
};

