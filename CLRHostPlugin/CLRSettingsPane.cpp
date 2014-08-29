#include "stdafx.h"

#include "CLRSettingsPane.h"

#include "mscorelib.h"

bool CLRSettingsPane::Attach(CLRObjectRef &clrObjectRef, mscorlib::_Type *objectType)
{
    if (CLRObject::Attach(clrObjectRef, objectType)) {
        if (!CLR_GET_METHOD(objectType, "CreatePane", &createPaneMethod)) {
            goto errorCleanup;
        }

        if (!CLR_GET_METHOD(objectType, "DestroyPane", &destroyPaneMethod)) {
            goto errorCleanup;
        }

        if (!CLR_GET_METHOD(objectType, "ApplySettings", &applySettingsMethod)) {
            goto errorCleanup;
        }

        if (!CLR_GET_METHOD(objectType, "CancelSettings", &cancelSettingsMethod)) {
            goto errorCleanup;
        }

        if (!CLR_GET_METHOD(objectType, "HasDefaults", &hasDefaultsMethod)) {
            goto errorCleanup;
        }

        if (!CLR_GET_METHOD(objectType, "SetDefaults", &setDefaultsMethod)) {
            goto errorCleanup;
        }

        if (!CLR_GET_METHOD(objectType, "get_Category", &getCategoryMethod)) {
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

void CLRSettingsPane::Detach()
{
    if (createPaneMethod) {
        createPaneMethod->Release();
        createPaneMethod = nullptr;
    }
    if (destroyPaneMethod) {
        destroyPaneMethod->Release();
        destroyPaneMethod = nullptr;
    }
    if (applySettingsMethod) {
        applySettingsMethod->Release();
        applySettingsMethod = nullptr;
    }
    if (cancelSettingsMethod) {
        cancelSettingsMethod->Release();
        cancelSettingsMethod = nullptr;
    }
    if (hasDefaultsMethod) {
        hasDefaultsMethod->Release();
        hasDefaultsMethod = nullptr;
    }
    if (setDefaultsMethod) {
        setDefaultsMethod->Release();
        setDefaultsMethod = nullptr;
    }
    if (getCategoryMethod) {
        getCategoryMethod->Release();
        getCategoryMethod = nullptr;
    }

    CLRObject::Detach();
}

long long CLRSettingsPane::CreatePane(long long parentHwnd)
{
    CLROBJECT_CHECK_VALID_NONVOID(0);

    variant_t objectRef(GetObjectRef());
    variant_t parentHwndArg(parentHwnd);
    variant_t returnVal;
    HRESULT hr;
    SAFEARRAY *args = SafeArrayCreateVector(VT_VARIANT, 0, 1);
    LONG index = 0;
    hr = SafeArrayPutElement(args, &index, &parentHwndArg);

    hr = createPaneMethod->Invoke_3(objectRef, args, &returnVal);
    SafeArrayDestroy(args);

    if (FAILED(hr)) {
        Log(L"Failed to invoke CLRSettingsPane::CreatePane on managed "
            L"instance: 0x%08lx", hr);
        return 0;
    }

    return returnVal.llVal;
}

void CLRSettingsPane::DestroyPane()
{
    CLROBJECT_CHECK_VALID_VOID();

    variant_t objectRef(GetObjectRef());

    HRESULT hr = destroyPaneMethod->Invoke_3(objectRef, nullptr, nullptr);

    if (FAILED(hr)) {
        Log(L"Failed to invoke CLRSettingsPane::DestroyPane on managed "
            L"instance: 0x%08lx", hr);
        return;
    }
}

void CLRSettingsPane::ApplySettings()
{
    CLROBJECT_CHECK_VALID_VOID();

    variant_t objectRef(GetObjectRef());

    HRESULT hr = applySettingsMethod->Invoke_3(objectRef, nullptr, nullptr);

    if (FAILED(hr)) {
        Log(L"Failed to invoke CLRSettingsPane::ApplySettings on managed "
            L"instance: 0x%08lx", hr);
        return;
    }
}

void CLRSettingsPane::CancelSettings()
{
    CLROBJECT_CHECK_VALID_VOID();

    variant_t objectRef(GetObjectRef());

    HRESULT hr = cancelSettingsMethod->Invoke_3(objectRef, nullptr, nullptr);

    if (FAILED(hr)) {
        Log(L"Failed to invoke CLRSettingsPane::CancelSettings on managed "
            L"instance: 0x%08lx", hr);
        return;
    }
}

bool CLRSettingsPane::HasDefaults()
{
    CLROBJECT_CHECK_VALID_NONVOID(false);

    variant_t objectRef(GetObjectRef());
    variant_t returnVal;

    HRESULT hr = hasDefaultsMethod->Invoke_3(objectRef, nullptr, &returnVal);

    if (FAILED(hr)) {
        Log(L"Failed to invoke CLRSettingsPane::SetDefaults on managed "
            L"instance: 0x%08lx", hr);
        return false;
    }

    return returnVal.boolVal == VARIANT_TRUE;
}

void CLRSettingsPane::SetDefaults()
{
    CLROBJECT_CHECK_VALID_VOID();

    variant_t objectRef(GetObjectRef());

    HRESULT hr = setDefaultsMethod->Invoke_3(objectRef, nullptr, nullptr);

    if (FAILED(hr)) {
        Log(L"Failed to invoke CLRSettingsPane::SetDefaults on managed "
            L"instance: 0x%08lx", hr);
        return;
    }
}

// small hack to keep around the category string long enough
std::wstring& CLRSettingsPane::GetCategory()
{
    CLROBJECT_CHECK_VALID_NONVOID(category = std::wstring(L"!error! see log"));

    variant_t objectRef(GetObjectRef());
    variant_t returnVal;

    HRESULT hr = getCategoryMethod->Invoke_3(objectRef, nullptr, &returnVal);
    if (FAILED(hr) || returnVal.bstrVal == nullptr) {
        Log(L"Failed to invoke CLRSettingsPane::GetCategory on managed "
            L"instance: 0x%08lx", hr);
        return category = std::wstring(L"!error! see log");
    }

    return category = std::wstring((const wchar_t*) returnVal.bstrVal);
}