//Created for Graphics I and II
//Author: Minsi Chen
#pragma once

#include "Renderable.h"
#include "Listener.h"
#include "Matrix4x4.h"
#include "Vector4D.h"

//A simple vertex data type
struct SimpleVertex
{
	Vector4D position;		//position
	Vector4D colour;		//colour
};

class OGLCube : public Renderable
{
	private:
		SimpleVertex*	m_vertices;
		unsigned int*	m_indices;

		void			InitUnitCube();
		
	public:
						OGLCube();
						~OGLCube();
		

		void			Render(const Matrix4x4* trans);
};
