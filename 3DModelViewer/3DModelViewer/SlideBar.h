#pragma once

#include "Renderable.h"
#include "Listener.h"
#include "Vector2D.h"

class SlideBar : public Renderable, public Listener
{
private:
	Vector2D			slideBarLeft, slideBarRight;
	Vector2D			SliderTopLeft, SliderTopRight, SliderBottomLeft, SliderBottomRight;
	Vector2D			SliderPoint;

	float				lowNumber;
	float				highNumber;

	char*				ID;

	float				slideBarLX, slideBarLY, slideBarRX, slideBarRY;
	float				stlX, stlY, strX, strY, sblX, sblY, sbrX, sbrY;
	float				spX, spY;
	float				incrementX;
	float				incrementStep;
	float				value;
	float				middleBar;
	float				leftDifference;

	bool				mouseDown = false;
	bool				sliderClicked = false;
	bool				belowLowerBound = false;
	bool				aboveUpperBound = false;

	float				oldX = 0, oldY = 0;
	float				oldXWindow = 0, oldYWindow = 0;

	float				alpha = 1.0f;


public:
	SlideBar();
	SlideBar(char * id, float lowNum, float highNum, float x, float y);
	~SlideBar();

	void				SetAlpha(float _alpha);
	void				ResetSlideBar();
	void				SetXY(float x, float y);
	float				ReturnValue();
	void				RenderSlideLine();
	void				RenderSlideButton();

	void				RenderValueDisplay();

	void				RenderLabel();
	void				Render(const Matrix4x4 * trans);
	bool				MouseMove(int x, int y);
	bool				MouseLBUp(int x, int y);
	bool				MouseLBDown(int x, int y);
	bool				MouseRBDown(int x, int y);
};

