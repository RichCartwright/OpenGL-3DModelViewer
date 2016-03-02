#include "UserInterface.h"
#include "GLFont.h"
#include <Windows.h>
#include "OGLWindow.h"
#include <gl/GL.h>
#include <sstream>
#include "SlideBar.h"


UserInterface::UserInterface()
{
	xRot = new SlideBar("XRot", -30.0f, 30.0f, workArea_TL.GetX() + 20.0f, workArea_TL.GetY() + 20.0f);
	yRot = new SlideBar("YRot", -30.0f, 30.0f, workArea_TL.GetX() + 20.0f, workArea_TL.GetY() + 20.0f);
	zRot = new SlideBar("ZRot", -30.0f, 30.0f, workArea_TL.GetX() + 20.0f, workArea_TL.GetY() + 20.0f);

	xTran = new SlideBar("XTrans", -30.0f, 30.0f, workArea_TL.GetX() + 20.0f, workArea_TL.GetY() + 20.0f);
	yTran = new SlideBar("YTrans", -30.0f, 30.0f, workArea_TL.GetX() + 20.0f, workArea_TL.GetY() + 20.0f);
	zTran = new SlideBar("ZTrans", -30.0f, 30.0f, workArea_TL.GetX() + 20.0f, workArea_TL.GetY() + 20.0f);
}

UserInterface::~UserInterface()
{
}

void UserInterface::Render()
{
}

void UserInterface::ResetAllSliders()
{
	xTran->ResetSlideBar();
	yTran->ResetSlideBar();
	zTran->ResetSlideBar();
}

void UserInterface::RenderSpinTick()
{
	GLFont *spinLabel = new GLFont();
	spinLabel->Create("Fonts\\another_font.glf");
	spinLabel->Begin();
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
			spinLabel->RenderText("Spin ", workArea_TL.GetX() + 10.0f, workArea_BR.GetY() - 350.0f, 0, 8);
	spinLabel->End();
	delete spinLabel;

	glBegin(GL_QUADS);
		glColor3f(1.0f, 1.0f, 1.0f);
			glVertex2f(workArea_TL.GetX() + 160.0f, workArea_BR.GetY() - 350.0f);
			glVertex2f(workArea_TL.GetX() + 160.0f, workArea_BR.GetY() - 370.0f);
			glVertex2f(workArea_TL.GetX() + 180.0f, workArea_BR.GetY() - 370.0f);
			glVertex2f(workArea_TL.GetX() + 180.0f, workArea_BR.GetY() - 350.0f);
	glEnd();

	if (spin)
	{
		glBegin(GL_QUADS);
			glColor3f(0.0f, 0.0f, 0.0f);
				glVertex2f(workArea_TL.GetX() + 165.0f, workArea_BR.GetY() - 355.0f);
				glVertex2f(workArea_TL.GetX() + 165.0f, workArea_BR.GetY() - 365.0f);
				glVertex2f(workArea_TL.GetX() + 175.0f, workArea_BR.GetY() - 365.0f);
				glVertex2f(workArea_TL.GetX() + 175.0f, workArea_BR.GetY() - 355.0f);
		glEnd();
	}
}

void UserInterface::RenderFilledTick()
{
	GLFont *fillLabel = new GLFont();
	fillLabel->Create("Fonts\\another_font.glf");
	fillLabel->Begin();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	fillLabel->RenderText("Fill ", workArea_TL.GetX() + 10.0f, workArea_BR.GetY() - 400.0f, 0, 8);
	fillLabel->End();
	delete fillLabel;

	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(workArea_TL.GetX() + 160.0f, workArea_BR.GetY() - 400.0f);
	glVertex2f(workArea_TL.GetX() + 160.0f, workArea_BR.GetY() - 420.0f);
	glVertex2f(workArea_TL.GetX() + 180.0f, workArea_BR.GetY() - 420.0f);
	glVertex2f(workArea_TL.GetX() + 180.0f, workArea_BR.GetY() - 400.0f);
	glEnd();

	if (fill)
	{
		glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex2f(workArea_TL.GetX() + 165.0f, workArea_BR.GetY() - 405.0f);
		glVertex2f(workArea_TL.GetX() + 165.0f, workArea_BR.GetY() - 415.0f);
		glVertex2f(workArea_TL.GetX() + 175.0f, workArea_BR.GetY() - 415.0f);
		glVertex2f(workArea_TL.GetX() + 175.0f, workArea_BR.GetY() - 405.0f);
		glEnd();
	}
}

