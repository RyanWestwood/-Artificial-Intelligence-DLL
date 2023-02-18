#pragma once
#include <math.h>
#include <iostream>

struct Vector2 {
	float x, y;

	Vector2() { x = 0.f, y = 0.f; }
	Vector2(float x, float y) : x(x), y(y) {}
	Vector2(int x, int y) : x(float(x)), y(float(y)) {}	

	friend Vector2 operator+(const Vector2& lhs, const Vector2& rhs) { return Vector2(lhs.x + rhs.x, lhs.y + rhs.y); }
	friend Vector2 operator-(const Vector2& lhs, const Vector2& rhs) { return Vector2(lhs.x - rhs.x, lhs.y - rhs.y); }
	friend Vector2 operator*(const Vector2& lhs, const Vector2& rhs) { return Vector2(lhs.x * rhs.x, lhs.y * rhs.y); }
	friend Vector2 operator*(const Vector2& lhs, const float value) { return Vector2(lhs.x * value, lhs.y * value); }
	friend Vector2 operator/(const Vector2& lhs, const Vector2& rhs) { return Vector2(lhs.x / rhs.x, lhs.y / rhs.y); }
	friend Vector2 operator/(const Vector2& lhs, float val) { return Vector2(lhs.x / val, lhs.y / val); }
	friend bool operator==(const Vector2& lhs, const Vector2& rhs) { return lhs.x == rhs.x && lhs.y == rhs.y; }
	friend bool operator!=(const Vector2& lhs, const Vector2& rhs) { return !operator==(lhs, rhs); }
	friend std::ostream& operator<<(std::ostream& out, const Vector2& value) { return out << "(" << value.x << ", " << value.y << ")\n"; }

	static float Magnitude(Vector2 vector)
    {
        return std::sqrtf(vector.x * vector.x + vector.y * vector.y);
    }

	float Magnitude()
	{
		return Magnitude(*this);
	}

	static Vector2 Normalize(Vector2 vector)
    {
        float magnitude = vector.Magnitude(vector);
        return magnitude > 0 ? Vector2{vector / magnitude} : Vector2{0.f,0.f};
    }

	Vector2 Normalize()
	{
		return Normalize(*this);
	}

	static float Distance(Vector2 vec1, Vector2 vec2)
	{
		float x = vec2.x - vec1.x;
		float y = vec2.y - vec1.y;
		return std::sqrtf(x * x + y * y);
	}

	float Distance(Vector2 vec)
	{
		return Distance(*this, vec);
	}

	static Vector2 MoveTowards(Vector2 current, Vector2 goal, float move_distance)
	{	
		Vector2 vec_to_target = goal - current;
		float distance_to_target = vec_to_target.Magnitude();

		if(distance_to_target < move_distance || distance_to_target == 0.f) return goal;

		return current + vec_to_target / distance_to_target * move_distance;
	}

	Vector2 MoveTowards(Vector2 goal, float move_distance)
	{
		return MoveTowards(*this, goal, move_distance);
	}
};