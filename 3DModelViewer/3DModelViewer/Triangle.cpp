//Created for Graphics I and II
//Author: Minsi Chen

#include "Triangle.h"

Triangle::Triangle()
{
	
}

Triangle::Triangle(int v0, int v1, int v2)
{
	SetVertexIndices(v0, v1, v2);
}


Triangle::~Triangle()
{
}

void Triangle::SetVertexIndices(int v0, int v1, int v2)
{
	m_vertices[0] = v0;
	m_vertices[1] = v1;
	m_vertices[2] = v2;
}