void UserInterface::RenderModelPicker()
{
	//Renders the title
	GLFont *modelSelectorLabel = new GLFont();
	modelSelectorLabel->Create("Fonts\\another_font.glf");
	modelSelectorLabel->Begin();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	modelSelectorLabel->RenderText("Model Selector: ", workArea_TL.GetX() + 10.0f, workArea_BR.GetY() - 450.0f, 0, 8);
	modelSelectorLabel->End();
	delete modelSelectorLabel;

	///////////////////////////////////////////////////////////////////////////////

	GLFont *teapotLabel = new GLFont();
	teapotLabel->Create("Fonts\\another_font.glf");
	teapotLabel->Begin();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	teapotLabel->RenderText("Teapot ", workArea_TL.GetX() + 10.0f, workArea_BR.GetY() - 500.0f, 0, 8);
	teapotLabel->End();
	delete teapotLabel;

	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(workArea_TL.GetX() + 160.0f, workArea_BR.GetY() - 500.0f);
	glVertex2f(workArea_TL.GetX() + 160.0f, workArea_BR.GetY() - 520.0f);
	glVertex2f(workArea_TL.GetX() + 180.0f, workArea_BR.GetY() - 520.0f);
	glVertex2f(workArea_TL.GetX() + 180.0f, workArea_BR.GetY() - 500.0f);
	glEnd();

	if (teapot)
	{
		glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex2f(workArea_TL.GetX() + 165.0f, workArea_BR.GetY() - 505.0f);
		glVertex2f(workArea_TL.GetX() + 165.0f, workArea_BR.GetY() - 515.0f);
		glVertex2f(workArea_TL.GetX() + 175.0f, workArea_BR.GetY() - 515.0f);
		glVertex2f(workArea_TL.GetX() + 175.0f, workArea_BR.GetY() - 505.0f);
		glEnd();
	}

	//Desmond
	GLFont *desmondLabel = new GLFont();
	desmondLabel->Create("Fonts\\another_font.glf");
	desmondLabel->Begin();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	desmondLabel->RenderText("Desmond Miles ", workArea_TL.GetX() + 10.0f, workArea_BR.GetY() - 550.0f, 0, 8);
	desmondLabel->End();
	delete desmondLabel;

	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(workArea_TL.GetX() + 160.0f, workArea_BR.GetY() - 550.0f);
	glVertex2f(workArea_TL.GetX() + 160.0f, workArea_BR.GetY() - 570.0f);
	glVertex2f(workArea_TL.GetX() + 180.0f, workArea_BR.GetY() - 570.0f);
	glVertex2f(workArea_TL.GetX() + 180.0f, workArea_BR.GetY() - 550.0f);
	glEnd();

	if (desmond)
	{
		glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex2f(workArea_TL.GetX() + 165.0f, workArea_BR.GetY() - 555.0f);
		glVertex2f(workArea_TL.GetX() + 165.0f, workArea_BR.GetY() - 565.0f);
		glVertex2f(workArea_TL.GetX() + 175.0f, workArea_BR.GetY() - 565.0f);
		glVertex2f(workArea_TL.GetX() + 175.0f, workArea_BR.GetY() - 555.0f);
		glEnd();
	}

	//Teddy
	GLFont *teddyLabel = new GLFont();
	teddyLabel->Create("Fonts\\another_font.glf");
	teddyLabel->Begin();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	teddyLabel->RenderText("Teddy ", workArea_TL.GetX() + 10.0f, workArea_BR.GetY() - 600.0f, 0, 8);
	teddyLabel->End();
	delete teddyLabel;

	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(workArea_TL.GetX() + 160.0f, workArea_BR.GetY() - 600.0f);
	glVertex2f(workArea_TL.GetX() + 160.0f, workArea_BR.GetY() - 620.0f);
	glVertex2f(workArea_TL.GetX() + 180.0f, workArea_BR.GetY() - 620.0f);
	glVertex2f(workArea_TL.GetX() + 180.0f, workArea_BR.GetY() - 600.0f);
	glEnd();

	if (teddy)
	{
		glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex2f(workArea_TL.GetX() + 165.0f, workArea_BR.GetY() - 605.0f);
		glVertex2f(workArea_TL.GetX() + 165.0f, workArea_BR.GetY() - 615.0f);
		glVertex2f(workArea_TL.GetX() + 175.0f, workArea_BR.GetY() - 615.0f);
		glVertex2f(workArea_TL.GetX() + 175.0f, workArea_BR.GetY() - 605.0f);
		glEnd();
	}

	//C3P0
	GLFont *C3P0Label = new GLFont();
	C3P0Label->Create("Fonts\\another_font.glf");
	C3P0Label->Begin();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	C3P0Label->RenderText("C-3P0", workArea_TL.GetX() + 10.0f, workArea_BR.GetY() - 650.0f, 0, 8);
	C3P0Label->End();
	delete C3P0Label;

	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(workArea_TL.GetX() + 160.0f, workArea_BR.GetY() - 650.0f);
	glVertex2f(workArea_TL.GetX() + 160.0f, workArea_BR.GetY() - 670.0f);
	glVertex2f(workArea_TL.GetX() + 180.0f, workArea_BR.GetY() - 670.0f);
	glVertex2f(workArea_TL.GetX() + 180.0f, workArea_BR.GetY() - 650.0f);
	glEnd();

	if (C3P0)
	{
		glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex2f(workArea_TL.GetX() + 165.0f, workArea_BR.GetY() - 655.0f);
		glVertex2f(workArea_TL.GetX() + 165.0f, workArea_BR.GetY() - 665.0f);
		glVertex2f(workArea_TL.GetX() + 175.0f, workArea_BR.GetY() - 665.0f);
		glVertex2f(workArea_TL.GetX() + 175.0f, workArea_BR.GetY() - 655.0f);
		glEnd();
	}
}

