#pragma once

#include <States/IState.h>

#include <vector>
#include <string>
#include <memory>

struct BenchmarkStateData
{
	std::string title;
	std::vector<std::string> columnNames;
	std::vector<std::shared_ptr<IState>> states;
};


