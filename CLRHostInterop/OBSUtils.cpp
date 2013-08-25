#include "OBSUtils.h"

std::wstring CLROBS::ToWString(System::String^ string)
{
    return marshal_as<std::wstring, System::String^>(string);
}