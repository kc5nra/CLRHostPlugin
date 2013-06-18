#pragma once

#include "ImageSource.h"
#include "SettingsPane.h"
#include "AbstractWPFSettingsPane.h"
#include "ImageSourceFactory.h"

using namespace CLROBS;

class CLRHostApi;

namespace CLROBS {

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