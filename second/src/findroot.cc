#include <Settings.h>

#include <GradientMethods/StepSplittingMethod.h>
#include <GradientMethods/ConstStepMethod.h>
#include <GradientMethods/DivergeSeriesMethod.h>
#include <Methods/CoordDescentMethod.h>

#include <Tables/Table.h>

#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <memory>
#include <cmath>

/*
 * f = 8
 * u = 9
 * o = 10
 * */
const double c_alpha = 8;
const double c_beta = 9;
const double c_gamma = 10;

double r1(Vector p)
{
	double x = p.x;
	double y = p.y;

	return c_beta * x*x - c_beta * y*y - 2.0 * c_gamma * x*y
		+ c_beta * x - c_alpha * y + c_gamma;
}
double r1dx(Vector p)
{
	double x = p.x;
	double y = p.y;

	return 2.0 * c_beta * x - 2.0 * c_gamma * y + c_beta;
}
double r1dy(Vector p)
{
	double x = p.x;
	double y = p.y;

	return -2.0 * c_beta * y - 2.0 * c_gamma * x - c_alpha;
}

double r2(Vector p)
{
	double x = p.x;
	double y = p.y;

	return 2.0 * c_beta * x*y + c_gamma * x*x - c_gamma * y*y
		+ c_alpha * x + c_beta * y + c_alpha;
}
double r2dx(Vector p)
{
	double x = p.x;
	double y = p.y;

	return 2.0 * c_beta * y + 2.0 * c_gamma * x + c_alpha;
}
double r2dy(Vector p)
{
	double x = p.x;
	double y = p.y;

	return 2.0 * c_beta * x - 2.0 * c_gamma * y + c_beta;
}

Function<double, Vector> f(
	[](Vector p) -> double
	{
		return std::hypot(r1(p), r2(p));
	}
);

Function<Vector, Vector> grad(
	[](Vector p) -> Vector
	{
		double r1_val = r1(p);
		double r2_val = r2(p);

		double r1dx_val = r1dx(p);
		double r1dy_val = r1dy(p);

		double r2dx_val = r2dx(p);
		double r2dy_val = r2dy(p);

		double n = std::hypot(r1_val, r2_val);

		return {
			(r1_val * r1dx_val + r2_val * r2dx_val) / n,
			(r1_val * r1dy_val + r2_val * r2dy_val) / n
		};
	}
);

void usage()
{
	std::cout << "usage: findroot <start x> <start y> <precision>\n";
}

std::string ToString(double value, int precision)
{
	std::stringstream str;
	str << std::setprecision(precision) << std::scientific
		<< value;
	return str.str();
}

std::string ToString(std::size_t value)
{
	std::stringstream str;
	str << value;
	return str.str();
}

Table totalTable;

template<class MethodT>
void RunMethod(std::ostream& out, Settings& settings, bool fastIterate = false)
{
	settings.Reset();

	Table table;
	table.SetTitle(MethodT::GetTitle());
	table.SetColumnNames(MethodT::GetColumnNames());

	auto method = std::make_unique<MethodT>(settings);
	method->Init(settings.start);
	std::shared_ptr<IState> prevState = nullptr;

	do
	{
		auto state = method->GetState();
		table.AddRow(state->ToString(prevState));
		prevState = state;

		if (fastIterate)
		{
			method->FastIterate();
		}
		else
		{
			method->Iterate();
		}
	}
	while (!method->IsEnded());

	table.Print(out);


	Table resTable;
	resTable.SetTitle("Results");
	resTable.SetColumnNames({ "Method", "x", "y",
			"calls to f(x, y)", "calls to grad f(x,y)" });

	int precision = settings.precision;
	auto res = method->GetResult();
	resTable.AddRow({ MethodT::GetTitle(),
			ToString(res.x, precision),
			ToString(res.y, precision),
			ToString(settings.f.GetCalls()),
			ToString(settings.grad.GetCalls()) });
	resTable.Print(out);

	totalTable.AddRow({ MethodT::GetTitle(),
			ToString(res.x, precision),
			ToString(res.y, precision),
			ToString(settings.f.GetCalls()),
			ToString(settings.grad.GetCalls()) });
}

int main(int argc, char* argv[])
{
	if (argc != 4)
	{
		usage();
		return EXIT_FAILURE;
	}

	double x, y;
	int precision = 6;

	sscanf(argv[1], "%lf", &x);
	sscanf(argv[2], "%lf", &y);
	sscanf(argv[3], "%d", &precision);

	double eps = std::pow(10, -(precision+1));

	Vector start{x, y};

	Settings settings{ precision+1, eps, start, f, grad };

	totalTable.SetTitle("Results");
	totalTable.SetColumnNames({ "Method", "x", "y",
			"calls to f(x, y)", "calls to grad f(x,y)" });

	std::ofstream out;
	out.open("results/coord_descent.txt");
	RunMethod<CoordDescentMethod>(out, settings);
	out.close();

	out.open("results/step_splitting.txt");
	RunMethod<StepSplittingMethod>(out, settings);
	out.close();

	out.open("results/const_step.txt");
	RunMethod<ConstStepMethod>(out, settings);
	out.close();

	out.open("results/diverge_series.txt");
	RunMethod<DivergeSeriesMethod>(out, settings);
	out.close();

	out.open("results/total.txt");
	totalTable.Print(out);
	out.close();

	totalTable.Print(std::cout);

	return EXIT_SUCCESS;
}

