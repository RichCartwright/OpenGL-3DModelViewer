//Created for Graphics I and II
//Author: Minsi Chen

#pragma once

#include "TriangleMesh.h"

//N.B. This OBJ file parser can only parse triangle faces from an OBJ file, all other face type will not be read correctly
class OBJFileReader
{
	public:

		//Parsing the given OBJ file without extracting data
		//Usage
		//1. filename, path to the OBJ file
		//2. vertex_out returns the number of vertices stored in the file
		//3. vert_normal_count returns the number normals stored in the file
		//4. vert_texcoord_count returns the number texture coordinates stored in the file
		//5. triangle_count returns the number triangles stored in the file
		static int firstPassOBJRead(const char* filename, int* vertex_count, int* vert_normal_count, int* vert_texcoord_count, int* triangle_count);

		//Parsing the given OBJ file and extract all data and stored them into a vertex array and a triangle array
		//Usage
		//1. filename, path to the OBJ file
		//2. inVertices, pointer to an array of Vertex to where the extracted vertices are stored
		//3. inTriangles, pointer to an array of Triangle to where the extracted vertices are stored
		static int secondPassOBJRead(const char* filename, Vertex* inVertices, Triangle* inTriangles);
};