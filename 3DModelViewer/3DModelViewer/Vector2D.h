#pragma once
#include <string>

class Vector2D
{
	public:
		Vector2D(void);
		Vector2D(float x, float y);
		Vector2D(const Vector2D& v);
		~Vector2D(void);

		float GetX(void) const;
		void SetX(float x);
		float GetY(void) const;
		void SetY(float y);

		Vector2D& operator= (const Vector2D &rhs);
		const Vector2D operator+(const Vector2D &other) const;
		const Vector2D operator-(const Vector2D &other) const;

	private:
		float _x;
		float _y;

		void Init(float x, float y);
		void Copy(const Vector2D& v);
		
};


