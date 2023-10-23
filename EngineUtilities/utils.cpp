#include "common/utils.h"
#include <sstream>

void __CheckEngineError(const char* msg, const char* file, int line)
{
    printf("Egine error file '%s' line '%d': %s\n", file, line, msg);
    return;
}

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

template <typename T>
std::string myutils::ArrayToString(char delimiter, const std::vector<T>& arr) {
    std::ostringstream oss;

    if (arr.empty()) {
        return "";
    }

    oss << arr[0];
    for (size_t i = 1; i < arr.size(); ++i) {
        oss << delimiter << arr[i];
    }

    return oss.str();
}

std::string myutils::BoolToString(bool input) {
    return input ? "1" : "0";
}

int myutils::Sign(int val)
{
    return (0 < val) - (val < 0);
}

float myutils::GetRandFloat(float a, float b)
{
    float random = ((float)rand()) / (float)RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

glm::vec4 myutils::StringToVec4(const std::string& glmstr) 
{
    glm::vec4 result;

    std::string values = glmstr.substr(glmstr.find('(') + 1, glmstr.find(')') - glmstr.find('(') - 1);
    std::stringstream ss(values);
    ss >> result.x >> result.y >> result.z >> result.w;

    return result;
}

glm::vec3 myutils::StringToVec3(const std::string& glmstr) 
{
    glm::vec3 result;

    std::string values = glmstr.substr(glmstr.find('(') + 1, glmstr.find(')') - glmstr.find('(') - 1);
    std::stringstream ss(values);
    ss >> result.x >> result.y >> result.z;

    return result;
}