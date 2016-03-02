#include <math.h>

#include "Vector4D.h"

Vector4D::Vector4D(const Vector4D& rhs)
{
	m_element[0] = rhs[0];
	m_element[1] = rhs[1];
	m_element[2] = rhs[2];
	m_element[3] = rhs[3];
}

float Vector4D::operator [] (const int i) const
{
	return m_element[i];
}

float& Vector4D::operator [] (const int i)
{
	return m_element[i];
}

Vector4D Vector4D::operator + (const Vector4D& rhs) const
{
	return Vector4D(
		(*this)[0] + rhs[0],
		(*this)[1] + rhs[1],
		(*this)[2] + rhs[2],
		(*this)[3] + rhs[3]);
}

Vector4D Vector4D::operator - (const Vector4D& rhs) const
{
	return Vector4D(
		(*this)[0] - rhs[0],
		(*this)[1] - rhs[1],
		(*this)[2] - rhs[2],
		(*this)[3] - rhs[3]);
}

Vector4D& Vector4D::operator = (const Vector4D& rhs)
{
	m_element[0] = rhs[0];
	m_element[1] = rhs[1];
	m_element[2] = rhs[2];
	m_element[3] = rhs[3];
	return *this;
}

Vector4D Vector4D::operator * (const Vector4D& rhs) const
{
	return Vector4D(
		m_element[0] * rhs[0],
		m_element[1] * rhs[1],
		m_element[2] * rhs[2],
		m_element[3] * rhs[3]);
}

Vector4D Vector4D::operator * (float scale) const
{
	return Vector4D(
		m_element[0] * scale,
		m_element[1] * scale,
		m_element[2] * scale,
		m_element[3] * scale
		);
}

float Vector4D::Length() const
{
	return sqrtf(m_element[0] * m_element[0]
		+ m_element[1] * m_element[1]
		+ m_element[2] * m_element[2]
		+ m_element[3] * m_element[3]);
}

float Vector4D::LengthSqr() const
{
	return m_element[0] * m_element[0]
		+ m_element[1] * m_element[1]
		+ m_element[2] * m_element[2]
		+ m_element[3] * m_element[3];
}

float Vector4D::DotProduct(const Vector4D& rhs) const
{
	return m_element[0] * rhs[0] + m_element[1] * rhs[1] + m_element[2] * rhs[2] + m_element[3] * rhs[3];
}

void Vector4D::Normalise()
{
	float length = this->Length();

	if (length > 1.0e-8f)
	{
		float invLen = 1.0f / length;

		m_element[0] *= invLen;
		m_element[1] *= invLen;
		m_element[2] *= invLen;
		m_element[3] *= invLen;
	}
}

Vector4D Vector4D::CrossProduct(const Vector4D& rhs) const
{
	return Vector4D(
		(m_element[1] * rhs[2] - m_element[2] * rhs[1]),
		(m_element[2] * rhs[0] - m_element[0] * rhs[2]),
		(m_element[0] * rhs[1] - m_element[1] * rhs[0]),
		1.0f
		);
}

void Vector4D::SetZero()
{
	m_element[0] = m_element[1] = m_element[2] = m_element[3] = 0.0f;
}
