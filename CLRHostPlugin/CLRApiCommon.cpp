#include "stdafx.h"

#include "CLRApiCommon.h"
#include "mscorelib.h"

bool getMethod(
    mscorlib::_Type * objectType,
    char *methodName,
    mscorlib::_MethodInfo **method,
    char *errorLocation)
{
    HRESULT hr;
    bstr_t bstrMethodName(methodName);

    hr = objectType->GetMethod_6(bstrMethodName, method);
    if (FAILED(hr) || !method) {
        Log(L"%s: failed to get %s method definition: 0x%08lx",
            errorLocation, methodName, hr);
        return false;
    }

    return true;
}