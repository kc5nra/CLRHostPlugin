#include "OBSUtils.h"

namespace CLROBS
{
    std::wstring ToWString(System::String^ string)
    {
        return marshal_as<std::wstring, System::String^>(string);
    }
}