#include "stdafx.h"

#include "CLRSettingsPane.h"

#include "mscorelib.h"

bool CLRSettingsPane::Attach(CLRObjectRef &clrObjectRef, mscorlib::_Type *objectType)
{
    CLRObject::Attach(clrObjectRef, objectType);

    bstr_t createPaneMethodName("CreatePane");
    bstr_t destroyPaneMethodName("DestroyPane");
    bstr_t applySettingsMethodName("ApplySettings");
    bstr_t cancelSettingsMethodName("CancelSettings");
    bstr_t hasDefaultsMethodName("HasDefaults");
    bstr_t setDefaultsMethodName("SetDefaults");

    // properties
    bstr_t getCategoryMethodName("get_Category");

    HRESULT hr;

    hr = objectType->GetMethod_6(createPaneMethodName, &createPaneMethod);
    if (FAILED(hr) || !createPaneMethod) {
        Log(TEXT("Failed to get CreatePane method definition of SettingsPane class: 0x%08lx"), hr); 
        goto errorCleanup;
    }

    hr = objectType->GetMethod_6(destroyPaneMethodName, &destroyPaneMethod);
    if (FAILED(hr) || !destroyPaneMethod) {
        Log(TEXT("Failed to get DestroyPane method definition of SettingsPane class: 0x%08lx"), hr); 
        goto errorCleanup;
    }


    hr = objectType->GetMethod_6(applySettingsMethodName, &applySettingsMethod);
    if (FAILED(hr) || !applySettingsMethod) {
        Log(TEXT("Failed to get ApplySettings method definition of SettingsPane class: 0x%08lx"), hr); 
        goto errorCleanup;
    }

    hr = objectType->GetMethod_6(cancelSettingsMethodName, &cancelSettingsMethod);
    if (FAILED(hr) || !cancelSettingsMethod) {
        Log(TEXT("Failed to get CancelSettings method definition of SettingsPane class: 0x%08lx"), hr); 
        goto errorCleanup;
    }

    hr = objectType->GetMethod_6(hasDefaultsMethodName, &hasDefaultsMethod);
    if (FAILED(hr) || !hasDefaultsMethod) {
        Log(TEXT("Failed to get HasDefaults method definition of SettingsPane class: 0x%08lx"), hr); 
        goto errorCleanup;
    }

    hr = objectType->GetMethod_6(setDefaultsMethodName, &setDefaultsMethod);
    if (FAILED(hr) || !setDefaultsMethod) {
        Log(TEXT("Failed to get SetDefaults method definition of SettingsPane class: 0x%08lx"), hr); 
        goto errorCleanup;
    }

    hr = objectType->GetMethod_6(getCategoryMethodName, &getCategoryMethod);
    if (FAILED(hr) || !getCategoryMethodName) {
        Log(TEXT("Failed to get Category property get() method definition of SettingsPane class: 0x%08lx"), hr); 
        goto errorCleanup;
    }

    goto success;

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
    if (!IsValid()) {
        Log(TEXT("CLRSettingsPane::CreatePane() no managed object attached"));
        return 0;
    }

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
        Log(TEXT("Failed to invoke CLRSettingsPane::CreatePane on managed instance: 0x%08lx"), hr); 
        return 0;
    }

    return returnVal.llVal;
}

void CLRSettingsPane::DestroyPane()
{
    if (!IsValid()) {
        Log(TEXT("CLRSettingsPane::DestroyPane() no managed object attached"));
        return;
    }

    variant_t objectRef(GetObjectRef());

    HRESULT hr = destroyPaneMethod->Invoke_3(objectRef, nullptr, nullptr);

    if (FAILED(hr)) {
        Log(TEXT("Failed to invoke CLRSettingsPane::DestroyPane on managed instance: 0x%08lx"), hr); 
        return;
    }
}

void CLRSettingsPane::ApplySettings()
{
    if (!IsValid()) {
        Log(TEXT("CLRSettingsPane::ApplySettings() no managed object attached"));
        return;
    }

    variant_t objectRef(GetObjectRef());

    HRESULT hr = applySettingsMethod->Invoke_3(objectRef, nullptr, nullptr);

    if (FAILED(hr)) {
        Log(TEXT("Failed to invoke CLRSettingsPane::ApplySettings on managed instance: 0x%08lx"), hr); 
        return;
    }
}

void CLRSettingsPane::CancelSettings()
{
    if (!IsValid()) {
        Log(TEXT("CLRSettingsPane::CancelSettings() no managed object attached"));
        return;
    }

    variant_t objectRef(GetObjectRef());

    HRESULT hr = cancelSettingsMethod->Invoke_3(objectRef, nullptr, nullptr);

    if (FAILED(hr)) {
        Log(TEXT("Failed to invoke CLRSettingsPane::CancelSettings on managed instance: 0x%08lx"), hr); 
        return;
    }
}

bool CLRSettingsPane::HasDefaults()
{
    if (!IsValid()) {
        Log(TEXT("CLRSettingsPane::SetDefaults() no managed object attached"));
        return false;
    }

    variant_t objectRef(GetObjectRef());
    variant_t returnVal;

    HRESULT hr = hasDefaultsMethod->Invoke_3(objectRef, nullptr, &returnVal);

    if (FAILED(hr)) {
        Log(TEXT("Failed to invoke CLRSettingsPane::SetDefaults on managed instance: 0x%08lx"), hr); 
        return false;
    }

    return returnVal.boolVal == VARIANT_TRUE;
}

void CLRSettingsPane::SetDefaults()
{
    if (!IsValid()) {
        Log(TEXT("CLRSettingsPane::SetDefaults() no managed object attached"));
    }

    variant_t objectRef(GetObjectRef());

    HRESULT hr = setDefaultsMethod->Invoke_3(objectRef, nullptr, nullptr);

    if (FAILED(hr)) {
        Log(TEXT("Failed to invoke CLRSettingsPane::SetDefaults on managed instance: 0x%08lx"), hr); 
        return;
    }
}

// small hack to keep around the category string long enough
std::wstring& CLRSettingsPane::GetCategory()
{
    if (!IsValid()) {
        Log(TEXT("CLRSettingsPane::GetCategory() no managed object attached"));
        return category = std::wstring(TEXT("!error! see log"));
    }

    variant_t objectRef(GetObjectRef());
    variant_t returnVal;

    HRESULT hr = getCategoryMethod->Invoke_3(objectRef, nullptr, &returnVal);
    if (FAILED(hr) || returnVal.bstrVal == nullptr) {
        Log(TEXT("Failed to invoke CLRSettingsPane::GetCategory on managed instance: 0x%08lx"), hr); 
        return category = std::wstring(TEXT("!error! see log"));
    }

    return category = std::wstring((const wchar_t*)returnVal.bstrVal);
}