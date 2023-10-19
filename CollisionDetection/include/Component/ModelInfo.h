#pragma once

#include <string>

// The vertex structure 
//	that's ON THE GPU (eventually) 
// So dictated from THE SHADER
struct Vertex
{
	float x, y, z, w;
	float r, g, b, a;
	float nx, ny, nz, nw;
};

struct ModelDrawInfo
{
	ModelDrawInfo();
	~ModelDrawInfo();

	std::string meshName;

	unsigned int VAOID;

	unsigned int vertexBufferID;
	unsigned int vertexBufferStartIndex;
	unsigned int numberOfVertices;

	unsigned int indexBufferID;
	unsigned int indexBufferStartIndex;
	unsigned int numberOfIndices;
	unsigned int numberOfTriangles;

	// The "local" (i.e. "CPU side" temporary array)
	Vertex* pVertices;	//  = 0;
	// The index buffer (CPU side)
	unsigned int* pIndices;
};