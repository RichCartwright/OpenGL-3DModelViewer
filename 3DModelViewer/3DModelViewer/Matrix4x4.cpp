#include <memory.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include "Vector4D.h"
#include "Matrix4x4.h"

Matrix4x4::Matrix4x4()
{
	SetIdentity();
}

Matrix4x4::Matrix4x4(const Matrix4x4& rhs)
{
	size_t matrix_size = sizeof(m_element);

	memcpy_s((&m_element[0][0]), matrix_size, rhs.ToPtr(), matrix_size);
}

Matrix4x4::~Matrix4x4()
{

}

const float* Matrix4x4::ToPtr() const
{
	return &(m_element[0][0]);
}

void Matrix4x4::SetZero()
{
	memset(&m_element, 0, sizeof(m_element));
}

void Matrix4x4::SetIdentity()
{
	SetZero();
	m_element[0][0] = m_element[1][1] = m_element[2][2] = m_element[3][3] = 1.0f;
}

Matrix4x4 Matrix4x4::operator* (const Matrix4x4& rhs) const
{
	Matrix4x4 result;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			result.m_element[i][j] = 0;

			for (int k = 0; k < 4; k++)
			{
				result.m_element[i][j] += m_element[i][k] * rhs.m_element[k][j];
			}
		}
	}
	
	return result;
}

Vector4D Matrix4x4::operator* (const Vector4D& rhs) const
{
	Vector4D result;

	result = rhs;
	
	result[0] = (m_element[0][0] * rhs[0]) + (m_element[0][1] * rhs[1]) + (m_element[0][2] * rhs[2]) + (m_element[0][3] * rhs[3]);
	result[1] = (m_element[1][0] * rhs[0]) + (m_element[1][1] * rhs[1]) + (m_element[1][2] * rhs[2]) + (m_element[1][3] * rhs[3]);
	result[2] = (m_element[2][0] * rhs[0]) + (m_element[2][1] * rhs[1]) + (m_element[2][2] * rhs[2]) + (m_element[2][3] * rhs[3]);
	result[3] = (m_element[3][0] * rhs[0]) + (m_element[3][1] * rhs[1]) + (m_element[3][2] * rhs[2]) + (m_element[3][3] * rhs[3]);
	
	return result;
}

void Matrix4x4::SetRotationXAxis(float degrees)
{
	m_element[0][0] = 1,	 m_element[0][1] = 0,					 m_element[0][2] = 0,								m_element[0][3] = 0;
	m_element[1][0] = 0,	 m_element[1][1] = cos(degrees / (180 * M_PI)),		 m_element[1][2] = sin(degrees / (180 * M_PI)),		m_element[1][3] = 0;
	m_element[2][0] = 0,	 m_element[2][1] = -sin(degrees / (180 * M_PI)),	 m_element[2][2] = cos(degrees / (180 * M_PI)),		m_element[2][3] = 0;
	m_element[3][0] = 0,     m_element[3][1] = 0,					 m_element[3][2] = 0,								m_element[3][3] = 1;
}

void Matrix4x4::SetRotationYAxis(float degrees)
{
	m_element[0][0] = cos(degrees / (180 * M_PI)),			 m_element[0][1] = 0,  m_element[0][2] = -sin(degrees / (180 * M_PI)),		m_element[0][3] = 0;
	m_element[1][0] = 0,						 m_element[1][1] = 1,  m_element[1][2] = 0,									m_element[1][3] = 0;
	m_element[2][0] = sin(degrees / (180 * M_PI)),			 m_element[2][1] = 0,  m_element[2][2] = cos(degrees / (180 * M_PI)),		m_element[2][3] = 0;
	m_element[3][0] = 0,						 m_element[3][1] = 0,  m_element[3][2] = 0,									m_element[3][3] = 1;
}

void Matrix4x4::SetRotationZAxis(float degrees)
{
	m_element[0][0] = cos(degrees / (180 * M_PI)),			m_element[0][1] = -sin(degrees / (180 * M_PI)),			m_element[0][2] = 0,	m_element[0][3] = 0;
	m_element[1][0] = sin(degrees / (180 * M_PI)),			m_element[1][1] = cos(degrees / (180 * M_PI)),			m_element[1][2] = 0,	m_element[1][3] = 0;
	m_element[2][0] = 0,						m_element[2][1] = 0,									m_element[2][2] = 1,	m_element[2][3] = 0;
	m_element[3][0] = 0,						m_element[3][1] = 0,									m_element[3][2] = 0,	m_element[3][3] = 1;
}

void Matrix4x4::SetTranslate(const Vector4D& tvec)
{
	m_element[0][2] = tvec[0];
	m_element[1][2] = tvec[1];
	m_element[2][2] = tvec[2];	
}

void Matrix4x4::SetScale(float sx, float sy, float sz)
{
	m_element[0][0] = sx,		m_element[0][1] = 0,	m_element[0][2] = 0,	m_element[0][3] = 0;
	m_element[1][0] = 0,		m_element[1][1] = sy,	m_element[1][2] = 0,	m_element[1][3] = 0;
	m_element[2][0] = 0,		m_element[2][1] = 0,	m_element[2][2] = sz,	m_element[2][3] = 0;
	m_element[3][0] = 0,		m_element[3][1] = 0,	m_element[3][2] = 0,	m_element[3][3] = 1;
}

void Matrix4x4::SetViewMatrix(const Vector4D& camera_position, const Vector4D& view_vector, const Vector4D& up_vector)
{
	//TODO: Slightly more advanced
	//Set this matrix as a view matrix based on the given camera_position, view_vector and up_vector
}
