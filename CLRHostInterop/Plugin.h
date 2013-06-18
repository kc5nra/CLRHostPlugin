#pragma once

#include "API.h"

using namespace System;
using namespace CLROBS;

namespace CLROBS {
    public interface class Plugin
    {
        property API^ Api {
            virtual API^ get() abstract;
            virtual void set(API^ api) abstract;
        }

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