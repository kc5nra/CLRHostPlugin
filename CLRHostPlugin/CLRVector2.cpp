#include "stdafx.h"

#include "CLRVector2.h"

#include "mscorelib.h"

bool CLRVector2::Attach(CLRObjectRef &clrObjectRef, mscorlib::_Type *objectType)
{
    if (CLRObject::Attach(clrObjectRef, objectType)) {
        if (!CLR_GET_METHOD(objectType, "get_X", &getXMethod)) {
            goto errorCleanup;
        }

        if (!CLR_GET_METHOD(objectType, "set_X", &setXMethod)) {
            goto errorCleanup;
        }

        if (!CLR_GET_METHOD(objectType, "get_Y", &getYMethod)) {
            goto errorCleanup;
        }

        if (!CLR_GET_METHOD(objectType, "set_Y", &setYMethod)) {
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
    CLROBJECT_CHECK_VALID_NONVOID(0);

    variant_t objectRef(GetObjectRef());
    variant_t returnVal;

    HRESULT hr = getXMethod->Invoke_3(objectRef, nullptr, &returnVal);
    if (FAILED(hr)) {
        Log(L"CLRVector2::getX() Failed to invoked get on managed "
            L"property Y: 0x%08lx", hr);
        return 0.0f;
    }

    return returnVal.fltVal;
}

void CLRVector2::setX(float x)
{
    CLROBJECT_CHECK_VALID_VOID();

    variant_t objectRef(GetObjectRef());
    variant_t returnVal;
    variant_t val(x);
    SAFEARRAY *args = SafeArrayCreateVector(VT_R4, 0, 1);
    LONG index = 0;
    SafeArrayPutElement(args, &index, &val);

    HRESULT hr = setXMethod->Invoke_3(objectRef, args, &returnVal);
    SafeArrayDestroy(args);

    if (FAILED(hr)) {
        Log(L"CLRVector2::setX() Failed to invoked set on managed "
            L"property X: 0x%08lx", hr);
        return;
    }

    return;
}

float CLRVector2::getY()
{
    CLROBJECT_CHECK_VALID_NONVOID(0);

    variant_t objectRef(GetObjectRef());
    variant_t returnVal;

    HRESULT hr = getYMethod->Invoke_3(objectRef, nullptr, &returnVal);
    if (FAILED(hr)) {
        Log(L"CLRVector2::getY() Failed to invoked get on managed property "
            L"Y: 0x%08lx", hr);
        return 0.0f;
    }

    return returnVal.fltVal;
}

void CLRVector2::setY(float y)
{
    CLROBJECT_CHECK_VALID_VOID();

    variant_t objectRef(GetObjectRef());
    variant_t returnVal;
    variant_t val(y);
    SAFEARRAY *args = SafeArrayCreateVector(VT_R4, 0, 1);
    LONG index = 0;
    SafeArrayPutElement(args, &index, &val);

    HRESULT hr = setYMethod->Invoke_3(objectRef, args, &returnVal);
    SafeArrayDestroy(args);

    if (FAILED(hr)) {
        Log(L"CLRVector2::setY() Failed to invoked set on managed property "
            L"Y: 0x%08lx", hr);
        return;
    }

    return;
}