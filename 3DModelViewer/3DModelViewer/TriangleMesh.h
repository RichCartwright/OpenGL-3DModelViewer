//Created for Graphics I and II
//Author: Minsi Chen

#pragma once
#include "Renderable.h"
#include "Triangle.h"
#include "Vector4D.h"
#include "Matrix4x4.h"
#include <vector>

//A minimalistic Vertex structure
struct Vertex
{
	Vector4D m_position;	//the position of the vertex
	Vector4D m_normal;		//the vertex normal 
};

class TriangleMesh : public Renderable
{
	private:
		Vertex*				m_vertices;			//a list of vertices
		Triangle*			m_triangles;		//a list of triangles
		int					m_numVertices;		//the number of vertices in the mesh
		int					m_numTriangles;		//the number of triangles in the mesh
		Vector4D			one, two, three;	//Three vectors that make the triangle
		Vector4D			normal;				//Vector for the triangle normal
		Vector4D			U;
		Vector4D			V;

		bool				Fill;
		void				ComputeTriangleNormals();
		void				ComputeVertexNormals();
		float				XTrans, YTrans, ZTrans;

		bool				teapotLoaded, desmondLoaded, teddyLoaded, C3P0Loaded; 
		bool				loadTeapot, loadDesmond, loadTeddy, loadC3P0; 

	public:
							TriangleMesh();
							~TriangleMesh();

		void				ModelSelector(bool teapot, bool desmond, bool teddy, bool C3P0);
		void				Render(const Matrix4x4* trans = 0);
		void				setFill(bool fill);
		void				setTransValues(float xTrans, float yTrans, float zTrans);
		bool				LoadMeshFromOBJFile(const char* filename);
		void				CleanUp();
};

