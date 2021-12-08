#include <iostream>
#include <fstream>
#include <memory>
#include <cmath>

#include <Benchmark.h>
#include <Printers/TablePrinter.h>

#include <Methods/PassiveSearchMethod.h>

#include <Methods/DichotomyMethod.h>
#include <Methods/GoldenRatioMethod.h>
#include <Methods/FibonacciMethod.h>
#include <Methods/TangentMethod.h>
#include <Methods/NewtonRaphsonMethod.h>
#include <Methods/SecantLinesMethod.h>

constexpr bool USE_DELTAS = true;

double f(double x)
{
	return std::sin(8 * x) + std::exp(9 * x)
		+ 8 * x * x + 9 * x + 10 + std::pow(x, 4.0f);
}

double df(double x)
{
	return 8 * std::cos(8 * x) + 9 * std::exp(9 * x)
		+ 16 * x + 9 + 4 * std::pow(x, 3.0f);
}

double ddf(double x)
{
	return -64 * std::sin(8 * x) + 81 * std::exp(9 * x)
		+ 16 + 12 * std::pow(x, 2.0f);
}

void BenchmarkPassiveSearch(const std::string& filename,
		std::shared_ptr<Settings> settings)
{
	std::ofstream fout{filename};

	std::shared_ptr<IPrinter> printer
		= std::make_shared<TablePrinter>(fout, settings, USE_DELTAS);

	Benchmark benchmark{settings};
	benchmark.Run<PassiveSearchMethod>();
	benchmark.PrintResults(printer);
}

void BenchmarkOtherMethods(const std::string& filename,
		std::shared_ptr<Settings> settings)
{
	std::ofstream fout{filename};

	std::shared_ptr<IPrinter> printer
		= std::make_shared<TablePrinter>(fout, settings, USE_DELTAS);

	Benchmark benchmark{settings};

	benchmark.Run<DichotomyMethod>();
	benchmark.Run<GoldenRatioMethod>();
	benchmark.Run<FibonacciMethod>();
	benchmark.Run<TangentMethod>();
	benchmark.Run<NewtonRaphsonMethod>();
	benchmark.Run<SecantLinesMethod>();

	benchmark.PrintResults(printer);
}

int main(int argc, char* argv[])
{
	double a = -0.5;
	double b = 5.0;
	int precision = 5;

	auto settings = std::make_shared<Settings>(a, b, precision, f, df, ddf);

	BenchmarkPassiveSearch("results/passive_search.txt", settings);
	BenchmarkOtherMethods("results/output.txt", settings);

	return EXIT_SUCCESS;
}

