#include "OBSApi.h"
#include "API.h"
#include "CLRHostApi.h"

using namespace System::Runtime::InteropServices;

void API::AddSettingsPane(CLROBS::SettingsPane^ settingsPane)
{
    System::IntPtr unkRef = Marshal::GetIUnknownForObject(settingsPane);
    CLRObjectRef objectRef(unkRef.ToPointer(), nullptr);
    clrHostApi->AddSettingsPane(objectRef);
}

void API::AddImageSourceFactory(CLROBS::ImageSourceFactory^ imageSourceFactory)
{
    System::IntPtr unkRef = Marshal::GetIUnknownForObject(imageSourceFactory);
    CLRObjectRef objectRef(unkRef.ToPointer(), nullptr);
    clrHostApi->AddImageSourceFactory(objectRef);
}

System::IntPtr API::GetMainWindowHandle()
{
    return System::IntPtr(::API->GetMainWindow());
}