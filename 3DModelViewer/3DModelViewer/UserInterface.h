#pragma once

#include "Renderable.h"
#include "Listener.h"
#include "Vector2D.h"
#include "SlideBar.h"

class UserInterface : public Renderable, public Listener
{
	private:
		Vector2D			workArea_TL, workArea_BL, workArea_BR, workArea_TR; 
		SlideBar			*xRot, *yRot, *zRot, *xTran, *yTran, *zTran; 
		float				oldX, oldY; 


	public:		
		float				xRotation, yRotation, zRotation; 
		float				xTrans, yTrans, zTrans;

		bool				teapot = true, desmond = false, teddy = false, C3P0 = false;

		bool				spin = false;
		bool				fill = true;

							UserInterface();
							~UserInterface();

		void				Render();
		void				ResetAllSliders();
		void				RenderSpinTick();
		void				RenderFilledTick();
		void				RenderModelPicker();
		void				SetXY(float tx, float ty, float bx, float by);
		void				Render(const Matrix4x4* trans = 0);
		bool				MouseMove(int x, int y);
		bool				MouseLBUp(int x, int y);
		bool				MouseLBDown(int x, int y);
		bool				MouseRBDown(int x, int y);
};

