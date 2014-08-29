#pragma once

#include "API.h"

using namespace System;

namespace CLROBS
{
    public interface class Plugin
    {
        virtual bool LoadPlugin() = 0;
        virtual void UnloadPlugin() = 0;
        virtual void OnStartStream() = 0;
        virtual void OnStopStream() = 0;

        property System::String^ Name {
            virtual System::String^ get();
        }
        property System::String^ Description {
            virtual System::String^ get();
        }
    };
};