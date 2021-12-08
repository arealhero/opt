#pragma once

#include <ostream>
#include <vector>

class IMethodState
{
public:
	virtual std::vector<double> GetValues() const = 0;
};

