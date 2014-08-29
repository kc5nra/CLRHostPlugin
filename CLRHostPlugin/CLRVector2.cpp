#include "stdafx.h"

#include "CLRVector2.h"

#include "mscorelib.h"

bool CLRVector2::Attach(CLRObjectRef &clrObjectRef, mscorlib::_Type *objectType)
{
    CLRObject::Attach(clrObjectRef, objectType);

    bstr_t getXMethodName("get_X");
    bstr_t setXMethodName("set_X");
    bstr_t getYMethodName("get_Y");
    bstr_t setYMethodName("set_Y");

    HRESULT hr;

    hr = objectType->GetMethod_6(getXMethodName, &getXMethod);
    if (FAILED(hr)) {
        Log(TEXT("Failed to get Create method definition of ImageSourceFactory class: 0x%08lx"), hr); 
        goto errorCleanup;
    }

    hr = objectType->GetMethod_6(setXMethodName, &setXMethod);
    if (FAILED(hr)) {
        Log(TEXT("Failed to get GetDisplayName method definition of ImageSourceFactory class: 0x%08lx"), hr); 
        goto errorCleanup;
    }

    hr = objectType->GetMethod_6(getYMethodName, &getYMethod);
    if (FAILED(hr)) {
        Log(TEXT("Failed to get GetSourceClassName method definition of ImageSourceFactory class: 0x%08lx"), hr); 
        goto errorCleanup;
    }

    hr = objectType->GetMethod_6(setYMethodName, &setYMethod);
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

void CLRVector2::Detach()
{
    if (getXMethod) {
        getXMethod->Release();
        getXMethod = nullptr;
    }
    if (setXMethod) {
        setXMethod->Release();
        setXMethod = nullptr;
    }
    if (getYMethod) {
        getYMethod->Release();
        getYMethod = nullptr;
    }
    if (setYMethod) {
        setYMethod->Release();
        setYMethod = nullptr;
    }

    CLRObject::Detach();
}

float CLRVector2::getX()
{
    if (!IsValid()) {
        Log(TEXT("CLRVector2::getX() no managed object attached"));
        return 0.0f;
    }

    variant_t objectRef(GetObjectRef());
    variant_t returnVal;

    HRESULT hr = getXMethod->Invoke_3(objectRef, nullptr, &returnVal);
    if (FAILED(hr)) {
        Log(TEXT("CLRVector2::getX() Failed to invoked get on managed property Y: 0x%08lx"), hr); 
        return 0.0f;
    }

    return returnVal.fltVal;
}

void CLRVector2::setX(float x)
{
    if (!IsValid()) {
        Log(TEXT("CLRVector2::setX() no managed object attached"));
    }

    variant_t objectRef(GetObjectRef());
    variant_t returnVal;
    variant_t val(x);
    SAFEARRAY *args = SafeArrayCreateVector(VT_R4, 0, 1);
    LONG index = 0;
    SafeArrayPutElement(args, &index, &val);

    HRESULT hr = setXMethod->Invoke_3(objectRef, args, &returnVal);
    SafeArrayDestroy(args);

    if (FAILED(hr)) {
        Log(TEXT("CLRVector2::setX() Failed to invoked set on managed property X: 0x%08lx"), hr); 
        return;
    }

    return;
}

float CLRVector2::getY()
{
    if (!IsValid()) {
        Log(TEXT("CLRVector2::getY() no managed object attached"));
        return 0.0f;
    }

    variant_t objectRef(GetObjectRef());
    variant_t returnVal;

    HRESULT hr = getYMethod->Invoke_3(objectRef, nullptr, &returnVal);
    if (FAILED(hr)) {
        Log(TEXT("CLRVector2::getY() Failed to invoked get on managed property Y: 0x%08lx"), hr); 
        return 0.0f;
    }

    return returnVal.fltVal;
}

void CLRVector2::setY(float y)
{
    if (!IsValid()) {
        Log(TEXT("CLRVector2::setY() no managed object attached"));
    }

    variant_t objectRef(GetObjectRef());
    variant_t returnVal;
    variant_t val(y);
    SAFEARRAY *args = SafeArrayCreateVector(VT_R4, 0, 1);
    LONG index = 0;
    SafeArrayPutElement(args, &index, &val);

    HRESULT hr = setYMethod->Invoke_3(objectRef, args, &returnVal);
    SafeArrayDestroy(args);

    if (FAILED(hr)) {
        Log(TEXT("CLRVector2::setY() Failed to invoked set on managed property Y: 0x%08lx"), hr); 
        return;
    }

    return;
}