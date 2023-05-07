#pragma once
#include <iostream>
#include <cmath>

namespace mEngine 
{
	namespace Math
	{
		class Vec2D
		{
		public:
			float x, y;

			Vec2D(float x = 0, float y = 0) : x(x), y(y) {}

			void Log(const std::string& msg = "") const {
				std::cout << msg << ' ';
				std::cout << "(X,Y)" << '(' << x << "," << y << ')' << '\n';
			}

			// arithmetic operators
			inline Vec2D operator+(const Vec2D& other) const { return {x + other.x, y + other.y}; }
			inline Vec2D operator-(const Vec2D& other) const { return {x - other.x, y - other.y}; }
			inline Vec2D operator*(float scalar) const { return {x * scalar, y * scalar}; }
			inline Vec2D operator/(float scalar) const { return {x / scalar, y / scalar}; }

			 // assignment operators
			inline Vec2D& operator+=(const Vec2D& other) { x += other.x; y += other.y; return *this; }
			inline Vec2D& operator-=(const Vec2D& other) { x -= other.x; y -= other.y; return *this; }
			inline Vec2D& operator/=(float scalar) { x /= scalar; y /= scalar; return *this; }
			inline Vec2D& operator*=(float scalar) { x *= scalar; y *= scalar; return *this; }

			// comparison operators
			inline bool operator==(const Vec2D& other) const { return x == other.x && y == other.y; }
			inline bool operator!=(const Vec2D& other) const { return !(*this == other); }

			// vector operations
			Vec2D distanceXY(const Vec2D& other) const 
			{
				return { std::abs(x - other.x), std::abs(y - other.y) };
			}
			inline float length() const { return sqrt(x * x + y * y); }
			inline float distance(const Vec2D& other) const { return (*this - other).length(); }
			inline Vec2D normalize() const { float len = length(); return len == 0 ? Vec2D(0, 0) : *this / len; }
			inline float dot(const Vec2D& other) const { return x * other.x + y * other.y; }
			inline float angle(const Vec2D& other) const { return atan2(other.y - y, other.x - x); }
			Vec2D project(const Vec2D& other) const { return other * dot(other) / other.dot(other); }
		};
	}
}