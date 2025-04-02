 #include "Vector2D.h"
#include <cmath>
using namespace std;

Vector2D::Vector2D()
{
	x = 0.0f;
	y = 0.0f;

 }
Vector2D::Vector2D(float x, float y)
{
	this->x = x;
	this->y = y;

}
Vector2D& Vector2D::Add(const Vector2D& vec)
{
	this->x += vec.x;
	this->y += vec.y;
	return *this;

}
Vector2D& Vector2D::Subtract(const Vector2D& vec)
{
	this->x -= vec.x;
	this->y -= vec.y;
	return *this;

}
Vector2D& Vector2D::Multiply(const Vector2D& vec)
{
	this->x *= vec.x;
	this->y *= vec.y;
	return *this;

}
Vector2D& Vector2D::Divide(const Vector2D& vec)
{
	this->x /= vec.x;
	this->y /= vec.y;
	return *this;

}

float Vector2D::Dist(const Vector2D& vec) const
{
	float dx = x - vec.x; // Calculate difference in x-coordinates
	float dy = y - vec.y; // Calculate difference in y-coordinates
	return sqrt(dx * dx + dy * dy); // Calculate distance using Pythagorean theorem
}


Vector2D& operator+(Vector2D& v1, const Vector2D& v2)
{
	return v1.Add(v2);
}
Vector2D& operator-(Vector2D& v1, const Vector2D& v2)
{
	return v1.Subtract(v2);
}
Vector2D& operator*(Vector2D& v1, const Vector2D& v2)
{
	return v1.Multiply(v2);
}
Vector2D& operator/(Vector2D& v1, const Vector2D& v2)
{
	return v1.Divide(v2);
}



Vector2D& Vector2D::operator+=(const Vector2D& vec)
{
	return this->Add(vec);
}
Vector2D& Vector2D::operator-=(const Vector2D& vec)
{
	return this->Subtract(vec);
}
Vector2D& Vector2D::operator*=(const Vector2D& vec)
{
	return this->Multiply(vec);
}
Vector2D& Vector2D::operator/=(const Vector2D& vec)
{
	return this->Divide(vec);
}

Vector2D& Vector2D::operator*(const int& i)
{
	this->x *= i;
	this->y *= i;
	return *this;
}

Vector2D& Vector2D::Zero()
{
	this->x = 0;
	this->y = 0;
	return *this;
}

ostream& operator<<(ostream& stream, const Vector2D& vec)
{
	stream << "(" << vec.x << "," << vec.y << ")";
	return stream;
}

float Vector2D::Length() const
{
	return sqrt(x * x + y * y); // Calculate the length (magnitude) using Pythagorean theorem
}
Vector2D& Vector2D::Normalize()
{
	float length = Length(); // Calculate the length of the vector
	if (length > 0) // Avoid division by zero if the vector is already zero length
	{
		float invLength = 1.0f / length; // Calculate the inverse length for efficiency
		x *= invLength;
		y *= invLength;
	}
	return *this; // Return the normalized vector (for chaining if needed)
}

Vector2D Vector2D::Rotate(double angleRadians) const
{
	double cosTheta = cos(angleRadians); // Calculate cosine of the angle
	double sinTheta = sin(angleRadians); // Calculate sine of the angle

	// Rotation formula for 2D vectors:
	// x' = x*cos(theta) - y*sin(theta)
	// y' = x*sin(theta) + y*cos(theta)
	return Vector2D(
		x * cosTheta - y * sinTheta, // Calculate rotated x-component
		x * sinTheta + y * cosTheta  // Calculate rotated y-component
	);
}