#pragma once
class Vector2
{
public:
	float x, y;
	Vector2(float fx, float fy)
		:x(fx), y(fy)
	{
	}
	float Cross(Vector2&);
	Vector2 operator -();
};

