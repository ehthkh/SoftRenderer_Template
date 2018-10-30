#include "stdafx.h"
#include "Vector2.h"

float Vector2::Dist(const Vector2 & v1, const Vector2 & v2)
{
	/*
	float xLength = v2.x - v1.x;
	float yLength = v2.y - v1.y;
	return sqrtf(xLength * xLength + yLength * yLength);
	*/

	return sqrtf(Vector2::DistSquared(v1, v2));
}

float Vector2::DistSquared(const Vector2 & v1, const Vector2 & v2)
{
	float xLength = v2.x - v1.x;
	float yLength = v2.y - v1.y;
	return xLength * xLength + yLength * yLength;

	//return sqrtf(Vector2::DistSquared(v1, v2));
}

Vector2 Vector2::operator*(const Matrix2 & mat) const
{
	Vector2 result;
	result.x = x * mat._11 + y * mat._12;
	result.y = x * mat._21 + y * mat._22;

	return result;
}

bool Vector2::Equals(const Vector2 & v, float tolerance) const
{
	return (fabs(x - v.x) < tolerance && fabs(y - v.y) < tolerance);
}
