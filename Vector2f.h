#pragma once
class Vector2f
{
public:

	Vector2f();
	Vector2f(float x, float y);
	~Vector2f();

	float X = 0;
	float Y = 0;

	static const Vector2f Top;
};
