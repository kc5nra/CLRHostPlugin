#include "API.h"
#include "CLRHostApi.h"

using namespace System::Runtime::InteropServices;

void API::AddSettingsPane(SettingsPane^ settingsPane)
{
    IntPtr unkRef = Marshal::GetIUnknownForObject(settingsPane);
    CLRObjectRef objectRef(unkRef.ToPointer(), nullptr);
    clrHostApi->AddSettingsPane(objectRef);
}

void API::AddImageSourceFactory(ImageSourceFactory^ imageSourceFactory)
{
    IntPtr unkRef = Marshal::GetIUnknownForObject(imageSourceFactory);
    CLRObjectRef objectRef(unkRef.ToPointer(), nullptr);
    clrHostApi->AddImageSourceFactory(objectRef);
}

IntPtr API::GetMainWindowHandle()
{
    return IntPtr(clrHostApi->GetMainWindowHandle());
}