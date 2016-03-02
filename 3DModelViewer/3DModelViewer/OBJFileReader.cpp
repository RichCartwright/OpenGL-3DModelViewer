//Created for Graphics I and II
//Author: Minsi Chen

#include "OBJFileReader.h"
#include "Vector4D.h"

int OBJFileReader::firstPassOBJRead(const char* filename, int* vertex_count, int* vert_normal_count, int* vert_texcoord_count, int* triangle_count)
{
	FILE* pfile;
	errno_t err;

	*vertex_count = 0;
	*vert_normal_count = 0;
	*vert_texcoord_count = 0;
	*triangle_count = 0;

	err = fopen_s(&pfile, filename, "r");

	if (!pfile)
	{
		//something has gone wrong when opening the file.
		return 1;
	}

	char tempbuffer[1024];
	char* strread = fgets(tempbuffer, 1024, pfile);

	do
	{
		char* v = &(tempbuffer[0]);
		if (*v == 'v')
		{
			if (*(v + 1) == 'n')		
				*vert_normal_count += 1;
			else if (*(v + 1) == 't')	
				*vert_texcoord_count += 1;
			else						
				*vertex_count += 1;
		}
		else if (*v == 'f')
		{
			*triangle_count += 1;
		}

		strread = fgets(tempbuffer, 1024, pfile);

	} while (strread != NULL);

	fclose(pfile);

	return 0;
}

int OBJFileReader::secondPassOBJRead(const char* filename, Vertex* inVertices, Triangle* inTriangles)
{
	FILE* pfile;
	errno_t err;

	err = fopen_s(&pfile, filename, "r");

	if (!pfile)
	{
		//something has gone wrong when opening the file.
		return 1;
	}

	char tempbuffer[1024];
	char* strread = fgets(tempbuffer, 1024, pfile);
	int vertex_read = 0;		//the number of vertices read from the file
	int normal_read = 0;		//the number of normals read from the file
	int texcoord_read = 0;		//the number of texture coordinates read from the file
	int triangle_read = 0;		//the number triangles read from the file

	do
	{
		char* v = &(tempbuffer[0]);
		if (*v == 'v')
		{
			float tempx, tempy, tempz;

			if (*(v + 1) == 'n')  //the line starts with "vn", i.e. a normal
			{
				sscanf_s(v, "%*s %f %f %f", &tempx, &tempy,	&tempz);
				
				//N.B. we will not use the normals stored in the file
				//all normals will be computed in TriangleMesh, see TriangleMesh::ComputeTriangleNormals and TriangleMesh::ComputeVertexNormals

				normal_read += 1;
			}
			else if (*(v + 1) == 't') //the line starts with "vt", i.e., texture coordinate
			{
				sscanf_s(v, "%*s %f %f", &tempx, &tempy);
				texcoord_read += 1;
			}
			else //the line starts with v, i.e. vertex position
			{
				sscanf_s(v + 1, "%f %f %f", &tempx, &tempy,	&tempz);
				
				//Store the vertex position in the vertex array 
				inVertices[vertex_read].m_position.SetVector(tempx, tempy, tempz, 1.0f);

				vertex_read += 1;
			}
		}
		else if (*v == 'f') //reading a face (triangle)
		{
			int vidx1, vidx2, vidx3;	//vertex indices
			
			int nidx1, nidx2, nidx3;	//normal indices

			int tidx1, tidx2, tidx3;	//texture coordinate indices

			if (sscanf_s(v, "%*s %d/%d/%d %d/%d/%d %d/%d/%d", &vidx1, &tidx1, &nidx1,
				&vidx2, &tidx2, &nidx2,
				&vidx3, &tidx3, &nidx3) == 9) //vertex, texture coordinates and normal
			{
				inTriangles[triangle_read].SetVertexIndices(vidx1 - 1, vidx2 - 1 , vidx3 - 1);
			}
			else if (sscanf_s(v, "%*s %d %d %d", &vidx1, &vidx2, &vidx3) == 3) //vertex only 
			{
				inTriangles[triangle_read].SetVertexIndices(vidx1 - 1, vidx2 - 1, vidx3 - 1);
			}
			else if (sscanf_s(v, "%*s %d/%d %d/%d %d/%d", &vidx1, &vidx2, &vidx3,
				&tidx1, &tidx2, &tidx3) == 3) // vertex and texture coordinates
			{
				inTriangles[triangle_read].SetVertexIndices(vidx1 - 1, vidx2 - 1, vidx3 - 1);
			}
			else if (sscanf_s(v, "%*s %d//%d %d//%d %d//%d", &vidx1, &vidx2, &vidx3,
				&nidx1, &nidx2, &nidx3) == 3) // vertex and normal
			{
				inTriangles[triangle_read].SetVertexIndices(vidx1 - 1, vidx2 - 1, vidx3 - 1);
			}
			else
			{
				//something is seriously fucked. abort
				//I don't want to deal with this.
				break;
			}
			triangle_read += 1;
		}

		strread = fgets(tempbuffer, 1024, pfile);

	} while (strread != NULL);

	fclose(pfile);

	return 0;
}