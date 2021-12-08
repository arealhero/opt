#pragma once

#include <States/IMethodState.h>

#include <vector>
#include <string>
#include <memory>

struct BenchmarkStateData
{
	std::string title;
	std::vector<std::string> columnNames;
	std::vector<std::shared_ptr<IMethodState>> states;
};


