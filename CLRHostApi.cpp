#include "OBSApi.h"
#include "CLRHostApi.h"
#include "CLRHostPlugin.h"
#include "CLRImageSourceFactory.h"

void CLRHostApi::CLRLog(std::wstring &logMessage)
{
    Log(TEXT("CLRApi>> %s"), logMessage.c_str());
}

void CLRHostApi::AddSettingsPane(CLRObjectRef &clrObjectReference)
{

}

void CLRHostApi::AddImageSourceFactory(CLRObjectRef &clrObjectRef)
{
    CLRHost *clrHost = CLRHostPlugin::instance->GetCLRHost();
    
    CLRImageSourceFactory *imageSourceFactory = new CLRImageSourceFactory();
    imageSourceFactory->Attach(clrObjectRef, clrHost->GetImageSourceFactoryType());
    
    std::wstring str = imageSourceFactory->GetDisplayName();
}