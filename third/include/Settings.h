#pragma once

#include <Function.h>
#include <Vector2d.h>

struct Settings
{
	int precision;
	double eps;

	Function<double, Vector2d> f;
	Function<Vector2d, Vector2d> grad;

	Function<double, Vector2d> g;
	Function<Vector2d, Vector2d> ggrad;

	/* allowable set's center */
	Vector2d c;
	double R;

	void Reset()
	{
		f.ResetCalls();
		grad.ResetCalls();
	}
};

