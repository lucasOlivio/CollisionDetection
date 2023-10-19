#include "Common/Utils.h"

namespace myfiles {
    // Get string after last "." in file name
    std::string GetFileExtension(std::string fileName)
    {
        size_t dotPos = fileName.find_last_of(".");
        if (dotPos != std::string::npos)
        {
            return fileName.substr(dotPos + 1);
        }
        return ""; // Empty string if no extension found
    }

    // Go to word after next appearence of string to search
    void JumpToSearch(std::istream& fileStream, std::string strToSearch)
    {
        std::string temp;
        while (fileStream >> temp)
        {
            if (temp == strToSearch)
            {
                break;
            }
        };
    }
}

namespace mymath {
    int Sign(int val)
    {
        return (0 < val) - (val < 0);
    }

    float GetRandFloat(float a, float b)
    {
        float random = ((float)rand()) / (float)RAND_MAX;
        float diff = b - a;
        float r = random * diff;
        return a + r;
    }
}