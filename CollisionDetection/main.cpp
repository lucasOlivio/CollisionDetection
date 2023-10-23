#include "Engine.h"
#include "common/constants.h"
#include <iostream>

int main(int argc, char* argv[])
{
    std::string sceneName = "";
    if (argc == 1) 
    {
        if (ndebug) {
            printf("Error: Must pass the scene to be loaded as argument!\n");
            exit(EXIT_FAILURE);
        }
        sceneName = "scene";
    }
    else
    {
        sceneName = argv[1];
    }
    
    Engine myEngine = Engine();
    bool isInitialized = myEngine.Initialize(sceneName);
    if (!isInitialized)
    {
        exit(EXIT_FAILURE);
    }

    while (myEngine.IsRunning())
    {
        myEngine.Update();
    }

    myEngine.Destroy();

    return 0;
}