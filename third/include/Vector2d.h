#pragma once

#include <ostream>
#include <cmath>

struct Vector2d
{
	double x;
	double y;

	double Length() const
	{
		return std::hypot(x, y);
	}
};

std::ostream& operator<<(std::ostream& out, const Vector2d& v)
{
	return out << '(' << v.x << ", " << v.y << ')';
}

Vector2d operator+(const Vector2d& lhs, const Vector2d& rhs)
{
	return { lhs.x + rhs.x, lhs.y + rhs.y };
}

Vector2d operator-(const Vector2d& lhs, const Vector2d& rhs)
{
	return { lhs.x - rhs.x, lhs.y - rhs.y };
}

Vector2d operator*(double a, const Vector2d& v)
{
	return { a * v.x, a * v.y };
}
Vector2d operator*(const Vector2d& v, double a)
{
	return a * v;
}
Vector2d operator/(const Vector2d& v, double a)
{
	return { v.x / a, v.y / a };
}

bool operator==(const Vector2d& lhs, const Vector2d& rhs)
{
	return lhs.x == rhs.x && lhs.y == rhs.y;
}
bool operator!=(const Vector2d& lhs, const Vector2d& rhs)
{
	return !(lhs == rhs);
}

double Dot(const Vector2d& lhs, const Vector2d& rhs)
{
	return lhs.x * rhs.x + lhs.y * rhs.y;
}

