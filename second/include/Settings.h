#pragma once

#include <Function.h>
#include <Vector.h>

struct Settings
{
	int precision;
	double eps;

	Vector start;

	Function<double, Vector>& f;
	Function<Vector, Vector>& grad;

	void Reset()
	{
		f.Reset();
		grad.Reset();
	}
};

