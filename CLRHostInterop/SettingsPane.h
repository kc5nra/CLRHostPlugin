#pragma once

using namespace System;

namespace CLROBS
{
    public interface class SettingsPane
    {
        virtual long long CreatePane(long long parentHwnd) = 0;
        virtual void DestroyPane() = 0;
        virtual void ApplySettings() = 0;
        virtual void CancelSettings() = 0;
        virtual bool HasDefaults() = 0;
        virtual void SetDefaults() = 0;

        property System::String^ Category {
            virtual System::String^ get();
        }
    };
};