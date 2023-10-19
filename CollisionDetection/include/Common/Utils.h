#pragma once
#include <iostream>
#include <string>

namespace myfiles {
    // Get string after last "." in file name
    std::string GetFileExtension(std::string fileName);

    // Go to word after next appearence of string to search
    void JumpToSearch(std::istream& fileStream, std::string strToSearch);
}

namespace mymath {
    // https://stackoverflow.com/questions/1903954/is-there-a-standard-sign-function-signum-sgn-in-c-c
    // Returns the sign of the given number
    int Sign(int val);

    // https://stackoverflow.com/questions/5289613/generate-random-float-between-two-floats
    // Returns a random float between (including) <a> and <b>
    float GetRandFloat(float a, float b);
}