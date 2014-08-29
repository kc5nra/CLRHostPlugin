#pragma once

#include "SettingsPane.h"

using namespace System;
using namespace System::Windows;
using namespace System::Windows::Interop;

#define _WM_GETDLGCODE          0x0087
#define _DLGC_WANTCHARS         0x0080
#define _DLGC_WANTALLKEYS       0x0004

#define _WS_EX_CONTROLPARENT    0x00010000L

#define _WS_SYSMENU             0x00080000L
#define _DS_CONTROL             0x00000400L
#define _WS_CHILD               0x40000000L

namespace CLROBS
{
    public ref class AbstractWPFSettingsPane abstract : public SettingsPane
    {
    private:
        HwndSource^ hwndSource;
        System::String ^category;

    public:
        AbstractWPFSettingsPane();

    public:
        virtual long long CreatePane(long long parentHwnd) sealed;
        virtual void DestroyPane() sealed;

        virtual void ApplySettings() = 0;
        virtual void CancelSettings() = 0;
        virtual bool HasDefaults() = 0;
        virtual void SetDefaults() = 0;

        property System::String^ Category
        {
        public:
            virtual System::String^ get();
        protected:
            virtual void set(System::String^ category) sealed;
        }

    public:
        virtual UIElement^ CreateUIElement() abstract;
    };
};