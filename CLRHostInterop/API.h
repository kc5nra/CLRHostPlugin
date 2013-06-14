#pragma once

#include "ImageSource.h"
#include "SettingsPane.h"
#include "AbstractWPFSettingsPane.h"
#include "ImageSourceFactory.h"

using namespace OBS;

class CLRHostApi;

namespace OBS {
    public ref class API
    {
    private:
        CLRHostApi *clrHostApi;

    public:
        API(long clrHostApiPointer)
        {
            this->clrHostApi = reinterpret_cast<CLRHostApi *>(clrHostApiPointer);
        }
    
    public:
        void AddSettingsPane(SettingsPane^ settingsPane);
        void AddImageSourceFactory(ImageSourceFactory^ imageSourceFactory);
    };
};