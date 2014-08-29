#include "stdafx.h"

#include "CLRImageSourceFactory.h"
#include "CLRImageSource.h"
#include "CLRXElement.h"

#include "mscorelib.h"

bool CLRImageSourceFactory::Attach(CLRObjectRef &clrObjectRef, mscorlib::_Type *objectType)
{
    if (CLRObject::Attach(clrObjectRef, objectType)) {
        if (!CLR_GET_METHOD(objectType, "Create", &createMethod)) {
            goto errorCleanup;
        }

        if (!CLR_GET_METHOD(objectType, "get_DisplayName", &getDisplayNameMethod)) {
            goto errorCleanup;
        }

        if (!CLR_GET_METHOD(objectType, "get_ClassName", &getSourceClassNameMethod)) {
            goto errorCleanup;
        }

        if (!CLR_GET_METHOD(objectType, "ShowConfiguration", &showConfigurationMethod)) {
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

CLRImageSource *CLRImageSourceFactory::Create(CLRXElement *element)
{
    CLROBJECT_CHECK_VALID_NONVOID(nullptr);

    // Must Release
    SAFEARRAY *createArgs = nullptr;
    SAFEARRAY *parameterTypes = nullptr;
    SAFEARRAY *constructors = nullptr;
    SAFEARRAY *constructorParameters = nullptr;
    mscorlib::_ParameterInfo *elementTypeInfo = nullptr;
    mscorlib::_Type *elementType = nullptr;
    mscorlib::_Type *returnType = nullptr;
    CLRImageSource *imageSource = nullptr;

    // Local
    HRESULT hr;
    variant_t objectRef(GetObjectRef());
    variant_t returnVal;
    variant_t elementRef(element->GetObjectRef());
    LONG argIndex = 0;

    createArgs = SafeArrayCreateVector(VT_VARIANT, 0, 1);

    hr = SafeArrayPutElement(createArgs, &argIndex, &elementRef);
    if (FAILED(hr)) {
        Log(L"CLRImageSourceFactory::Create() failed to set config argument "
            L"pointer: 0x%08lx", hr);
        goto errorCleanup;
    }

    hr = createMethod->Invoke_3(objectRef, createArgs, &returnVal);
    if (FAILED(hr) || !returnVal.punkVal) {
        Log(L"Failed to invoke Create on managed instance: 0x%08lx", hr);
        goto errorCleanup;
    }
    SafeArrayDestroy(createArgs);
    createArgs = nullptr;

    hr = createMethod->get_returnType(&returnType);
    if (FAILED(hr) || !returnType) {
        Log(L"Failed to get return type for Create method");
        goto errorCleanup;
    }

    imageSource = new CLRImageSource();
    if (!imageSource->Attach(CLRObjectRef(returnVal.punkVal, nullptr), returnType)) {
        Log(L"Failed to attach unmanaged wrapper to managed ImageSource "
            L"object");
        goto errorCleanup;
    }
    returnType->Release();
    goto success;

errorCleanup:
    if (parameterTypes) {
        SafeArrayDestroy(parameterTypes);
        parameterTypes = nullptr;
    }
    if (createArgs) {
        SafeArrayDestroy(createArgs);
        createArgs = nullptr;
    }
    if (constructors) {
        SafeArrayDestroy(constructors);
        constructors = nullptr;
    }
    if (constructorParameters) {
        SafeArrayDestroy(constructorParameters);
        constructorParameters = nullptr;
    }
    if (elementType) {
        elementType->Release();
        elementType = nullptr;
    }
    if (returnType) {
        returnType->Release();
        returnType = nullptr;
    }
    if (imageSource) {
        delete imageSource;
        imageSource = nullptr;
    }
success:

    return imageSource;
}

std::wstring CLRImageSourceFactory::GetDisplayName()
{
    CLROBJECT_CHECK_VALID_NONVOID(std::wstring(L"!error! see log"));

    variant_t objectRef(GetObjectRef());
    variant_t returnVal;

    HRESULT hr = getDisplayNameMethod->Invoke_3(objectRef, nullptr, &returnVal);
    if (FAILED(hr)) {
        Log(L"Failed to invoke GetDisplayName on managed instance: "
            L"0x%08lx", hr);
        return std::wstring(L"!error! see log");
    }

    return std::wstring((const wchar_t*) returnVal.bstrVal);
}

std::wstring CLRImageSourceFactory::GetSourceClassName()
{
    CLROBJECT_CHECK_VALID_NONVOID(std::wstring(L"!error! see log"));

    variant_t objectRef(GetObjectRef());
    variant_t returnVal;

    HRESULT hr = getSourceClassNameMethod->Invoke_3(objectRef, nullptr, &returnVal);
    if (FAILED(hr)) {
        Log(L"Failed to invoke GetSourceClassName on managed instance: 0x%08lx",
            hr);
        return std::wstring(L"!error! see log");
    }

    return std::wstring((const wchar_t*) returnVal.bstrVal);
}

bool CLRImageSourceFactory::ShowConfiguration(CLRXElement *element)
{
    CLROBJECT_CHECK_VALID_NONVOID(false);

    HRESULT hr;
    variant_t objectRef(GetObjectRef());
    SAFEARRAY *createArgs = nullptr;
    variant_t elementRef(element->GetObjectRef());
    LONG argIndex = 0;
    variant_t returnVal(false);

    createArgs = SafeArrayCreateVector(VT_VARIANT, 0, 1);

    hr = SafeArrayPutElement(createArgs, &argIndex, &elementRef);
    if (FAILED(hr)) {
        Log(L"CLRImageSourceFactory::ShowConfiguration() failed to set config "
            L"argument pointer: 0x%08lx", hr);
        goto errorCleanup;
    }

    hr = showConfigurationMethod->Invoke_3(objectRef, createArgs, &returnVal);
    if (FAILED(hr)) {
        Log(L"CLRImageSourceFactory::ShowConfiguration() failed to invoke "
            L"ShowConfiguration on managed instance: 0x%08lx", hr);
        goto errorCleanup;
    }
    SafeArrayDestroy(createArgs);
    createArgs = nullptr;

    goto success;

errorCleanup:
    if (createArgs) {
        SafeArrayDestroy(createArgs);
        createArgs = nullptr;
    }

success:
    return returnVal.boolVal == VARIANT_TRUE;
}