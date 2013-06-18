#pragma once

using namespace System;

namespace CLROBS {
    public interface class SettingsPane
    {
        virtual void CreatePane(IntPtr parentHwnd) = 0;
        virtual void DestroyPane() = 0;
        virtual String^ GetCategory() = 0;
        virtual void ApplySettings() = 0;
        virtual void CancelSettings() = 0;
        virtual bool HasDefaults() = 0;
        virtual void SetDefaults() = 0;
    };
};