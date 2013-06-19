#pragma once

#include "API.h"

using namespace System;
using namespace CLROBS;

namespace CLROBS {
    public interface class Plugin
    {

        virtual bool LoadPlugin() = 0;
        virtual void UnloadPlugin() = 0;
        virtual void OnStartStream() = 0;
        virtual void OnStopStream() = 0;

        property String^ Name {
            virtual String^ get();
        }
        property String^ Description {
            virtual String^ get();
        }
    };
};