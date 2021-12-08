#pragma once

#include <ostream>
#include <cmath>

struct Vector
{
	double x;
	double y;

	double Length() const
	{
		return Norm();
	}

	double Norm() const
	{
		return std::hypot(x, y);
	}

	static double Dot(const Vector& lhs, const Vector& rhs)
	{
		return lhs.x * rhs.x + lhs.y * rhs.y;
	}
};

std::ostream& operator<<(std::ostream& out, const Vector& p)
{
	return out << '(' << p.x << ',' << p.y << ')';
}

Vector operator*(double a, const Vector& p)
{
	return { a * p.x, a * p.y };
}
Vector operator+(const Vector& p1, const Vector& p2)
{
	return { p1.x + p2.x, p1.y + p2.y };
}
Vector operator-(const Vector& p1, const Vector& p2)
{
	return { p1.x - p2.x, p1.y - p2.y };
}
Vector operator/(const Vector& p, double a)
{
	return { p.x / a, p.y / a };
}

