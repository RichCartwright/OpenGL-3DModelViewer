#pragma once

class Vector4D;

class Matrix4x4
{
private:
	float				m_element[4][4];

public:
	Matrix4x4();
	Matrix4x4(const Matrix4x4& rhs);
	~Matrix4x4();

	void				SetZero();
	void				SetIdentity();
	const float*		ToPtr() const;
	
	//The following methods are not implemented
	//This is a part of the basic requirements for Coursework 2
	Matrix4x4			operator*(const Matrix4x4& rhs) const;
	Vector4D			operator*(const Vector4D& rhs) const;
	
	void				SetRotationXAxis(float degrees);
	void				SetRotationYAxis(float degrees);
	void				SetRotationZAxis(float degrees);
	void				SetTranslate(const Vector4D& tvec);
	void				SetScale(float sx, float sy, float sz);
	void				SetViewMatrix(const Vector4D& camera_position, const Vector4D& view_vector, const Vector4D& up_vector);
};

