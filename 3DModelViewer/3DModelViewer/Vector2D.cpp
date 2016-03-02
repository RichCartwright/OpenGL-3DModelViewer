#include "Vector2D.h"

// Constructors

Vector2D::Vector2D(void)
{
	Init(0.0f, 0.0f);
}

Vector2D::Vector2D(float x, float y)
{
	Init(x, y);
}

Vector2D::Vector2D(const Vector2D& v)
{
	Copy(v);
}

Vector2D::~Vector2D(void)
{
}

// Accessors and mutators

float Vector2D::GetX(void) const
{
	return _x;
}

void Vector2D::SetX(float x)
{
	_x = x;
}

float Vector2D::GetY(void) const
{
	return _y;
}

void Vector2D::SetY(float y)
{
	_y = y;
}

// Operator overloads

Vector2D& Vector2D::operator= (const Vector2D &rhs)
{
	if (this != &rhs)
	{
		// Only copy if we are not assigning to ourselves. 
		// (remember that a = b is the same as a.operator=(b))
		Copy(rhs);
	}
	return *this;
}

const Vector2D Vector2D::operator+(const Vector2D &other) const
{
	Vector2D result;
	result.SetX(_x + other.GetX());
	result.SetY(_y + other.GetY());
	return result;
}

const Vector2D Vector2D::operator-(const Vector2D &other) const
{
	Vector2D result;
	result.SetX(_x - other.GetX());
	result.SetY(_y - other.GetY());
	return result;
}


// Private methods

void Vector2D::Init(float x, float y)
{
	_x = x;
	_y = y;
}

void Vector2D::Copy(const Vector2D& v)
{
	_x = v.GetX();
	_y = v.GetY();
}
