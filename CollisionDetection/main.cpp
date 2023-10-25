#include "Engine.h"
#include <iostream>

int main(int argc, char* argv[])
{
    std::string sceneName = "";
    if (argc == 1) 
    {
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

    myEngine.Run();

    myEngine.Exit();

    return 0;
}