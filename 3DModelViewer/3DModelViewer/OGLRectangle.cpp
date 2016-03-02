#include "OGLRectangle.h"
#include <Windows.h>
#include <gl/GL.h>

OGLRectangle::OGLRectangle()
{
	//init the OGLRectangle to a fixed size
	m_topleft.SetX(-50.0f);
	m_topleft.SetY(50.0f);

	m_bottomright.SetX(50.0f);
	m_bottomright.SetY(-50.0f);
}

OGLRectangle::~OGLRectangle()
{

}

void OGLRectangle::Render(const Matrix4x4* trans)
{
	float tlx = m_topleft.GetX();
	float tly = m_topleft.GetY();
	float brx = m_bottomright.GetX();
	float bry = m_bottomright.GetY();

	//Draw a rectangle with psychedelic colour
	glBegin(GL_TRIANGLE_STRIP);								
	glColor3f(1.0f,0.0f,0.0f);						
	glVertex2f(tlx, bry);					
		
	glColor3f(0.0f,1.0f,0.0f);						
	glVertex2f(brx, bry);					
		
	glColor3f(0.0f,0.0f,1.0f);						
	glVertex2f( tlx, tly);
	
	glColor3f(1.0f,0.0f,1.0f);						
	glVertex2f( brx, tly);

	glEnd();
}

bool OGLRectangle::MouseMove( int x, int y )
{
	m_topleft.SetX( (float) x );
	m_topleft.SetY( (float) y );
	
	m_bottomright.SetX( (float) x + 100.0f );
	m_bottomright.SetY( (float) y + 100.0f);
	

	return true;
}

bool OGLRectangle::MouseLBUp( int x, int y )
{
	return true;
}
bool OGLRectangle::MouseLBDown( int x, int y )
{
	return true;
}