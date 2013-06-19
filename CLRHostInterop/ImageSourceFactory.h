#pragma once

#include "ImageSource.h"

using namespace CLROBS;
using namespace System;

namespace CLROBS {
    public interface class ImageSourceFactory
    {
        virtual ImageSource^ Create(XElement^ data) = 0;
        virtual bool ShowConfiguration(XElement^ data) = 0;

        property String^ DisplayName {
            virtual String^ get();
        }
        property String^ ClassName {
            virtual String^ get();
        }      
    };
};