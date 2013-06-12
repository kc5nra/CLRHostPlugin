#pragma once

using namespace System;

namespace OBSAPI {
    public interface class SettingsPane
    {
        virtual String^ GetCategory() = 0;
        virtual IntPtr CreatePane(IntPtr parentHwnd) = 0;
        virtual void DestroyPane() = 0;
        virtual void ApplySettings() = 0;
        virtual void CancelSettings() = 0;
        virtual bool HasDefaults() = 0;
        virtual void SetDefaults() = 0;
    };
};