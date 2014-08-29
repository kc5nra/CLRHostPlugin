#include "stdafx.h"

#include "CLRImageSource.h"
#include "CLRVector2.h"

#include "mscorelib.h"

bool CLRImageSource::Attach(CLRObjectRef &clrObjectRef, mscorlib::_Type *objectType)
{
    CLRObject::Attach(clrObjectRef, objectType);

    bstr_t preprocessMethodName("Preprocess");
    bstr_t tickMethodName("Tick");
    bstr_t renderMethodName("Render");
    bstr_t getSizeMethodName("get_Size");
    bstr_t updateSettingsMethodName("UpdateSettings");
    bstr_t beginSceneMethodName("BeginScene");
    bstr_t endSceneMethodName("EndScene");
    
    HRESULT hr;

    hr = objectType->GetMethod_6(preprocessMethodName, &preprocessMethod);
    if (FAILED(hr) || !preprocessMethod) {
        Log(TEXT("Failed to get Preprocess method definition of ImageSource class: 0x%08lx"), hr); 
        goto errorCleanup;
    }

    hr = objectType->GetMethod_6(tickMethodName, &tickMethod);
    if (FAILED(hr) || !tickMethod) {
        Log(TEXT("Failed to get Tick method definition of ImageSource class: 0x%08lx"), hr); 
        goto errorCleanup;
    }

    hr = objectType->GetMethod_6(renderMethodName, &renderMethod);
    if (FAILED(hr) || !renderMethod) {
        Log(TEXT("Failed to get Render method definition of ImageSource class: 0x%08lx"), hr); 
        goto errorCleanup;
    }

    hr = objectType->GetMethod_6(getSizeMethodName, &getSizeMethod);
    if (FAILED(hr) || !getSizeMethod) {
        Log(TEXT("Failed to get GetSize method definition of ImageSource class: 0x%08lx"), hr); 
        goto errorCleanup;
    }

    hr = objectType->GetMethod_6(updateSettingsMethodName, &updateSettingsMethod);
    if (FAILED(hr) || !updateSettingsMethod) {
        Log(TEXT("Failed to get UpdateSettings method definition of ImageSource class: 0x%08lx"), hr); 
        goto errorCleanup;
    }

    hr = objectType->GetMethod_6(beginSceneMethodName, &beginSceneMethod);
    if (FAILED(hr) || !beginSceneMethod) {
        Log(TEXT("Failed to get BeginScene method definition of ImageSource class: 0x%08lx"), hr); 
        goto errorCleanup;
    }

    hr = objectType->GetMethod_6(endSceneMethodName, &endSceneMethod);
    if (FAILED(hr) || !endSceneMethod) {
        Log(TEXT("Failed to get EndScene method definition of ImageSource class: 0x%08lx"), hr); 
        goto errorCleanup;
    }

    goto success;

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
    if (!IsValid()) {
        Log(TEXT("CLRPlugin::Preprocess() no managed object attached"));
    }

    variant_t objectRef(GetObjectRef());

    HRESULT hr = preprocessMethod->Invoke_3(objectRef, nullptr, nullptr);
    if (FAILED(hr)) {
        Log(TEXT("Failed to invoke Preprocess on managed instance: 0x%08lx"), hr); 
    }

    return;
}

void CLRImageSource::Tick(float seconds)
{
    if (!IsValid()) {
        Log(TEXT("CLRImageSource::Tick() no managed object attached"));
    }

    variant_t objectRef(GetObjectRef());
    variant_t val(seconds);
    HRESULT hr;
    SAFEARRAY *args = SafeArrayCreateVector(VT_VARIANT, 0, 1);
    LONG index = 0;
    
    hr = SafeArrayPutElement(args, &index, &val);

    hr = tickMethod->Invoke_3(objectRef, args, nullptr);
    SafeArrayDestroy(args);
    
    if (FAILED(hr)) {
        Log(TEXT("CLRVector2::Tick() failed to invoked on managed instance: 0x%08lx"), hr); 
        return;
    }

    return;
}

void CLRImageSource::Render(float x, float y, float width, float height)
{
    if (!IsValid()) {
        Log(TEXT("CLRImageSource::Render() no managed object attached"));
    }

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
        Log(TEXT("CLRImageSource::Render() failed to invoked on managed instance: 0x%08lx"), hr); 
        return;
    }

    return;
}

CLRVector2 *CLRImageSource::GetSize()
{
    if (!IsValid()) {
        Log(TEXT("CLRImageSource::GetSize() no managed object attached"));
        return nullptr;
    }

    variant_t objectRef(GetObjectRef());
    variant_t returnVal;

    HRESULT hr = getSizeMethod->Invoke_3(objectRef, nullptr, &returnVal);
    if (FAILED(hr) || !returnVal.punkVal) {
        Log(TEXT("CLRImageSource::GetSize() failed to invoke on managed instance: 0x%08lx"), hr); 
        return nullptr;
    }
    
    mscorlib::_Type *returnType = nullptr;
    hr = getSizeMethod->get_returnType(&returnType);

    if (FAILED(hr) || !returnType) {
        Log(TEXT("CLRImageSource::GetSize() failed to get return type of managed method"));
        return nullptr;
    }

    CLRVector2 *vector2 = new CLRVector2();
    if (!vector2->Attach(CLRObjectRef(returnVal.punkVal, nullptr), returnType)) {
        Log(TEXT("CLRImageSource::GetSize() ailed to attach unmanaged wrapper to managed Vector2 object"));
        returnType->Release();
        delete vector2;
        return nullptr;
    } else {
        returnType->Release();
    }

    return vector2;   
}

void CLRImageSource::UpdateSettings()
{
    if (!IsValid()) {
        Log(TEXT("CLRPlugin::UpdateSettings() no managed object attached"));
    }

    variant_t objectRef(GetObjectRef());

    HRESULT hr = updateSettingsMethod->Invoke_3(objectRef, nullptr, nullptr);
    if (FAILED(hr)) {
        Log(TEXT("CLRPlugin::UpdateSettings() failed to invoke on managed instance: 0x%08lx"), hr); 
    }

    return;
}

void CLRImageSource::BeginScene()
{
    if (!IsValid()) {
        Log(TEXT("CLRPlugin::BeginScene() no managed object attached"));
    }

    variant_t objectRef(GetObjectRef());

    HRESULT hr = beginSceneMethod->Invoke_3(objectRef, nullptr, nullptr);
    if (FAILED(hr)) {
        Log(TEXT("CLRPlugin::BeginScene() failed to invoke on managed instance: 0x%08lx"), hr); 
    }

    return;
}

void CLRImageSource::EndScene()
{
    if (!IsValid()) {
        Log(TEXT("CLRPlugin::EndScene() no managed object attached"));
    }

    variant_t objectRef(GetObjectRef());

    HRESULT hr = endSceneMethod->Invoke_3(objectRef, nullptr, nullptr);
    if (FAILED(hr)) {
        Log(TEXT("CLRPlugin::EndScene() failed to invoke on managed instance: 0x%08lx"), hr); 
    }

    return;
}