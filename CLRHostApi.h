#pragma once

#include <string>
#include "CLRApiCommon.h"
#include "CLRObjectRef.h"

class CLR_API CLRHostApi {
public:
    void CLRLog(std::wstring &logMessage);
    void AddSettingsPane(CLRObjectRef &clrObjectReference);
    void AddImageSourceFactory(CLRObjectRef &clrObjectReference);
};