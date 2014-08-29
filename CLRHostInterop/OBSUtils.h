#pragma once

#include <msclr\marshal_cppstd.h>

using namespace msclr::interop;

namespace CLROBS
{
    std::wstring ToWString(System::String^ string);
};