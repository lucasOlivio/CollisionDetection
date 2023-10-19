#include "Common/Global.h"
#include "System/MainSystem.h"
#include "Common/OpenGL.h"
#include <cstdio>

MainSystem* pgMainSystem = new MainSystem();

// TODO: Callbacks should be in an event system, managed by queues or in an observever pattern, for now will be here for simplicity

void ErrorCallback(int error, const char* description) {
    fprintf(stderr, "Error: %s\n", description);
}

// TODO: This should only work when the game is not playing, should have 2 states playing and editing.
// And when stop playing should come back to initial positions

// This callback is from the "typing" windows system
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    // Close window
    if (key == GLFW_KEY_ESCAPE && (action == GLFW_PRESS))
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
        return;
    }

    // Save scene
    if (key == GLFW_KEY_F1 && (action == GLFW_PRESS))
    {
        pgMainSystem->Save();
        return;
    }
    if (key == GLFW_KEY_F5 && (action == GLFW_PRESS))
    {
        pgMainSystem->Reload();
        return;
    }

    // CTRL key down + action key
    // Light controls
    // --------------------------------------------
    if ((mods & GLFW_MOD_CONTROL) == GLFW_MOD_CONTROL)
    {
        // Light selection
        // --------------------------------------------
        if (key == GLFW_KEY_PAGE_UP && (action == GLFW_PRESS || action == GLFW_REPEAT))
        {
            pgMainSystem->pSceneSystem->pLightManager->ChangeSelectedLight(1);
            return;
        }
        if (key == GLFW_KEY_PAGE_DOWN && (action == GLFW_PRESS || action == GLFW_REPEAT))
        {
            pgMainSystem->pSceneSystem->pLightManager->ChangeSelectedLight(-1);
            return;
        }
        // --------------------------------------------

        // Light position
        // --------------------------------------------
        if (key == GLFW_KEY_A && (action == GLFW_PRESS || action == GLFW_REPEAT))
        {
            pgMainSystem->pSceneSystem->pLightManager->MoveSelectedLight(0, -1);
            return;
        }
        if (key == GLFW_KEY_D && (action == GLFW_PRESS || action == GLFW_REPEAT))
        {
            pgMainSystem->pSceneSystem->pLightManager->MoveSelectedLight(0, 1);
            return;
        }

        if (key == GLFW_KEY_Q && (action == GLFW_PRESS || action == GLFW_REPEAT))
        {
            pgMainSystem->pSceneSystem->pLightManager->MoveSelectedLight(1, -1);
            return;
        }
        if (key == GLFW_KEY_E && (action == GLFW_PRESS || action == GLFW_REPEAT))
        {
            pgMainSystem->pSceneSystem->pLightManager->MoveSelectedLight(1, 1);
            return;
        }

        if (key == GLFW_KEY_S && (action == GLFW_PRESS || action == GLFW_REPEAT))
        {
            pgMainSystem->pSceneSystem->pLightManager->MoveSelectedLight(2, -1);
            return;
        }
        if (key == GLFW_KEY_W && (action == GLFW_PRESS || action == GLFW_REPEAT))
        {
            pgMainSystem->pSceneSystem->pLightManager->MoveSelectedLight(2, 1);
            return;
        }
        // --------------------------------------------

        // Light attenuation
        // --------------------------------------------
        // Linear attenuation 
        if (key == GLFW_KEY_Z && (action == GLFW_PRESS || action == GLFW_REPEAT))
        {
            pgMainSystem->pSceneSystem->pLightManager->ChangeAttenuationInSelectedLight(1, -1);
        }
        if (key == GLFW_KEY_X && (action == GLFW_PRESS || action == GLFW_REPEAT))
        {
            pgMainSystem->pSceneSystem->pLightManager->ChangeAttenuationInSelectedLight(1, 1);
        }

        // Quadratic attenuation 
        if (key == GLFW_KEY_C && (action == GLFW_PRESS || action == GLFW_REPEAT))
        {
            pgMainSystem->pSceneSystem->pLightManager->ChangeAttenuationInSelectedLight(2, -1);
        }
        if (key == GLFW_KEY_V && (action == GLFW_PRESS || action == GLFW_REPEAT))
        {
            pgMainSystem->pSceneSystem->pLightManager->ChangeAttenuationInSelectedLight(2, 1);
        }
        // --------------------------------------------

        // Light directions
        // --------------------------------------------
        if (key == GLFW_KEY_F && (action == GLFW_PRESS || action == GLFW_REPEAT))
        {
            pgMainSystem->pSceneSystem->pLightManager->ChangeDirectionSelectedLight(0, -1);
            return;
        }
        if (key == GLFW_KEY_H && (action == GLFW_PRESS || action == GLFW_REPEAT))
        {
            pgMainSystem->pSceneSystem->pLightManager->ChangeDirectionSelectedLight(0, 1);
            return;
        }

        if (key == GLFW_KEY_R && (action == GLFW_PRESS || action == GLFW_REPEAT))
        {
            pgMainSystem->pSceneSystem->pLightManager->ChangeDirectionSelectedLight(1, -1);
            return;
        }
        if (key == GLFW_KEY_Y && (action == GLFW_PRESS || action == GLFW_REPEAT))
        {
            pgMainSystem->pSceneSystem->pLightManager->ChangeDirectionSelectedLight(1, 1);
            return;
        }

        if (key == GLFW_KEY_G && (action == GLFW_PRESS || action == GLFW_REPEAT))
        {
            pgMainSystem->pSceneSystem->pLightManager->ChangeDirectionSelectedLight(2, -1);
            return;
        }
        if (key == GLFW_KEY_T && (action == GLFW_PRESS || action == GLFW_REPEAT))
        {
            pgMainSystem->pSceneSystem->pLightManager->ChangeDirectionSelectedLight(2, 1);
            return;
        }
        // --------------------------------------------

        // Light params
        // --------------------------------------------
        if (key == GLFW_KEY_J && (action == GLFW_PRESS || action == GLFW_REPEAT))
        {
            pgMainSystem->pSceneSystem->pLightManager->ChangeParamsSelectedLight(0, -1);
            return;
        }
        if (key == GLFW_KEY_L && (action == GLFW_PRESS || action == GLFW_REPEAT))
        {
            pgMainSystem->pSceneSystem->pLightManager->ChangeParamsSelectedLight(0, 1);
            return;
        }

        if (key == GLFW_KEY_U && (action == GLFW_PRESS || action == GLFW_REPEAT))
        {
            pgMainSystem->pSceneSystem->pLightManager->ChangeParamsSelectedLight(1, -1);
            return;
        }
        if (key == GLFW_KEY_O && (action == GLFW_PRESS || action == GLFW_REPEAT))
        {
            pgMainSystem->pSceneSystem->pLightManager->ChangeParamsSelectedLight(1, 1);
            return;
        }

        if (key == GLFW_KEY_K && (action == GLFW_PRESS || action == GLFW_REPEAT))
        {
            pgMainSystem->pSceneSystem->pLightManager->ChangeParamsSelectedLight(2, -1);
            return;
        }
        if (key == GLFW_KEY_I && (action == GLFW_PRESS || action == GLFW_REPEAT))
        {
            pgMainSystem->pSceneSystem->pLightManager->ChangeParamsSelectedLight(2, 1);
            return;
        }
        // --------------------------------------------

        // Light status
        // --------------------------------------------
        if (key == GLFW_KEY_B && (action == GLFW_PRESS || action == GLFW_REPEAT))
        {
            pgMainSystem->pSceneSystem->pLightManager->ToggleSelectedLight();
            return;
        }
        // --------------------------------------------
    }
    // --------------------------------------------

    // SHIFT key down + action key
    // Mesh controls
    // --------------------------------------------
    if ((mods & GLFW_MOD_SHIFT) == GLFW_MOD_SHIFT)
    {
        // Mesh selection
        // --------------------------------------------
        if (key == GLFW_KEY_PAGE_UP && (action == GLFW_PRESS || action == GLFW_REPEAT))
        {
            pgMainSystem->pSceneSystem->pMeshManager->ChangeSelectedMesh(1);
            return;
        }
        if (key == GLFW_KEY_PAGE_DOWN && (action == GLFW_PRESS || action == GLFW_REPEAT))
        {
            pgMainSystem->pSceneSystem->pMeshManager->ChangeSelectedMesh(-1);
            return;
        }
        // --------------------------------------------

        // Mesh position
        // --------------------------------------------
        if (key == GLFW_KEY_A && (action == GLFW_PRESS || action == GLFW_REPEAT))
        {
            pgMainSystem->pSceneSystem->pMeshManager->MoveSelectedMesh(0, -1);
            return;
        }
        if (key == GLFW_KEY_D && (action == GLFW_PRESS || action == GLFW_REPEAT))
        {
            pgMainSystem->pSceneSystem->pMeshManager->MoveSelectedMesh(0, 1);
            return;
        }

        if (key == GLFW_KEY_Q && (action == GLFW_PRESS || action == GLFW_REPEAT))
        {
            pgMainSystem->pSceneSystem->pMeshManager->MoveSelectedMesh(1, -1);
            return;
        }
        if (key == GLFW_KEY_E && (action == GLFW_PRESS || action == GLFW_REPEAT))
        {
            pgMainSystem->pSceneSystem->pMeshManager->MoveSelectedMesh(1, 1);
            return;
        }

        if (key == GLFW_KEY_S && (action == GLFW_PRESS || action == GLFW_REPEAT))
        {
            pgMainSystem->pSceneSystem->pMeshManager->MoveSelectedMesh(2, -1);
            return;
        }
        if (key == GLFW_KEY_W && (action == GLFW_PRESS || action == GLFW_REPEAT))
        {
            pgMainSystem->pSceneSystem->pMeshManager->MoveSelectedMesh(2, 1);
            return;
        }
        // --------------------------------------------


        // Mesh rotation
        // --------------------------------------------
        if (key == GLFW_KEY_F && (action == GLFW_PRESS || action == GLFW_REPEAT))
        {
            pgMainSystem->pSceneSystem->pMeshManager->RotateSelectedMesh(0, -1);
            return;
        }
        if (key == GLFW_KEY_H && (action == GLFW_PRESS || action == GLFW_REPEAT))
        {
            pgMainSystem->pSceneSystem->pMeshManager->RotateSelectedMesh(0, 1);
            return;
        }

        if (key == GLFW_KEY_R && (action == GLFW_PRESS || action == GLFW_REPEAT))
        {
            pgMainSystem->pSceneSystem->pMeshManager->RotateSelectedMesh(1, -1);
            return;
        }
        if (key == GLFW_KEY_Y && (action == GLFW_PRESS || action == GLFW_REPEAT))
        {
            pgMainSystem->pSceneSystem->pMeshManager->RotateSelectedMesh(1, 1);
            return;
        }

        if (key == GLFW_KEY_G && (action == GLFW_PRESS || action == GLFW_REPEAT))
        {
            pgMainSystem->pSceneSystem->pMeshManager->RotateSelectedMesh(2, -1);
            return;
        }
        if (key == GLFW_KEY_T && (action == GLFW_PRESS || action == GLFW_REPEAT))
        {
            pgMainSystem->pSceneSystem->pMeshManager->RotateSelectedMesh(2, 1);
            return;
        }
        // --------------------------------------------


        // Mesh scaling
        // --------------------------------------------
        if (key == GLFW_KEY_Z && (action == GLFW_PRESS || action == GLFW_REPEAT))
        {
            pgMainSystem->pSceneSystem->pMeshManager->ChangeScaleSelectedMesh(-1);
            return;
        }
        if (key == GLFW_KEY_X && (action == GLFW_PRESS || action == GLFW_REPEAT))
        {
            pgMainSystem->pSceneSystem->pMeshManager->ChangeScaleSelectedMesh(1);
            return;
        }
        // --------------------------------------------
    }
    // --------------------------------------------

    // Nothing down
    // Camera controls
    // --------------------------------------------
    if (mods == 0)
    {
        // Camera position
        // --------------------------------------------
        if (key == GLFW_KEY_A && (action == GLFW_PRESS || action == GLFW_REPEAT))
        {
            pgMainSystem->pRenderingSystem->MoveCamera(0, -1);
            return;
        }
        if (key == GLFW_KEY_D && (action == GLFW_PRESS || action == GLFW_REPEAT))
        {
            pgMainSystem->pRenderingSystem->MoveCamera(0, 1);
            return;
        }

        if (key == GLFW_KEY_Q && (action == GLFW_PRESS || action == GLFW_REPEAT))
        {
            pgMainSystem->pRenderingSystem->MoveCamera(1, -1);
            return;
        }
        if (key == GLFW_KEY_E && (action == GLFW_PRESS || action == GLFW_REPEAT))
        {
            pgMainSystem->pRenderingSystem->MoveCamera(1, 1);
            return;
        }

        if (key == GLFW_KEY_S && (action == GLFW_PRESS || action == GLFW_REPEAT))
        {
            pgMainSystem->pRenderingSystem->MoveCamera(2, -1);
            return;
        }
        if (key == GLFW_KEY_W && (action == GLFW_PRESS || action == GLFW_REPEAT))
        {
            pgMainSystem->pRenderingSystem->MoveCamera(2, 1);
            return;
        }
        // --------------------------------------------

        // Camera target
        // --------------------------------------------
        if (key == GLFW_KEY_Z && (action == GLFW_PRESS || action == GLFW_REPEAT))
        {
            pgMainSystem->pRenderingSystem->MoveCameraTarget(0, -1);
            return;
        }
        if (key == GLFW_KEY_X && (action == GLFW_PRESS || action == GLFW_REPEAT))
        {
            pgMainSystem->pRenderingSystem->MoveCameraTarget(0, 1);
            return;
        }

        if (key == GLFW_KEY_C && (action == GLFW_PRESS || action == GLFW_REPEAT))
        {
            pgMainSystem->pRenderingSystem->MoveCameraTarget(1, -1);
            return;
        }
        if (key == GLFW_KEY_V && (action == GLFW_PRESS || action == GLFW_REPEAT))
        {
            pgMainSystem->pRenderingSystem->MoveCameraTarget(1, 1);
            return;
        }
        // --------------------------------------------

        return;
    }
    // --------------------------------------------
}

int main(int argc, char** argv) {
    char* sceneName;
    if (argc < 2)
    {
        sceneName = (char*)"scene01";
    }
    else
    {
        sceneName = argv[1];
    }

    pgMainSystem->Initialize(sceneName, ErrorCallback, KeyCallback);

    pgMainSystem->MainLoop();

    return 0;
}


