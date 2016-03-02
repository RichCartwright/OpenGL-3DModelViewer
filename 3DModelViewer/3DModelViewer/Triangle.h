//Created for Graphics I and II
//Author: Minsi Chen

#pragma once
#include "Vector4D.h"

class Triangle
{
private:
	Vector4D	m_normal;		//normal to the triangle
	int		m_vertices[3];		//vertex indices
	
public:
	Triangle();
	Triangle(int v0, int v1, int v2);
	~Triangle();

	void SetVertexIndices(int v0, int v1, int v2);
	
	inline const int* GetVertexIndices()
	{
		return m_vertices;
	}

	inline void SetNormal(const Vector4D& normal)
	{
		m_normal = normal;
	}

	inline Vector4D GetNormal() const
	{
		return m_normal;
	}

};

