#include "OBSApi.h"
#include "CLRHostApi.h"
#include "CLRHostPlugin.h"
#include "CLRImageSource.h"
#include "CLRImageSourceFactory.h"
#include "CLRSettingsPane.h"
#include "ImageSourceBridge.h"
#include "SettingsPaneBridge.h"

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

void CLRHostApi::AddSettingsPane(CLRObjectRef &clrObjectRef)
{
    CLRHost *clrHost = CLRHostPlugin::instance->GetCLRHost();

    CLRSettingsPane *clrSettingsPane = new CLRSettingsPane();
    if (clrSettingsPane->Attach(clrObjectRef, clrHost->GetSettingsPaneType())) {
        OBSAddSettingsPane(new SettingsPaneBridge(clrSettingsPane));
    }
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
    CLRHost *clrHost = CLRHostPlugin::instance->GetCLRHost();

    auto imageSourceFactories = clrHostApi->GetImageSourceFactories();
    if (imageSourceFactories[className]) {
        CLRXElement *clrElement = CLRXElement::Create(clrHost->GetXElementType(), element);
        if (!clrElement) {
            Log(TEXT("CLRHostApi::CreateImageSource() unable to create managed CLRXElement wrapper"));
            return nullptr;
        }
        CLRImageSource *imageSource = imageSourceFactories[className]->Create(clrElement);
        delete clrElement;
        if (imageSource) {
            return new ImageSourceBridge(imageSource);
        } else {
            Log(TEXT("ImageSourceFactory returned null CLRImageSource for class %s"), className.c_str());
            return nullptr;
        }
    } else {
        Log(TEXT("Couldn't find matching ImageSourceFactory for class %s"), className.c_str());
        return nullptr;
    }
}

bool STDCALL ConfigureImageSource(XElement *element, bool isInitializing)
{
    if (element == nullptr) {
        Log(TEXT("Configuration element is null, skipping"));
        return false;
    }

    if (!element->HasItem(TEXT("class"))) {
        Log(TEXT("Configuration element doesn't have class name, skipping"));
        return false;
    }

    XElement *data = element->GetElement(TEXT("data"));
    if(!data) {
        data = element->CreateElement(TEXT("data"));
    }

    std::wstring className = element->GetString(TEXT("class"));

    CLRHostApi *clrHostApi = CLRHostPlugin::instance->GetCLRApi();
    CLRHost *clrHost = CLRHostPlugin::instance->GetCLRHost();

    auto imageSourceFactories = clrHostApi->GetImageSourceFactories();
    if (imageSourceFactories[className]) {
        CLRXElement *clrElement = CLRXElement::Create(clrHost->GetXElementType(), data);
        if (!clrElement) {
            Log(TEXT("CLRHostApi::CreateImageSource() unable to create managed CLRXElement wrapper"));
            return false;
        }
        bool returnValue = imageSourceFactories[className]->ShowConfiguration(clrElement);
        delete clrElement;
        return returnValue;
    } else {
        Log(TEXT("Couldn't find matching ImageSourceFactory for class %s"), className.c_str());
        return false;
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