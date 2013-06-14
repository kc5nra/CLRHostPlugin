#pragma once

#include "ImageSource.h"

using namespace OBS;
using namespace System;

namespace OBS {
    public interface class ImageSourceFactory
    {
        virtual ImageSource^ Create() = 0;
        virtual void ShowConfiguration() = 0;

        property String^ DisplayName {
            virtual String^ get();
        }
        property String^ ClassName {
            virtual String^ get();
        }      
    };
};