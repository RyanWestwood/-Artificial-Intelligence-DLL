#pragma once
#include <math.h>
#include <iostream>

struct Vector2 {
	float x, y;

	Vector2() { x = 0.f, y = 0.f; }
	Vector2(float x, float y) : x(x), y(y) {}
	Vector2(int x, int y) : x(float(x)), y(float(y)) {}
	
	Vector2 Normalize() {
		float magnitude = std::sqrtf(x * x + y * y);
		return Vector2(x / magnitude, y / magnitude);
	}

	static float Distance(const Vector2& lhs, const Vector2& rhs){
		float x = lhs.x - rhs.x;
		float y = lhs.y - rhs.y;
		return std::sqrtf(x * x + y * y);
	}

	friend Vector2 operator+(const Vector2& lhs, const Vector2& rhs) { return Vector2(lhs.x + rhs.x, lhs.y + rhs.y); }
	friend Vector2 operator-(const Vector2& lhs, const Vector2& rhs) { return Vector2(lhs.x - rhs.x, lhs.y - rhs.y); }
	friend Vector2 operator*(const Vector2& lhs, const Vector2& rhs) { return Vector2(lhs.x * rhs.x, lhs.y * rhs.y); }
	friend Vector2 operator*(const Vector2& lhs, const float value) { return Vector2(lhs.x * value, lhs.y * value); }
	friend Vector2 operator/(const Vector2& lhs, const Vector2& rhs) { return Vector2(lhs.x / rhs.x, lhs.y / rhs.y); }
	friend bool operator==(const Vector2& lhs, const Vector2& rhs) { return lhs.x == rhs.x && lhs.y == rhs.y; }
	friend bool operator!=(const Vector2& lhs, const Vector2& rhs) { return !operator==(lhs, rhs); }
	friend std::ostream& operator<<(std::ostream& out, const Vector2& value) { return out << "(" << value.x << ", " << value.y << ")\n"; }
};