#pragma once

#include <Vector.h>

#include <string>
#include <cstddef>

struct BenchmarkResultData
{
	std::string title;

	Vector minArg;
	std::size_t fCalls, gradCalls;
	/* double result; /1* TODO: rename *1/ */
	/* std::size_t fCalls, dfCalls, ddfCalls; */
};

