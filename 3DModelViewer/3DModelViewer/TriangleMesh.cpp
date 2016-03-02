//Created for Graphics I and II
//Author: Minsi Chen

#include "Resource.h"
#include "TriangleMesh.h"
#include "OBJFileReader.h"
#include <windows.h>
#include <gl/GL.h>
#include "GLFont.h"

TriangleMesh::TriangleMesh()
{
	m_vertices = NULL;
	m_triangles = NULL;
	m_numTriangles = 0;
	m_numVertices = 0;
}

TriangleMesh::~TriangleMesh()
{
	CleanUp();
}

void TriangleMesh::ModelSelector(bool teapot, bool desmond, bool teddy, bool C3P0)
{

	//If a new model has been chosen, it will load. If the model is already loaded and nothing has changed, it will just pass through
	loadTeapot = teapot;
	loadDesmond = desmond; 
	loadTeddy = teddy; 
	loadC3P0 = C3P0;

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	if (loadTeapot)
	{
		if (!teapotLoaded)
		{
			CleanUp();

			TriangleMesh::LoadMeshFromOBJFile("teapot.obj");
			ComputeTriangleNormals();
			ComputeVertexNormals();
			teapotLoaded = true; 
			desmondLoaded = false; 
			teddyLoaded = false;
			C3P0Loaded = false;
		}
	}
	else if (loadDesmond)
	{
		if (!desmondLoaded)
		{
			CleanUp();

			TriangleMesh::LoadMeshFromOBJFile("Desmond_Miles.obj");
			ComputeTriangleNormals();
			ComputeVertexNormals();
			teapotLoaded = false;
			desmondLoaded = true;
			teddyLoaded = false;
			C3P0Loaded = false;
		}
	}
	else if (loadTeddy)
	{
		if (!teddyLoaded)
		{
			CleanUp();

			TriangleMesh::LoadMeshFromOBJFile("Teddy.obj");
			ComputeTriangleNormals();
			ComputeVertexNormals();
			teapotLoaded = false;
			desmondLoaded = false;
			teddyLoaded = true;
			C3P0Loaded = false;
		}
	}
	else if (loadC3P0)
	{
		if (!C3P0Loaded)
		{
			CleanUp();

			TriangleMesh::LoadMeshFromOBJFile("C3P0.obj");
			ComputeTriangleNormals();
			ComputeVertexNormals();
			teapotLoaded = false;
			desmondLoaded = false;
			teddyLoaded = false;
			C3P0Loaded = true;
		}
	}	
}
void TriangleMesh::Render(const Matrix4x4* trans)
{
	Matrix4x4 transformation = *trans;

	GLfloat mat_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat mat_diffuse[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat mat_Specular[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	GLfloat mat_emmissive[] = { 0.05f, 0.05f, 0.05f, 1.0f };
	float shininess;

	if (!C3P0Loaded)
	{
		shininess = 80.0f;
	}
	else
	{
		shininess = 10.0f;
	}

	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &shininess);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_Specular);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mat_emmissive);

	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_NORMALIZE);

	//Depending on the Fill box, depends how its rendered
	if (Fill)
	{
		glBegin(GL_TRIANGLES);
	}
	else
	{
		glBegin(GL_LINES);
	}

	if (C3P0Loaded) //Gives C3P0 golden colour 
	{
		glColor3f(1.0f, 0.71f, 0.0f);
	}
	else //Only C3P0 deserves colour
	{
		glColor3f(1.0f, 1.0f, 1.0f);
	}

	for (int i = 0; i < m_numTriangles; i++)
	{
		//Translation, pushing it back 300 units on the Z axis, only once. I could of done this by scaling the models or moving them back
		//I chose to move them back, but the scaling does work too. 
		Vector4D tVec;
		if (loadTeapot)
		{
			tVec.SetVector(XTrans, YTrans, -20.5f + ZTrans, 1);
		}

		if (loadDesmond)
		{
			tVec.SetVector(XTrans / 10.0f, YTrans / 10.0f + 0.5f , -5.5f + ZTrans / 10.0f, 1);
		}

		if (loadTeddy)
		{
			tVec.SetVector(XTrans, YTrans, -100.5f + ZTrans * 10.0f, 1);
		}

		if (loadC3P0)
		{
			tVec.SetVector(XTrans, YTrans, -50.0f + ZTrans, 1);
		}

		const int* indices = m_triangles[i].GetVertexIndices();	

		//Makes a copy of the original vertices + transformation (So the original isn't manipulated)
		one = (transformation * m_vertices[indices[0]].m_position) + tVec;
		two = (transformation * m_vertices[indices[1]].m_position) + tVec;
		three = (transformation * m_vertices[indices[2]].m_position) + tVec;

		//Dont need a translation for normals, just the transformation
		Vector4D normalOne = (transformation * m_vertices[indices[0]].m_normal), 
					normalTwo = (transformation * m_vertices[indices[1]].m_normal), 
						normalThree = (transformation * m_vertices[indices[2]].m_normal);

		//Normalise the vectors now everything has been done to them
		normalOne.Normalise(), normalTwo.Normalise(), normalThree.Normalise();

		//Give the vertex backwards, because the model appears to have it vertices clockwise 
		glNormal3f(normalOne[0], normalOne[1], normalOne[2]), 
			glVertex4f(one[0], one[1], one[2], one[3]);
		glNormal3f(normalTwo[0], normalTwo[1], normalTwo[2]),
			glVertex4f(two[0], two[1], two[2], two[3]);
		glNormal3f(normalThree[0], normalThree[1], normalThree[2]),
			glVertex4f(three[0], three[1], three[2], three[3]);	
	}
	glEnd();

}

