#include "CLRPlugin.h"

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

bool CLRPlugin::Attach(CLRObjectRef &clrObjectRef, mscorlib::_Type *objectType)
{
    CLRObject::Attach(clrObjectRef, objectType);

    bstr_t loadPlugindName("LoadPlugin");
    bstr_t unloadPluginMethodName("UnloadPlugin");
    bstr_t onStartStreamMethodName("OnStartStream");
    bstr_t onStopStreamMethodName("OnStopStream");
    bstr_t getPluginNameMethodName("GetPluginName");
    bstr_t getPluginDescriptionMethodName("GetPluginDescription");


    HRESULT hr;
    
    hr = objectType->GetMethod_6(loadPlugindName, &loadPluginMethod);
    if (FAILED(hr)) {
        Log(TEXT("Failed to get LoadPlugin method definition of Plugin class: 0x%08lx"), hr); 
        goto errorCleanup;
    }

    hr = objectType->GetMethod_6(unloadPluginMethodName, &unloadPluginMethod);
    if (FAILED(hr)) {
        Log(TEXT("Failed to get UnloadPlugin method definition of Plugin class: 0x%08lx"), hr); 
        goto errorCleanup;
    }

    hr = objectType->GetMethod_6(onStartStreamMethodName, &onStartStreamMethod);
    if (FAILED(hr)) {
        Log(TEXT("Failed to get OnStartStream method definition of Plugin class: 0x%08lx"), hr); 
        goto errorCleanup;
    }

    hr = objectType->GetMethod_6(onStopStreamMethodName, &onStopStreamMethod);
    if (FAILED(hr)) {
        Log(TEXT("Failed to get OnStopStream method definition of Plugin class: 0x%08lx"), hr); 
        goto errorCleanup;
    }

    hr = objectType->GetMethod_6(getPluginNameMethodName, &getPluginNameMethod);
    if (FAILED(hr)) {
        Log(TEXT("Failed to get GetPluginName method definition of Plugin class: 0x%08lx"), hr); 
        goto errorCleanup;
    }

    hr = objectType->GetMethod_6(getPluginDescriptionMethodName, &getPluginDescriptionMethod);
    if (FAILED(hr)) {
        Log(TEXT("Failed to get GetPluginDescription method definition of Plugin class: 0x%08lx"), hr); 
        goto errorCleanup;
    }

    goto success;

errorCleanup:
    
    Detach();
    return false;

success:
    return true;
}

void CLRPlugin::Detach()
{
    if (loadPluginMethod) {
        loadPluginMethod->Release();
        loadPluginMethod = nullptr;
    }
    if (unloadPluginMethod) {
        unloadPluginMethod->Release();
        unloadPluginMethod = nullptr;
    }
    if (onStartStreamMethod) {
        onStartStreamMethod->Release();
        onStartStreamMethod = nullptr;
    }
    if (onStopStreamMethod) {
        onStopStreamMethod->Release();
        onStopStreamMethod = nullptr;
    }
    if (getPluginNameMethod) {
        getPluginNameMethod->Release();
        getPluginNameMethod = nullptr;
    }
    if (getPluginDescriptionMethod) {
        getPluginDescriptionMethod->Release();
        getPluginDescriptionMethod = nullptr;
    }

    CLRObject::Detach();
}

std::wstring CLRPlugin::GetPluginName()
{
    if (!IsValid()) {
        Log(TEXT("CLRPlugin::GetPluginName() no managed object attached"));
        return std::wstring(TEXT("!error! see log"));
    }

    variant_t objectRef(GetObjectRef());
    variant_t returnVal;

    HRESULT hr = getPluginNameMethod->Invoke_3(objectRef, nullptr, &returnVal);
    if (FAILED(hr)) {
        Log(TEXT("Failed to invoked GetPluginName on managed instance: 0x%08lx"), hr); 
        return std::wstring(TEXT("!error! see log"));
    }

    return std::wstring((const wchar_t*)returnVal.bstrVal);
}

std::wstring CLRPlugin::GetPluginDescription()
{
    if (!IsValid()) {
        Log(TEXT("CLRPlugin::GetPluginDescription() no managed object attached"));
        return std::wstring(TEXT("!error! see log"));
    }

    variant_t objectRef(GetObjectRef());
    variant_t returnVal;

    HRESULT hr = getPluginDescriptionMethod->Invoke_3(objectRef, nullptr, &returnVal);
    if (FAILED(hr)) {
        Log(TEXT("Failed to invoked GetPluginDescription on managed instance: 0x%08lx"), hr); 
        return std::wstring(TEXT("!error! see log"));
    }

    return std::wstring((const wchar_t*)returnVal.bstrVal);
}