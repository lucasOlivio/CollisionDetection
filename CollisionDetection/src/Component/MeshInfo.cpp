#include "Component/ModelInfo.h"

ModelDrawInfo::ModelDrawInfo()
{
    this->VAOID = 0;

    this->vertexBufferID = 0;
    this->vertexBufferStartIndex = 0;
    this->numberOfVertices = 0;

    this->indexBufferID = 0;
    this->indexBufferStartIndex = 0;
    this->numberOfIndices = 0;
    this->numberOfTriangles = 0;

    // The "local" (i.e. "CPU side" temporary array)
    this->pVertices = nullptr;	// or NULL
    this->pIndices = nullptr;		// or NULL

    return;
}

ModelDrawInfo::~ModelDrawInfo() 
{
    if (this->pVertices)
    {
        delete this->pVertices;
    }
    if (this->pIndices)
    {
        delete this->pIndices;
    }
}