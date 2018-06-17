#ifndef _FUNCTION_H_
#define _FUNCTION_H_

#include <cmath>
#include <Windows.h>

#define PI 3.1415926535f

class Fn
{
private:
	static float _sinTable[3600];
	static float _cosTable[3600];

	/// 삼각함수 관련 함수 모음
public:
	static float LengthDirX(float len, float degree);
	static float LengthDirY(float len, float degree);

	static float PointDirection(float x1, float y1, float x2, float y2);
	static float PointDistance(float x1, float y1, float x2, float y2);

	/// 계산 함수 모음
public:
	static float Sqrt(float value);
	static float Sin(float value);
	static float Cos(float value);

	static void LookupTableCreator();

	/// 충돌처리 함수 모음
public:
	static bool CollisionWithMouse(const POINT &mouse, float x, float y, int width, int height);
};

#endif