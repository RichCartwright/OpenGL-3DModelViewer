#pragma once

//This is an abstract class
//It cannot be instantiated without being inherited by a concrete class

class Matrix4x4;

class Renderable
{
	public:

		//this is a pure virtual function
		virtual void			Render(const Matrix4x4* trans = 0) = 0;
};