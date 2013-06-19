#pragma once

#include "SettingsPane.h"

using namespace CLROBS;
using namespace System;
using namespace System::Windows;
using namespace System::Windows::Interop;

#define WS_CHILD    0x40000000L
#define WS_VISIBLE  0x10000000L

namespace CLROBS 
{
    public ref class AbstractWPFSettingsPane abstract: public SettingsPane {
    public:
        virtual void CreatePane(IntPtr parentHwnd) sealed;
        virtual void DestroyPane() = 0;
        virtual System::String^ GetCategory() = 0;
        virtual void ApplySettings() = 0;
        virtual void CancelSettings() = 0;
        virtual bool HasDefaults() = 0;
        virtual void SetDefaults() = 0;
    public:
        virtual UIElement^ CreateUIElement() abstract;
    };
};