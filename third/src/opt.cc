#include <iostream>

#include <Methods/CoordDescentMethod.h>
#include <Methods/ExternalPenaltyMethod.h>
#include <Methods/InternalPenaltyMethod.h>

#include <Function.h>
#include <Settings.h>

#include <TablePrinter.h>
#include <StateBuilder.h>

#include <iostream>
#include <fstream>

#include <cstdlib>
#include <cmath>

/*
 * f = 8
 * u = 9
 * o = 10
 * */
const double c_alpha = 8;
const double c_beta = 9;
const double c_gamma = 10;

double r1(Vector2d p)
{
	double x = p.x;
	double y = p.y;

	return c_beta * x*x - c_beta * y*y - 2.0 * c_gamma * x*y
		+ c_beta * x - c_alpha * y + c_gamma;
}
double r1dx(Vector2d p)
{
	double x = p.x;
	double y = p.y;

	return 2.0 * c_beta * x - 2.0 * c_gamma * y + c_beta;
}
double r1dy(Vector2d p)
{
	double x = p.x;
	double y = p.y;

	return -2.0 * c_beta * y - 2.0 * c_gamma * x - c_alpha;
}

double r2(Vector2d p)
{
	double x = p.x;
	double y = p.y;

	return 2.0 * c_beta * x*y + c_gamma * x*x - c_gamma * y*y
		+ c_alpha * x + c_beta * y + c_alpha;
}
double r2dx(Vector2d p)
{
	double x = p.x;
	double y = p.y;

	return 2.0 * c_beta * y + 2.0 * c_gamma * x + c_alpha;
}
double r2dy(Vector2d p)
{
	double x = p.x;
	double y = p.y;

	return 2.0 * c_beta * x - 2.0 * c_gamma * y + c_beta;
}

Function<double, Vector2d> f(
	[](Vector2d p) -> double
	{
		auto r1val = r1(p);
		auto r2val = r2(p);

		return r1val * r1val + r2val * r2val;
	}
);

Function<Vector2d, Vector2d> grad(
	[](Vector2d p) -> Vector2d
	{
		double r1_val = r1(p);
		double r2_val = r2(p);

		double r1dx_val = r1dx(p);
		double r1dy_val = r1dy(p);

		double r2dx_val = r2dx(p);
		double r2dy_val = r2dy(p);

		return {
			2.0 * (r1_val * r1dx_val + r2_val * r2dx_val),
			2.0 * (r1_val * r1dy_val + r2_val * r2dy_val)
		};
	}
);


const Vector2d c{1.0, 2.0};
const double R = 1;

Function<double, Vector2d> g(
	[](Vector2d p) -> double
	{
		auto x = p.x - c.x;
		auto y = p.y - c.y;

		auto val = x * x + y * y - R * R;
		return val;
	}
);

Function<Vector2d, Vector2d> ggrad(
	[](Vector2d p) -> Vector2d
	{
		auto x = p.x - c.x;
		auto y = p.y - c.y;

		auto dx = 2.0 * x;
		auto dy = 2.0 * y;

		return {
			dx,
			dy
		};
	}
);

TablePrinter totalPrinter;
template <typename MethodType>
void RunMethod(std::ostream& out, Settings& settings, Vector2d start)
{
	settings.Reset();


	TablePrinter printer;

	auto method = std::make_unique<MethodType>(settings);
	auto methodName = method->GetName();
	std::cout << methodName << ": running...\n";

	printer.SetTitle(methodName);
	printer.SetColumnNames(method->GetColumnNames());

	method->Init(start);

	do
	{
		auto state = method->GetState();
		printer.AddRow(state);

		method->Iterate();
	}
	while (!method->IsEnded());

	auto state = method->GetState();
	printer.AddRow(state);
	printer.Print(out);

	TablePrinter resultPrinter;
	resultPrinter.SetTitle("Results");
	resultPrinter.SetColumnNames({ "Method", "x", "y",
			"calls to f(x, y)", "calls to grad f(x,y)" });

	int precision = settings.precision;
	double eps = settings.eps;
	StateBuilder builder{precision, eps};

	auto result = method->GetResult();
	builder.Add(methodName);
	builder.Add(result);
	builder.Add(settings.f.GetCalls());
	builder.Add(settings.grad.GetCalls());

	state = builder.GetState();
	resultPrinter.AddRow(state);
	resultPrinter.Print(out);

	totalPrinter.AddRow(state);

	std::cout << methodName << ": done\n";
}

int main()
{
	int precision = 4;
	double eps = std::pow(10, -(precision + 1));

	Vector2d start{c.x, c.y};

	Settings settings{precision, eps, f, grad, g, ggrad, c, R};
	totalPrinter.SetTitle("Results");
	totalPrinter.SetColumnNames({ "Method", "x", "y",
			"calls to f(x, y)", "calls to grad f(x,y)" });

	std::ofstream fout;

	fout.open("results/external_penalty.txt");
	RunMethod<ExternalPenaltyMethod>(fout, settings, start);
	fout.close();

	fout.open("results/internal_penalty.txt");
	RunMethod<InternalPenaltyMethod>(fout, settings, start);
	fout.close();

	fout.open("results/total.txt");
	totalPrinter.Print(fout);
	fout.close();

	totalPrinter.Print(std::cout);

	return EXIT_SUCCESS;
}

