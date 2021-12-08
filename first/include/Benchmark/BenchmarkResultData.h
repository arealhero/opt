#pragma once

#include <string>
#include <cstddef>

struct BenchmarkResultData
{
	std::string title;

	double result; /* TODO: rename */
	std::size_t fCalls, dfCalls, ddfCalls;
};

