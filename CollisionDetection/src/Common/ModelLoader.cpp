#include <iostream>

#include "Common/ModelLoader.h"
#include "Common/cFileLoader_Imp.h"

const std::string BASE_PATH_MODELS = "assets/models/";

bool LoadData(std::string fileName, ModelDrawInfo* pDrawInfo)
{
    AssimpHelper::cFileLoader helper = AssimpHelper::cFileLoader();
    AssimpHelper::cFileLoader::sPostProcessFlags loadFlags;

    std::string fileFullPath = BASE_PATH_MODELS + fileName;
	bool isMeshLoaded = helper.Load3DModelFile(fileFullPath, loadFlags, pDrawInfo);
    if (!isMeshLoaded)
    {
        std::cout << "Error:" << helper.getLastError().c_str();
        return false;
    }

    return true;
}
