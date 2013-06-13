#pragma once

using namespace System;

namespace OBS {
    public interface class Plugin
    {
        virtual bool LoadPlugin();
        virtual void UnloadPlugin();
        virtual void OnStartStream();
        virtual void OnStopStream();
        virtual String^ GetPluginName();
        virtual String^ GetPluginDescription();
    };
};