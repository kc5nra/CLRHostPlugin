#include "OBSApi.h"
#include "CLRHostApi.h"
#include "CLRHostPlugin.h"
#include "CLRImageSourceFactory.h"

CLRHostApi::~CLRHostApi()
{
    for(auto i = imageSourceFactories.begin(); i != imageSourceFactories.end(); i++) {
        auto entry = *i;
        if (entry.second) {
            delete entry.second;
        }
    }
    imageSourceFactories.clear();
}

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
    if (imageSourceFactory->Attach(clrObjectRef, clrHost->GetImageSourceFactoryType())) {
        std::wstring sourceName = imageSourceFactory->GetSourceClassName(); 
        if (imageSourceFactories[sourceName] != nullptr) {
            delete imageSourceFactories[sourceName];
        }
        imageSourceFactories[sourceName] = imageSourceFactory;
    } else {
        Log(TEXT("Error attaching unmanaged CLRImageSourceFactory to managed instance"));
        delete imageSourceFactory;
    }


}