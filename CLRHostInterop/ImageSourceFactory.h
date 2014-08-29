#pragma once

#include "ImageSource.h"

using namespace System;

namespace CLROBS
{
    public interface class ImageSourceFactory
    {
        virtual ImageSource^ Create(XElement^ data) = 0;
        virtual bool ShowConfiguration(XElement^ data) = 0;

        property System::String^ DisplayName {
            virtual System::String^ get();
        }
        property System::String^ ClassName {
            virtual System::String^ get();
        }
    };
};