#pragma once

#include <string>
#include <vector>

namespace myutils
{
    // Get string after last "." in file name
    std::string GetFileExtension(const std::string& fileName);

    // Split string based on delimiter
    void SplitString(const std::string& stringIn,
        char delimiter,
        std::vector<std::string> vecOut);
}