void TriangleMesh::setFill(bool fill)
{
	Fill = fill;
}

void TriangleMesh::setTransValues(float xTrans, float yTrans, float zTrans)
{
	XTrans = xTrans; 
	YTrans = yTrans; 
	ZTrans = zTrans; 
}

void TriangleMesh::ComputeTriangleNormals()
{
	for (int i = 0; i < m_numTriangles; i++)
	{
		const int* indices = m_triangles[i].GetVertexIndices();
		const int x = 0;
		const int y = 1; 
		const int z = 2; 

		U = (m_vertices[indices[y]].m_position - m_vertices[indices[x]].m_position);
		V = (m_vertices[indices[z]].m_position - m_vertices[indices[x]].m_position);

		Vector4D UV = U.CrossProduct(V);
		m_triangles[i].SetNormal(UV);
	}
}

void TriangleMesh::ComputeVertexNormals()
{
	for (int i = 0; i < m_numTriangles; i++)
	{
		const int* indices = m_triangles[i].GetVertexIndices();

		m_vertices[indices[0]].m_normal = (m_triangles[i - 1].GetNormal() + m_triangles[i+1].GetNormal() + m_triangles[i + 2].GetNormal());
		m_vertices[indices[1]].m_normal = (m_triangles[i - 1].GetNormal() + m_triangles[i+1].GetNormal() + m_triangles[i + 2].GetNormal());
		m_vertices[indices[2]].m_normal = (m_triangles[i - 1].GetNormal() + m_triangles[i+1].GetNormal() + m_triangles[i + 2].GetNormal());

		m_vertices[indices[0]].m_normal.Normalise();
		m_vertices[indices[1]].m_normal.Normalise();
		m_vertices[indices[2]].m_normal.Normalise();
	}
}

bool TriangleMesh::LoadMeshFromOBJFile(const char* filename)
{
	//First pass: reading the OBJ to gether info related to the mesh
	int numVertices = 0;
	int numNormals = 0;
	int numTexCoords = 0;
	int numTriangles = 0;

	if (OBJFileReader::firstPassOBJRead(filename, &numVertices, &numNormals, &numTexCoords, &numTriangles))
	{
		printf("Error parsing file: %s\n", filename);
		return false;
	}
	
	//allocate memory for m_vertices and m_triangles based on the number of vertices and triangles from the first pass
	if (m_vertices && m_triangles)
	{
		printf("Vertex array and triangle array have already been allocated.\n");
		return false;
	}

	m_vertices = new Vertex[numVertices];
	m_triangles = new Triangle[numTriangles];
	
	if (OBJFileReader::secondPassOBJRead(filename, m_vertices, m_triangles))
	{
		printf("Error parsing file: %s\n", filename);
		return false;
	}

	ComputeTriangleNormals();
	ComputeVertexNormals();

	m_numTriangles = numTriangles;
	m_numVertices = numVertices;
	
	return true;
}

void TriangleMesh::CleanUp()
{
	if (m_vertices)
		delete[] m_vertices;
	if (m_triangles)
		delete[] m_triangles;

	m_vertices = NULL;
	m_triangles = NULL;
	m_numTriangles = 0;
	m_numVertices = 0;
}