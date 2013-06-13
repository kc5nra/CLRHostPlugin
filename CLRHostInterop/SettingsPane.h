#pragma once

using namespace System;

namespace OBS {
    public interface class SettingsPane
    {
        virtual String^ GetCategory();
        virtual IntPtr CreatePane(IntPtr parentHwnd);
        virtual void DestroyPane();
        virtual void ApplySettings();
        virtual void CancelSettings();
        virtual bool HasDefaults();
        virtual void SetDefaults();
    };
};