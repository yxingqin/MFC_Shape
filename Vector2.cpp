#include "pch.h"
#include "Vector2.h"
float Vector2::Cross(Vector2& v)
{
	return(x * v.y - y * v.x);
}
Vector2 Vector2::operator -()
{
	this->x = -this->x;
	this->y = -this->y;
	return *this;
}