#pragma once

#include <Windows.h>
#include "OGLRectangle.h"
#include "OGLCube.h"
#include "TriangleMesh.h"
#include "UserInterface.h"

class OGLWindow
{
	private:
		HWND						m_hwnd;		//handle to a window
		HDC							m_hdc;		//handle to a device context
		HGLRC						m_hglrc;	//handle to a gl rendering context
		RECT						clientrect; //Clientrect to share the current rect size 

		int							m_width;	//width of the OGL drawing surface
		int							m_height;	//height of the OGL drawing surface
		
		//This is not an ideal place to hold geometry data
		OGLCube						*m_cube;
		TriangleMesh				*teapot;
		UserInterface				*UI;

		float				rotateX = 0;
		float				rotateY = 0;
		float				rotateZ = 0;

		int					 i = 0;

		float				_width;
		float				_height;
		bool				wireMesh = false; 


	protected:

		HGLRC		CreateOGLContext (HDC hdc);
		BOOL		DestroyOGLContext();
		void		InitOGLState();

	public:
					OGLWindow();
					OGLWindow(HINSTANCE hInstance, int width, int height);
					~OGLWindow();

		BOOL		InitWindow(HINSTANCE hInstance, int width, int height);
		void		Render3D(); //Preps the 3D render 
		void		RenderUI(); //2D
		void		Render();
		void		Resize( int width, int height );
		void		SetVisible( BOOL visible );
		void		DestroyOGLWindow();

		BOOL		MouseLBDown ( int x, int y );
		BOOL		MouseLBUp ( int x, int y );
		BOOL		MouseMove ( int x, int y );
};