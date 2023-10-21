#include "utils.h"
#include <sstream>

std::string myutils::GetFileExtension(const std::string& fileName)
{
    size_t dotPos = fileName.find_last_of(".");
    if (dotPos != std::string::npos)
    {
        return fileName.substr(dotPos + 1);
    }
    return fileName; // Full string if no extension found
}

void myutils::SplitString(const std::string& stringIn,
    char delimiter,
    std::vector<std::string> vecOut)
{
    std::istringstream iss(stringIn.c_str());
    std::string token;

    vecOut.clear();
    while (std::getline(iss, token, delimiter)) {
        vecOut.push_back(token);
    }
}
