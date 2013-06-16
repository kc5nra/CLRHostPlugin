#include "OBSApi.h"
#include "CLRHostApi.h"
#include "CLRHostPlugin.h"
#include "CLRImageSource.h"
#include "CLRImageSourceFactory.h"
#include "ImageSourceBridge.h"

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
ImageSource* STDCALL CreateImageSource(XElement *element)
{
    if (element == nullptr) 
    {
        return nullptr;
    }
    
    if (!element->GetParent() || !element->GetParent()->HasItem(TEXT("class"))) {
        Log(TEXT("Bad parent item, null or doesn't have class name"));
        return nullptr;
    }

    std::wstring className = element->GetParent()->GetString(TEXT("class"));

    CLRHostApi *clrHostApi = CLRHostPlugin::instance->GetCLRApi();
    auto imageSourceFactories = clrHostApi->GetImageSourceFactories();
    if (imageSourceFactories[className]) {
        CLRImageSource *imageSource = imageSourceFactories[className]->Create();
        return new ImageSourceBridge(imageSource);
    } else {
        Log(TEXT("Couldn't find matching ImageSourceFactory for class %s"), className.c_str());
        return nullptr;
    }
}
void ConfigureImageSource(XElement *element, bool isInitializing)
{
    if (element == nullptr) {
        Log(TEXT("Configuration element is null, skipping"));
        return;
    }

    if (!element->HasItem(TEXT("class"))) {
        Log(TEXT("Configuration element doesn't have class name, skipping"));
        return;
    }

    XElement *data = element->GetElement(TEXT("data"));
    if(!data) {
        data = element->CreateElement(TEXT("data"));
    }

    std::wstring className = element->GetString(TEXT("class"));

    CLRHostApi *clrHostApi = CLRHostPlugin::instance->GetCLRApi();
    auto imageSourceFactories = clrHostApi->GetImageSourceFactories();
    if (imageSourceFactories[className]) {
        imageSourceFactories[className]->ShowConfiguration();
    } else {
        Log(TEXT("Couldn't find matching ImageSourceFactory for class %s"), className.c_str());
        return;
    }
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
        API->RegisterImageSourceClass(
            sourceName.c_str(),
            imageSourceFactory->GetDisplayName().c_str(),
            (OBSCREATEPROC)CreateImageSource,
            (OBSCONFIGPROC)ConfigureImageSource);

    } else {
        Log(TEXT("Error attaching unmanaged CLRImageSourceFactory to managed instance"));
        delete imageSourceFactory;
    }


}