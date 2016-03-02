#pragma once
//Created for Graphics I and II
//Author: Minsi Chen

class Vector4D
{
private:
	float		m_element[4];

public:
	Vector4D()
	{
		m_element[0] = 0.0f;
		m_element[1] = 0.0f;
		m_element[2] = 0.0f;
		m_element[3] = 1.0f;
	}
	
	Vector4D(float x, float y, float z, float w = 1.0f)
	{
		m_element[0] = x; m_element[1] = y; m_element[2] = z;
		m_element[3] = w;
	}

	Vector4D(const Vector4D& rhs);

	virtual ~Vector4D() { ; }

	//accessor for each vector component
	//e.g. Vector4D vec; 
	//		vec[0]
	float operator [] (const int i) const;
	float& operator [] (const int i);
	
	//some common vector operators
	Vector4D operator + (const Vector4D& rhs) const;
	Vector4D operator - (const Vector4D& rhs) const;
	Vector4D& operator = (const Vector4D& rhs);
	Vector4D operator * (const Vector4D& rhs) const;
	Vector4D operator * (float scale) const;

	float Length()	const;
	float LengthSqr() const;
	void Normalise();

	float DotProduct(const Vector4D& rhs) const;
	Vector4D CrossProduct(const Vector4D& rhs) const;
	void SetZero();
	inline void SetVector(float x, float y, float z, float w) { m_element[0] = x; m_element[1] = y; m_element[2] = z; m_element[3] = w; }

};

