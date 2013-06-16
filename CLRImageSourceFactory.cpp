#include "CLRImageSourceFactory.h"

#include <metahost.h> 
#include <string>

#pragma comment(lib, "mscoree.lib") 
#import "mscorlib.tlb" raw_interfaces_only high_property_prefixes("_get","_put","_putref") rename("ReportEvent", "InteropServices_ReportEvent") 
using namespace mscorlib; 

void __cdecl Log(const TCHAR *format, ...);
void __cdecl CrashError(const TCHAR *format, ...);

#ifndef assert
#ifdef _DEBUG
#define assert(check) if(!(check)) CrashError(TEXT("Assertion Failiure: (") TEXT(#check) TEXT(") failed\r\nFile: %s, line %d"), TEXT(__FILE__), __LINE__);
#else
#define assert(check)
#endif
#endif

bool CLRImageSourceFactory::Attach(CLRObjectRef &clrObjectRef, mscorlib::_Type *objectType)
{
    CLRObject::Attach(clrObjectRef, objectType);

    bstr_t createMethodName("Create");
    bstr_t getDisplayNameMethodName("get_DisplayName");
    bstr_t getSourceClassNameMethodName("get_ClassName");
    bstr_t showConfigurationMethodName("ShowConfiguration");


    HRESULT hr;

    hr = objectType->GetMethod_6(createMethodName, &createMethod);
    if (FAILED(hr)) {
        Log(TEXT("Failed to get Create method definition of ImageSourceFactory class: 0x%08lx"), hr); 
        goto errorCleanup;
    }

    hr = objectType->GetMethod_6(getDisplayNameMethodName, &getDisplayNameMethod);
    if (FAILED(hr)) {
        Log(TEXT("Failed to get GetDisplayName method definition of ImageSourceFactory class: 0x%08lx"), hr); 
        goto errorCleanup;
    }

    hr = objectType->GetMethod_6(getSourceClassNameMethodName, &getSourceClassNameMethod);
    if (FAILED(hr)) {
        Log(TEXT("Failed to get GetSourceClassName method definition of ImageSourceFactory class: 0x%08lx"), hr); 
        goto errorCleanup;
    }

    hr = objectType->GetMethod_6(showConfigurationMethodName, &showConfigurationMethod);
    if (FAILED(hr)) {
        Log(TEXT("Failed to get ShowConfiguration method definition of ImageSourceFactory class: 0x%08lx"), hr); 
        goto errorCleanup;
    }

    goto success;

errorCleanup:

    Detach();
    return false;

success:
    return true;
}

void CLRImageSourceFactory::Detach()
{
    if (createMethod) {
        createMethod->Release();
        createMethod = nullptr;
    }
    if (getDisplayNameMethod) {
        getDisplayNameMethod->Release();
        getDisplayNameMethod = nullptr;
    }
    if (getSourceClassNameMethod) {
        getSourceClassNameMethod->Release();
        getSourceClassNameMethod = nullptr;
    }
    if (showConfigurationMethod) {
        showConfigurationMethod->Release();
        showConfigurationMethod = nullptr;
    }

    CLRObject::Detach();
}

CLRImageSource *CLRImageSourceFactory::Create()
{
    if (!IsValid()) {
        Log(TEXT("CLRImageSourceFactory::Create() no managed object attached"));
        return nullptr;
    }

    variant_t objectRef(GetObjectRef());
    variant_t returnVal;

    HRESULT hr = createMethod->Invoke_3(objectRef, nullptr, &returnVal);
    if (FAILED(hr) || !returnVal.punkVal) {
        Log(TEXT("Failed to invoke Create on managed instance: 0x%08lx"), hr); 
        return nullptr;
    }
    _Type *returnType = nullptr;
    hr = createMethod->get_returnType(&returnType);

    if (FAILED(hr) || !returnType) {
        Log(TEXT("Failed to get return type for Create method"));
        return nullptr;
    }

    CLRImageSource *imageSource = new CLRImageSource();
    if (!imageSource->Attach(CLRObjectRef(returnVal.punkVal, nullptr), returnType)) {
        Log(TEXT("Failed to attach unmanaged wrapper to managed ImageSource object"));
        returnType->Release();
        delete imageSource;
        return nullptr;
    } else {
        returnType->Release();
    }


    return imageSource;   
}

std::wstring CLRImageSourceFactory::GetDisplayName()
{
    if (!IsValid()) {
        Log(TEXT("CLRImageSourceFactory::GetDisplayName() no managed object attached"));
        return std::wstring(TEXT("!error! see log"));
    }

    variant_t objectRef(GetObjectRef());
    variant_t returnVal;

    HRESULT hr = getDisplayNameMethod->Invoke_3(objectRef, nullptr, &returnVal);
    if (FAILED(hr)) {
        Log(TEXT("Failed to invoke GetDisplayName on managed instance: 0x%08lx"), hr); 
        return std::wstring(TEXT("!error! see log"));
    }

    return std::wstring((const wchar_t*)returnVal.bstrVal);
}

std::wstring CLRImageSourceFactory::GetSourceClassName()
{
    if (!IsValid()) {
        Log(TEXT("CLRImageSourceFactory::GetSourceClassName() no managed object attached"));
        return std::wstring(TEXT("!error! see log"));
    }

    variant_t objectRef(GetObjectRef());
    variant_t returnVal;

    HRESULT hr = getSourceClassNameMethod->Invoke_3(objectRef, nullptr, &returnVal);
    if (FAILED(hr)) {
        Log(TEXT("Failed to invoke GetSourceClassName on managed instance: 0x%08lx"), hr); 
        return std::wstring(TEXT("!error! see log"));
    }

    return std::wstring((const wchar_t*)returnVal.bstrVal);
}

void CLRImageSourceFactory::ShowConfiguration()
{
    if (!IsValid()) {
        Log(TEXT("CLRImageSourceFactory::ShowConfiguration() no managed object attached"));
        return;
    }

    variant_t objectRef(GetObjectRef());

    HRESULT hr = showConfigurationMethod->Invoke_3(objectRef, nullptr, nullptr);
    if (FAILED(hr)) {
        Log(TEXT("Failed to invoke ShowConfiguration on managed instance: 0x%08lx"), hr); 
        return;
    }
}