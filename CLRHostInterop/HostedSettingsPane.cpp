#include "HostedSettingsPane.h"

void HostedSettingsPane::CreatePane(IntPtr parentHwnd)
{
    UIElement ^uiElement = CreateUIElement();
   
    HwndSource^ source = gcnew HwndSource(
        0,                          // class style
        WS_VISIBLE | WS_CHILD,      // style
        0,                          // exstyle
        0, 0, 427, 336,        
        "",
        parentHwnd                  // parent window 
    );
}
