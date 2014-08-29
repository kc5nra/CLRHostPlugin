#pragma once

#ifdef CLR_DLL
#define CLR_API __declspec(dllexport)
#else
#define CLR_API __declspec(dllimport)
#endif

#define CLR_GET_METHOD(type, methodName, method) \
    getMethod(type, methodName, method, __FUNCSIG__)

namespace mscorlib
{
    struct _Type;
    struct _MethodInfo;
}

bool getMethod(mscorlib::_Type * type, char *methodName, 
    mscorlib::_MethodInfo **method, char *errorLocation);