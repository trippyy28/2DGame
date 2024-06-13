#include "Vec2.h"

// Default constructor
Vec2::Vec2() : x(0), y(0) {}

// Parameterized constructor
Vec2::Vec2(float xin, float yin) : x(xin), y(yin) {}

// Equality operator
bool Vec2::operator==(const Vec2 &rhs) const
{
    return x == rhs.x && y == rhs.y;
}

// Inequality operator
bool Vec2::operator!=(const Vec2 &rhs) const
{
    return !(*this == rhs);
}

// Addition operator
Vec2 Vec2::operator+(const Vec2 &rhs) const
{
    return Vec2(x + rhs.x, y + rhs.y);
}

// Subtraction operator
Vec2 Vec2::operator-(const Vec2 &rhs) const
{
    return Vec2(x - rhs.x, y - rhs.y);
}

// Division operator
Vec2 Vec2::operator/(const Vec2 &rhs) const
{
    return Vec2(x / rhs.x, y / rhs.y);
}

// Multiplication operator
Vec2 Vec2::operator*(const Vec2 &rhs) const
{
    return Vec2(x * rhs.x, y * rhs.y);
}

// Scalar multiplication operator
Vec2 Vec2::operator*(float scalar) const
{
    return Vec2(x * scalar, y * scalar);
}

// Addition assignment operator
void Vec2::operator+=(const Vec2 &rhs)
{
    x += rhs.x;
    y += rhs.y;
}

// Subtraction assignment operator
void Vec2::operator-=(const Vec2 &rhs)
{
    x -= rhs.x;
    y -= rhs.y;
}

// Division assignment operator
void Vec2::operator/=(const Vec2 &rhs)
{
    x /= rhs.x;
    y /= rhs.y;
}

// Multiplication assignment operator
void Vec2::operator*=(const Vec2 &rhs)
{
    x *= rhs.x;
    y *= rhs.y;
}

// Scalar multiplication assignment operator
void Vec2::operator*=(float scalar)
{
    x *= scalar;
    y *= scalar;
}