void UserInterface::SetXY(float tx, float ty, float bx, float by)
{
	workArea_TL.SetX(tx), workArea_TL.SetY(ty);
	workArea_BL.SetX(bx), workArea_BL.SetY(by);
	workArea_BR.SetX(tx + 200.0f), workArea_BR.SetY(by);
	workArea_TR.SetX(tx + 200.0f), workArea_TR.SetY(ty);
}

void UserInterface::Render(const Matrix4x4 * trans)
{
	xRotation = xRot->ReturnValue();
	yRotation = yRot->ReturnValue();
	zRotation = zRot->ReturnValue();
	xTrans = xTran->ReturnValue();
	yTrans = yTran->ReturnValue();
	zTrans = zTran->ReturnValue();

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glBegin(GL_QUADS);
		glColor4f(0.3f, 0.3f, 0.3f, 0.5f);
			glVertex2f(workArea_TL.GetX(), workArea_TL.GetY());
			glVertex2f(workArea_BL.GetX(), workArea_BL.GetY());
			glVertex2f(workArea_BR.GetX(), workArea_BR.GetY());
			glVertex2f(workArea_TR.GetX(), workArea_TR.GetY());
	glEnd();

	xRot->SetXY(workArea_TL.GetX() + 20.0f, workArea_BR.GetY() - 50.0f);
	yRot->SetXY(workArea_TL.GetX() + 20.0f, workArea_BR.GetY() - 100.0f);
	zRot->SetXY(workArea_TL.GetX() + 20.0f, workArea_BR.GetY() - 150.0f);
	xTran->SetXY(workArea_TL.GetX() + 20.0f, workArea_BR.GetY() - 200.0f);
	yTran->SetXY(workArea_TL.GetX() + 20.0f, workArea_BR.GetY() - 250.0f);
	zTran->SetXY(workArea_TL.GetX() + 20.0f, workArea_BR.GetY() - 300.0f);

	RenderSpinTick();
	RenderFilledTick();
	RenderModelPicker();

	xRot->Render(NULL);
	yRot->Render(NULL);
	zRot->Render(NULL);

	xTran->Render(NULL);
	yTran->Render(NULL);
	zTran->Render(NULL);

}

bool UserInterface::MouseMove(int x, int y)
{
	Listener *xRotMouseMove = static_cast<Listener*>(xRot);
	Listener *yRotMouseMove = static_cast<Listener*>(yRot);
	Listener *zRotMouseMove = static_cast<Listener*>(zRot);

	Listener *xTranMouseMove = static_cast<Listener*>(xTran);
	Listener *yTranMouseMove = static_cast<Listener*>(yTran);
	Listener *zTranMouseMove = static_cast<Listener*>(zTran);

	xRotMouseMove->MouseMove(x - oldX, y);
	yRotMouseMove->MouseMove(x - oldX, y);
	zRotMouseMove->MouseMove(x - oldX, y);

	xTranMouseMove->MouseMove(x - oldX, y);
	yTranMouseMove->MouseMove(x - oldX, y);
	zTranMouseMove->MouseMove(x - oldX, y);

	oldX = x; 
	oldY = y;
	return true;
}

