#include "Manager/VAOManager.h"

#include "Common/OpenGL.h"
#include "Common/ModelLoader.h"
#include "Component/ModelInfo.h"

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include <vector>

#include <sstream>
#include <fstream>


void VAOManager::DestroyVBO(std::string modelName)
{
    ModelDrawInfo* pModelInfo = this->FindDrawInfoByModelName(modelName);
    if (!pModelInfo)
    {
        //Model not loaded
        return;
    }
    glDeleteBuffers(1, &(pModelInfo->vertexBufferID));
    this->m_mapModelNameToVAOID.erase(modelName);
    delete pModelInfo;
    return;
}

bool VAOManager::LoadModelIntoVAO(
    std::string fileName,
    unsigned int shaderProgramID) {
    // Load the model from file
    // Checking if the info already exist in our map
    ModelDrawInfo* pDrawInfo = this->FindDrawInfoByModelName(fileName);
    if (pDrawInfo)
    {
        // Info is already loaded
        return true;
    }
    pDrawInfo = new ModelDrawInfo();
    pDrawInfo->meshName = fileName;

    if (!LoadData(fileName, pDrawInfo))
    {
        return false;
    };

    // Ask OpenGL for a new buffer ID...
    glGenVertexArrays(1, &(pDrawInfo->VAOID));
    // "Bind" this buffer:
    // - aka "make this the 'current' VAO buffer
    glBindVertexArray(pDrawInfo->VAOID);

    // Now ANY state that is related to vertex or index buffer
    //	and vertex attribute layout, is stored in the 'state' 
    //	of the VAO... 


    // NOTE: OpenGL error checks have been omitted for brevity
//	glGenBuffers(1, &vertex_buffer);
    glGenBuffers(1, &(pDrawInfo->vertexBufferID));

    //	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, pDrawInfo->vertexBufferID);
    // sVert vertices[3]
    glBufferData(GL_ARRAY_BUFFER,
        sizeof(Vertex) * pDrawInfo->numberOfVertices,	// ::g_NumberOfVertsToDraw,	// sizeof(vertices), 
        (GLvoid*)pDrawInfo->pVertices,							// pVertices,			//vertices, 
        GL_STATIC_DRAW);


    // Copy the index buffer into the video card, too
    // Create an index buffer.
    glGenBuffers(1, &(pDrawInfo->indexBufferID));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pDrawInfo->indexBufferID);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER,			// Type: Index element array
        sizeof(unsigned int) * pDrawInfo->numberOfIndices,
        (GLvoid*)pDrawInfo->pIndices,
        GL_STATIC_DRAW);

    // Set the vertex attributes.

    GLint vpos_location = glGetAttribLocation(shaderProgramID, "vPos");	// program
    GLint vcol_location = glGetAttribLocation(shaderProgramID, "vCol");	// program;
    GLint vNormal_location = glGetAttribLocation(shaderProgramID, "vNormal");	// program;

    // Set the vertex attributes for this shader
    glEnableVertexAttribArray(vpos_location);	    // vPos
    glVertexAttribPointer(vpos_location, 4,		// vPos
        GL_FLOAT, GL_FALSE,
        sizeof(Vertex),
        (void*)offsetof(Vertex, x));

    glEnableVertexAttribArray(vcol_location);	    // vCol
    glVertexAttribPointer(vcol_location, 4,		// vCol
        GL_FLOAT, GL_FALSE,
        sizeof(Vertex),
        (void*)offsetof(Vertex, r));

    glEnableVertexAttribArray(vNormal_location);	// vNormal
    glVertexAttribPointer(vNormal_location, 4,		// vNormal
        GL_FLOAT, GL_FALSE,
        sizeof(Vertex),
        (void*)offsetof(Vertex, nx));

    // Now that all the parts are set up, set the VAO to zero
    glBindVertexArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glDisableVertexAttribArray(vpos_location);
    glDisableVertexAttribArray(vcol_location);
    glDisableVertexAttribArray(vNormal_location);

    // Store the draw information into the map
    this->m_mapModelNameToVAOID[pDrawInfo->meshName] = pDrawInfo;

    return true;
}


// We don't want to return an int, likely
ModelDrawInfo* VAOManager::FindDrawInfoByModelName(std::string filename) {
    std::map< std::string /*model name*/,
        ModelDrawInfo* /* info needed to draw*/ >::iterator
        itDrawInfo = this->m_mapModelNameToVAOID.find(filename);

    // Find it? 
    if (itDrawInfo == this->m_mapModelNameToVAOID.end()) {
        // Nope
        return nullptr;
    }

    // Else we found the thing to draw
    // ...so 'return' that information
    return itDrawInfo->second;
}
