#include "Resource.h"
#include <windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "OGLWindow.h"
#include "Matrix4x4.h"
#include "Vector4D.h"
#include "TriangleMesh.h"
#include "GLFont.h"
#include "UserInterface.h"

OGLWindow::OGLWindow()
{
	
}

OGLWindow::~OGLWindow()
{
	//Clean up the renderable
	delete m_cube;
}

OGLWindow::OGLWindow(HINSTANCE hInstance, int width, int height)
{
	//InitWindow(hInstance, width, height);
}

HGLRC OGLWindow::CreateOGLContext(HDC hdc)
{
	unsigned int pixelformat;
	HGLRC hglrc;

	static PIXELFORMATDESCRIPTOR pfd = 
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Support Window
		PFD_SUPPORT_OPENGL |						// Format Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request RGBA Format
		32,											// Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits mask
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		32,											// Z-Buffer depth
		0,											// Stencil Buffer
		0,											// Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};

	if (!(pixelformat=ChoosePixelFormat(hdc,&pfd)))
	{
		return 0;
	}

	if(!SetPixelFormat(hdc,pixelformat,&pfd))
	{
		return 0;
	}

	if (!(hglrc=wglCreateContext(hdc)))
	{
		return 0;
	}

	if(!wglMakeCurrent(hdc,hglrc))
	{
		return 0;
	}

	return hglrc;
}

void OGLWindow::DestroyOGLWindow()
{
	DestroyOGLContext();

	DestroyWindow( m_hwnd );

	m_hwnd = NULL;
	m_hdc = NULL;
}

BOOL OGLWindow::DestroyOGLContext()
{
	if ( m_hglrc )
	{
		wglMakeCurrent( NULL, NULL );
		wglDeleteContext( m_hglrc );
		m_hglrc = NULL;
	}
	
	if ( !ReleaseDC ( m_hwnd, m_hdc ) )
		return FALSE;

	return TRUE;
}

BOOL OGLWindow::InitWindow(HINSTANCE hInstance, int width, int height)
{
	RECT clientrect;

	m_hwnd = CreateWindowEx( WS_EX_APPWINDOW | WS_EX_WINDOWEDGE,
		L"OGLWindow", L"OGLWindow", WS_OVERLAPPEDWINDOW|WS_CLIPSIBLINGS|WS_CLIPCHILDREN,
		0, 0, width, height, NULL, NULL, hInstance, NULL);

	if ( ! m_hwnd )
		return FALSE;

	m_hdc = GetDC( m_hwnd );

	GetClientRect(m_hwnd, &clientrect);

	SetWindowPos(m_hwnd, NULL, 10, 10, (width << 1) - clientrect.right, (height << 1) - clientrect.bottom, SWP_HIDEWINDOW | SWP_NOREDRAW);
		
	m_width = width;
	m_height = height;

	if (!(m_hglrc = CreateOGLContext(m_hdc)))
		return FALSE;
	InitOGLState();

	//Instantiate a Renderable as OGLCube
	teapot = new TriangleMesh();
	UI = new UserInterface();

	return TRUE;
}

void OGLWindow::SetVisible ( BOOL visible )
{
	ShowWindow ( m_hwnd, visible? SW_SHOW : SW_HIDE );
}

void OGLWindow::Render3D()
{
	float xTrans = UI->xTrans;
	float yTrans = UI->yTrans;
	float zTrans = UI->zTrans;

	//Enables depth test again now 2D is finished 
	glEnable(GL_DEPTH_TEST);
	//Set up for 3D
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, (double)m_width / (double)m_height, 0.1, 500);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Light0 params 
	GLfloat ambientColour[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat lightColour0[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat lightPos0[] = { -50.0f, 50.0f, 100.0f, 0.0f };
	GLfloat lightSpecular0[] = { 1.0, 1.0, 1.0, 1.0 };

	//Bind the params to the light
	glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, ambientColour);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColour0);
		glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
		glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular0);
	//Enable light
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLoadIdentity();

	teapot->setTransValues(xTrans, yTrans, zTrans);

	if (UI->spin)
	{
		rotateX += UI->xRotation;
		rotateY += UI->yRotation;
		rotateZ += UI->zRotation;
	}
	else
	{
		rotateX = (UI->xRotation * 100);
		rotateY = (UI->yRotation * 100);
		rotateZ = (UI->zRotation * 100);
	}

	Matrix4x4 transformation;
	Matrix4x4 Rz;
		Rz.SetIdentity();
		Rz.SetRotationZAxis(rotateZ);
	Matrix4x4 Rx;
		Rx.SetIdentity();
		Rx.SetRotationXAxis(rotateX);
	Matrix4x4 Ry;
		Ry.SetIdentity();
		Ry.SetRotationYAxis(rotateY);

	transformation.SetIdentity();
	transformation = (Rz * Rx * Ry);

	teapot->setFill(UI->fill);
	teapot->Render(&transformation);

}

void OGLWindow::RenderUI()
{
	//Disables all 3D parameters
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);

	//Sets projection to gl0rtho, with no depth for 2D
	glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-0.5*_width, 0.5*_width, -0.5*_height, 0.5*_height, -1.0, 1.0);

	//Renders the UI, passes in null because there is no transformation needed for the 2D 
	UI->Render(NULL);
	UI->SetXY((clientrect.left - clientrect.right) * 0.5, (clientrect.top - clientrect.bottom) * 0.5, (clientrect.left - clientrect.right) * 0.5, (clientrect.bottom - clientrect.top) * 0.5);

}

void OGLWindow::Render()
{
	//Clears the old buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	teapot->ModelSelector(UI->teapot, UI->desmond, UI->teddy, UI->C3P0);

	Render3D();
	RenderUI();

	glPopMatrix();
	glFlush();
	SwapBuffers(m_hdc);
	return;
}

void OGLWindow::Resize( int width, int height )
{
	_width = width;
	_height = height;

	GetClientRect(m_hwnd, &clientrect);

	int left = width - clientrect.right;
	int top = height - clientrect.bottom;

	m_width = width - left;
	m_height = height - top;

	double aspectratio = (double)m_width / (double)m_height;

	glViewport(0, 0 , m_width, m_height );
	
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();

	gluPerspective(45, aspectratio, 1, 500);
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

	return;
}

void OGLWindow::InitOGLState()
{
	glClearColor( 0.1f, 0.1f, 0.3f, 1.0f );

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

BOOL OGLWindow::MouseLBDown ( int x, int y )
{
	Listener *UI_LBD = static_cast<Listener*>(UI);
	
	UI_LBD->MouseLBDown(x - (clientrect.right * 0.5), -y + (clientrect.bottom * 0.5));

	return TRUE;
}

BOOL OGLWindow::MouseLBUp ( int x, int y )
{
	Listener *UI_LBU = static_cast<Listener*>(UI);

	UI_LBU->MouseLBUp(x - (clientrect.right * 0.5), -y + (clientrect.bottom * 0.5));
	return TRUE;
}

BOOL OGLWindow::MouseMove ( int x, int y )
{
	Listener *UI_MouseMove = static_cast<Listener*>(UI);

	UI_MouseMove->MouseMove(x - (clientrect.right * 0.5), -y + (clientrect.bottom * 0.5));
	return TRUE;
}