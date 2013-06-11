#pragma once

#include <string>

#ifdef CLR_HOST_API
#define CLRHOST_API __declspec(dllexport)
#else
#define CLR_HOST_API __declspec(dllimport)
#endif

class CLR_HOST_API CLRHostApi {
public:
    void OBSLog(std::wstring &logMessage);
    void Hello();
};