#include "Function.h"

#include <d3dx9.h>

#include <stdio.h>
#include <math.h>

float Fn::_sinTable[3600];
float Fn::_cosTable[3600];

float Fn::LengthDirX(float len, float degree)
{
	return Cos(degree)*len;
}

float Fn::LengthDirY(float len, float degree)
{
	return Sin(degree)*len;
}

float Fn::PointDirection(float x1, float y1, float x2, float y2)
{
	return atan2(y2 - y1, x2 - x1) * 180 / PI;
}

float Fn::PointDistance(float x1, float y1, float x2, float y2)
{
	return sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
}

float Fn::Sqrt(float value)
{
	long i;
	float x2, y;
	const float threehalfs = 1.5F;

	x2 = value * 0.5F;
	y = value;
	i = *(long *)&y;                       // evil floating point bit level hacking
	i = 0x5f3759df - (i >> 1);               // what the fuck?
	y = *(float *)&i;
	y = y * (threehalfs - (x2 * y * y));   // 1st iteration
	//      y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed

	return y;
}

void Fn::LookupTableCreator()
{
	for (int i = 0; i < 3600; i++) {
		float x = D3DXToRadian((float)i / 10.0f);
		_sinTable[i] = sin(x);
		_cosTable[i] = cos(x);
	}
}

inline float Fn::Sin(float degree)
{
	if (degree == 0) return 0;

	int idx = degree * 10;
	if (degree >= 0)
		idx %= 3601;
	else
		idx %= 3600;

	if (degree >= 0)
		idx = 3600 - idx;

	int sign = 1;
	sign = (idx >= 0) ? 1 : -1;

	return -_sinTable[sign*(int)idx];
}

inline float Fn::Cos(float degree)
{
	if (degree == 0) return 1;

	int idx = degree * 10;
	if (degree >= 0)
		idx %= 3601;
	else
		idx %= 3600;

	if (degree >= 0)
		idx = 3600 - idx;

	int sign = 1;
	sign = (idx >= 0) ? 1 : -1;

	return _cosTable[sign*(int)idx];
}

bool Fn::CollisionWithMouse(const POINT &mouse, float x, float y, int width, int height)
{
	if (mouse.x >= x - width / 2 && mouse.x <= x + width / 2 && mouse.y >= y - height / 2 && mouse.y <= y + height / 2)
		return true;
	return false;
}