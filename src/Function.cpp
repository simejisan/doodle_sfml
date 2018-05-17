#include "Function.h"

namespace Engine
{
    std::string int_to_string(int integer)
    {
        char character[10];
        sprintf(character, "%d", integer);
        return std::string(character);
    }

    std::string float_to_string(float real_number)
    {
        char character[10];
        sprintf(character, "%.2f", real_number);
        return std::string(character);
    }

    std::wstring int_to_wstring(int integer)
    {
        char character[10];
        sprintf(character, "%d", integer);
        std::string temp_string = std::string(character);
        std::wstring temp_wstring(temp_string.begin(), temp_string.end());
        return temp_wstring;
    }

    std::wstring float_to_wstring(float real_number)
    {
        char character[10];
        sprintf(character, "%.2f", real_number);
        std::string temp_string = std::string(character);
        std::wstring temp_wstring(temp_string.begin(), temp_string.end());
        return temp_wstring;
    }
}
