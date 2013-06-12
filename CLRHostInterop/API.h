#pragma once

#include "CLRHostApi.h"

#include "ImageSource.h"
#include "SettingsPane.h"
#include "ImageSourceFactory.h"

using namespace OBSAPI;

public ref class API
{
private:
    CLRHostApi *clrHostApi;

public:
    API(CLRHostApi *clrHostApi)
    {
        this->clrHostApi = clrHostApi;
    }
    
public:
    void AddSettingsPane(SettingsPane^ settingsPane);
    void AddImageSourceFactory(ImageSourceFactory^ imageSourceFactory);
};
