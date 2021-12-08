#pragma once

#include <Benchmark/BenchmarkStateData.h>
#include <Benchmark/BenchmarkResultData.h>

#include <ostream>
#include <vector>

class IPrinter
{
public:
	virtual void PrintStateData(const BenchmarkStateData& stateData) = 0;
	virtual void PrintResultData(const std::vector<BenchmarkResultData>& resultData) = 0;
};

