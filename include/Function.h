#ifndef _Function_HPP_
#define _Functions_HPP_

#include <string>
#include <fstream>

namespace Engine
{
    //   Chuyển đổi từ kiểu int sang string
    std::string int_to_string(int integer);

    //   Chuyển đổi từ kiểu float sang string với 2 chữ số thập phân
    std::string float_to_string(float real_number);

    //   Chuyển đổi từ kiểu int sang wstring
    std::wstring int_to_wstring(int integer);

    //   Chuyển đổi từ kiểu float sang wstring với 2 chữ số thập phân
    std::wstring float_to_wstring(float real_number);
}

#endif // _CommonFunctions_HPP_
