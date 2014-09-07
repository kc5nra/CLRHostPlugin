#pragma once

#include <string>
#include <map>
#include <vector>

#include "CLRApiCommon.h"
#include "CLRObjectRef.h"
#include "SettingsPaneBridge.h"
#include "CLRImageSourceFactory.h"

class CLRHostApi
{
private:
    std::map<std::wstring, CLRImageSourceFactory*> imageSourceFactories;
    std::vector <SettingsPaneBridge *> settingsPanes;
public:
    ~CLRHostApi();
public:
    CLR_API void AddSettingsPane(CLRObjectRef &clrObjectReference);
    CLR_API void AddImageSourceFactory(CLRObjectRef &clrObjectReference);
    CLR_API void RemoveSettingsPane(CLRObjectRef &clrObjectReference);
    CLR_API void RemoveImageSourceFactory(CLRObjectRef &clrObjectReference);

public:
    std::map<std::wstring, CLRImageSourceFactory*> &GetImageSourceFactories()
    {
        return imageSourceFactories;
    }
};