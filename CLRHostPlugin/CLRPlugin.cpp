#include "stdafx.h"

#include "CLRPlugin.h"

#include "mscorelib.h"

bool CLRPlugin::Attach(CLRObjectRef &clrObjectRef, mscorlib::_Type *objectType)
{
    if (CLRObject::Attach(clrObjectRef, objectType)) {
        if (!CLR_GET_METHOD(objectType, "LoadPlugin", &loadPluginMethod))
        {
            goto errorCleanup;
        }

        if (!CLR_GET_METHOD(objectType, "UnloadPlugin", &unloadPluginMethod))
        {
            goto errorCleanup;
        }

        if (!CLR_GET_METHOD(objectType, "OnStartStream", &onStartStreamMethod))
        {
            goto errorCleanup;
        }

        if (!CLR_GET_METHOD(objectType, "OnStopStream", &onStopStreamMethod))
        {
            goto errorCleanup;
        }

        if (!CLR_GET_METHOD(objectType, "get_Name", &getPluginNameMethod))
        {
            goto errorCleanup;
        }

        if (!CLR_GET_METHOD(objectType, "get_Description", &getPluginDescriptionMethod)) {
            goto errorCleanup;
        }

        goto success;
    }

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

bool CLRPlugin::LoadPlugin()
{
    CLROBJECT_CHECK_VALID_NONVOID(false);

    variant_t objectRef(GetObjectRef());
    variant_t returnVal;

    HRESULT hr = loadPluginMethod->Invoke_3(objectRef, nullptr, &returnVal);
    if (FAILED(hr)) {
        Log(L"Failed to invoke OnStopStream on managed instance: 0x%08lx", hr);
    }

    return returnVal.boolVal == VARIANT_TRUE;
}

void CLRPlugin::UnloadPlugin()
{
    CLROBJECT_CHECK_VALID_VOID();

    variant_t objectRef(GetObjectRef());

    HRESULT hr = unloadPluginMethod->Invoke_3(objectRef, nullptr, nullptr);
    if (FAILED(hr)) {
        Log(L"Failed to invoke UnloadPlugin on managed instance: 0x%08lx", hr);
    }

    return;
}

void CLRPlugin::OnStartStream()
{
    CLROBJECT_CHECK_VALID_VOID();

    variant_t objectRef(GetObjectRef());

    HRESULT hr = onStartStreamMethod->Invoke_3(objectRef, nullptr, nullptr);
    if (FAILED(hr)) {
        Log(L"Failed to invoke OnStartStream on managed instance: 0x%08lx", hr);
    }

    return;
}

void CLRPlugin::OnStopStream()
{
    CLROBJECT_CHECK_VALID_VOID();

    variant_t objectRef(GetObjectRef());

    HRESULT hr = onStopStreamMethod->Invoke_3(objectRef, nullptr, nullptr);
    if (FAILED(hr)) {
        Log(L"Failed to invoke OnStopStream on managed instance: 0x%08lx", hr);
    }

    return;
}

std::wstring CLRPlugin::GetPluginName()
{
    CLROBJECT_CHECK_VALID_NONVOID(std::wstring(L"!error! see log"));

    variant_t objectRef(GetObjectRef());
    variant_t returnVal;

    HRESULT hr = getPluginNameMethod->Invoke_3(objectRef, nullptr, &returnVal);
    if (FAILED(hr)) {
        Log(L"Failed to invoke GetPluginName on managed instance: 0x%08lx", hr);
        return std::wstring(L"!error! see log");
    }

    return std::wstring((const wchar_t*) returnVal.bstrVal);
}

std::wstring CLRPlugin::GetPluginDescription()
{
    CLROBJECT_CHECK_VALID_NONVOID(std::wstring(L"!error! see log"));

    variant_t objectRef(GetObjectRef());
    variant_t returnVal;

    HRESULT hr = getPluginDescriptionMethod->Invoke_3(objectRef, nullptr, &returnVal);
    if (FAILED(hr)) {
        Log(L"Failed to invoke GetPluginDescription on managed instance: "
            L"0x%08lx", hr);
        return std::wstring(L"!error! see log");
    }

    return std::wstring((const wchar_t*) returnVal.bstrVal);
}