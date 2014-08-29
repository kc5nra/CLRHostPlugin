#include "stdafx.h"

#include "CLRImageSource.h"
#include "CLRVector2.h"

#include "mscorelib.h"

bool CLRImageSource::Attach(CLRObjectRef &clrObjectRef, mscorlib::_Type *objectType)
{
    if (CLRObject::Attach(clrObjectRef, objectType))
    {
        if (!CLR_GET_METHOD(objectType, "Preprocess", &preprocessMethod)) {
            goto errorCleanup;
        }

        if (!CLR_GET_METHOD(objectType, "Tick", &tickMethod)) {
            goto errorCleanup;
        }

        if (!CLR_GET_METHOD(objectType, "Render", &renderMethod)) {
            goto errorCleanup;
        }

        if (!CLR_GET_METHOD(objectType, "get_Size", &getSizeMethod)) {
            goto errorCleanup;
        }

        if (!CLR_GET_METHOD(objectType, "UpdateSettings", &updateSettingsMethod)) {
            goto errorCleanup;
        }

        if (!CLR_GET_METHOD(objectType, "BeginScene", &beginSceneMethod)) {
            goto errorCleanup;
        }

        if (!CLR_GET_METHOD(objectType, "EndScene", &endSceneMethod)) {
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

void CLRImageSource::Detach()
{
    if (preprocessMethod) {
        preprocessMethod->Release();
        preprocessMethod = nullptr;
    }
    if (tickMethod) {
        tickMethod->Release();
        tickMethod = nullptr;
    }
    if (renderMethod) {
        renderMethod->Release();
        renderMethod = nullptr;
    }
    if (getSizeMethod) {
        getSizeMethod->Release();
        getSizeMethod = nullptr;
    }
    if (updateSettingsMethod) {
        updateSettingsMethod->Release();
        updateSettingsMethod = nullptr;
    }
    if (beginSceneMethod) {
        beginSceneMethod->Release();
        beginSceneMethod = nullptr;
    }
    if (endSceneMethod) {
        endSceneMethod->Release();
        endSceneMethod = nullptr;
    }

    CLRObject::Detach();
}

void CLRImageSource::Preprocess()
{
    CLROBJECT_CHECK_VALID_VOID();

    variant_t objectRef(GetObjectRef());

    HRESULT hr = preprocessMethod->Invoke_3(objectRef, nullptr, nullptr);
    if (FAILED(hr)) {
        Log(L"Failed to invoke Preprocess on managed instance: 0x%08lx",
            hr);
    }

    return;
}

void CLRImageSource::Tick(float seconds)
{
    CLROBJECT_CHECK_VALID_VOID();

    variant_t objectRef(GetObjectRef());
    variant_t val(seconds);
    HRESULT hr;
    SAFEARRAY *args = SafeArrayCreateVector(VT_VARIANT, 0, 1);
    LONG index = 0;

    hr = SafeArrayPutElement(args, &index, &val);

    hr = tickMethod->Invoke_3(objectRef, args, nullptr);
    SafeArrayDestroy(args);

    if (FAILED(hr)) {
        Log(L"CLRVector2::Tick() failed to invoked on managed instance: "
            L"0x%08lx", hr);
        return;
    }

    return;
}

void CLRImageSource::Render(
    float x, float y,
    float width, float height)
{
    CLROBJECT_CHECK_VALID_VOID();

    variant_t objectRef(GetObjectRef());

    variant_t valX(x);
    variant_t valY(y);
    variant_t valWidth(width);
    variant_t valHeight(height);

    SAFEARRAY *args = SafeArrayCreateVector(VT_VARIANT, 0, 4);
    LONG index = 0;
    SafeArrayPutElement(args, &index, &valX);
    index++;
    SafeArrayPutElement(args, &index, &valY);
    index++;
    SafeArrayPutElement(args, &index, &valWidth);
    index++;
    SafeArrayPutElement(args, &index, &valHeight);

    HRESULT hr = renderMethod->Invoke_3(objectRef, args, nullptr);
    SafeArrayDestroy(args);

    if (FAILED(hr)) {
        Log(L"CLRImageSource::Render() failed to invoked on managed "
            L"instance: 0x%08lx", hr);
        return;
    }

    return;
}

CLRVector2 *CLRImageSource::GetSize()
{
    CLROBJECT_CHECK_VALID_NONVOID(nullptr);

    variant_t objectRef(GetObjectRef());
    variant_t returnVal;

    HRESULT hr = getSizeMethod->Invoke_3(objectRef, nullptr, &returnVal);
    if (FAILED(hr) || !returnVal.punkVal) {
        Log(L"CLRImageSource::GetSize() failed to invoke on managed instance: "
            L"0x%08lx", hr);
        return nullptr;
    }

    mscorlib::_Type *returnType = nullptr;
    hr = getSizeMethod->get_returnType(&returnType);

    if (FAILED(hr) || !returnType) {
        Log(L"CLRImageSource::GetSize() failed to get return type of managed "
            L"method");
        return nullptr;
    }

    CLRVector2 *vector2 = new CLRVector2();
    if (!vector2->Attach(CLRObjectRef(returnVal.punkVal, nullptr), returnType))
    {
        Log(L"CLRImageSource::GetSize() ailed to attach unmanaged wrapper to "
            L"managed Vector2 object");
        returnType->Release();
        delete vector2;
        return nullptr;
    }
    else {
        returnType->Release();
    }

    return vector2;
}

void CLRImageSource::UpdateSettings()
{
    CLROBJECT_CHECK_VALID_VOID();

    variant_t objectRef(GetObjectRef());

    HRESULT hr = updateSettingsMethod->Invoke_3(objectRef, nullptr, nullptr);
    if (FAILED(hr)) {
        Log(L"CLRPlugin::UpdateSettings() failed to invoke on managed "
            L"instance: 0x%08lx", hr);
    }

    return;
}

void CLRImageSource::BeginScene()
{
    CLROBJECT_CHECK_VALID_VOID();

    variant_t objectRef(GetObjectRef());

    HRESULT hr = beginSceneMethod->Invoke_3(objectRef, nullptr, nullptr);
    if (FAILED(hr)) {
        Log(L"CLRPlugin::BeginScene() failed to invoke on managed "
            L"instance: 0x%08lx", hr);
    }

    return;
}

void CLRImageSource::EndScene()
{
    CLROBJECT_CHECK_VALID_VOID();

    variant_t objectRef(GetObjectRef());

    HRESULT hr = endSceneMethod->Invoke_3(objectRef, nullptr, nullptr);
    if (FAILED(hr)) {
        Log(L"CLRPlugin::EndScene() failed to invoke on managed instance: "
            L"0x%08lx", hr);
    }

    return;
}