bool UserInterface::MouseLBUp(int x, int y)
{
	Listener *xRotLBU = static_cast<Listener*>(xRot);
	Listener *yRotLBU = static_cast<Listener*>(yRot);
	Listener *zRotLBU = static_cast<Listener*>(zRot);

	Listener *xTranLBU = static_cast<Listener*>(xTran);
	Listener *yTranLBU = static_cast<Listener*>(yTran);
	Listener *zTranLBU = static_cast<Listener*>(zTran);

	xRotLBU->MouseLBUp(x, y);
	yRotLBU->MouseLBUp(x, y);
	zRotLBU->MouseLBUp(x, y);

	xTranLBU->MouseLBUp(x, y);
	yTranLBU->MouseLBUp(x, y);
	zTranLBU->MouseLBUp(x, y);

	if (x > (workArea_TL.GetX() + 160.0f) && x < (workArea_TL.GetX() + 180.0f) && y > (workArea_BR.GetY() - 370.0f) && y < (workArea_BR.GetY() - 350.0f))
	{
		if (spin)
		{
			spin = false;
		}
		else if (!spin)
		{
			spin = true;
		}
	}

	if (x > (workArea_TL.GetX() + 160.0f) && x < (workArea_TL.GetX() + 180.0f) && y >(workArea_BR.GetY() - 420.0f) && y < (workArea_BR.GetY() - 400.0f))
	{
		if (fill)
		{
			fill = false;
		}
		else if (!fill)
		{
			fill = true;
		}
	}

	if (x > (workArea_TL.GetX() + 160.0f) && x < (workArea_TL.GetX() + 180.0f) && y >(workArea_BR.GetY() - 520.0f) && y < (workArea_BR.GetY() - 500.0f))
	{
		if (!teapot)
		{
			teapot = true;
			desmond = false;
			teddy = false;
			C3P0 = false;
			ResetAllSliders();
		}
	}

	if (x >(workArea_TL.GetX() + 160.0f) && x < (workArea_TL.GetX() + 180.0f) && y >(workArea_BR.GetY() - 570.0f) && y < (workArea_BR.GetY() - 550.0f))
	{
		if (!desmond)
		{
			teapot = false;
			desmond = true;
			teddy = false;
			C3P0 = false;
			ResetAllSliders();

		}
	}

	if (x >(workArea_TL.GetX() + 160.0f) && x < (workArea_TL.GetX() + 180.0f) && y >(workArea_BR.GetY() - 620.0f) && y < (workArea_BR.GetY() - 600.0f))
	{
		if (!teddy)
		{
			teapot = false;
			desmond = false;
			teddy = true;
			C3P0 = false;
			ResetAllSliders();

		}
	}

	if (x >(workArea_TL.GetX() + 160.0f) && x < (workArea_TL.GetX() + 180.0f) && y >(workArea_BR.GetY() - 670.0f) && y < (workArea_BR.GetY() - 650.0f))
	{
		if (!C3P0)
		{
			teapot = false;
			desmond = false;
			teddy = false;
			C3P0 = true;
			ResetAllSliders();

		}
	}

	return false;
}

bool UserInterface::MouseLBDown(int x, int y)
{	
	oldX = x;
	oldY = y;

	Listener *xRotLBD = static_cast<Listener*>(xRot);
	Listener *yRotLBD = static_cast<Listener*>(yRot);
	Listener *zRotLBD = static_cast<Listener*>(zRot);

	Listener *xTranLBD = static_cast<Listener*>(xTran);
	Listener *yTranLBD = static_cast<Listener*>(yTran);
	Listener *zTranLBD = static_cast<Listener*>(zTran);

	yRotLBD->MouseLBDown(x, y);
	xRotLBD->MouseLBDown(x, y);
	zRotLBD->MouseLBDown(x, y);

	xTranLBD->MouseLBDown(x, y);
	yTranLBD->MouseLBDown(x, y);
	zTranLBD->MouseLBDown(x, y);

	return true;
}

bool UserInterface::MouseRBDown(int x, int y)
{
	return false;
}
