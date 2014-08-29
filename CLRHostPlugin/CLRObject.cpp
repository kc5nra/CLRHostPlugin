#include "stdafx.h"

#include "CLRObject.h"

#include "mscorelib.h"

CLRObject::~CLRObject()
{
    if (objectType && objectRef) {
        mscorlib::IDisposable *disposable;
        HRESULT hr = objectRef->QueryInterface(&disposable);
        if (SUCCEEDED(hr) && disposable) {
            disposable->Dispose();
            disposable->Release();
        }
    }
    Detach();
}

bool CLRObject::Attach(CLRObjectRef &clrObjectRef, mscorlib::_Type *objectType)
{
    this->objectRef = (IUnknown *) clrObjectRef.GetObjectRef();
    this->objectType = objectType;

    objectRef->AddRef();
    objectType->AddRef();
    return true;
}

void CLRObject::Detach()
{
    if (objectRef) {
        objectRef->Release();
        objectRef = nullptr;
    }
    if (objectType) {
        objectType->Release();
        objectType = nullptr;
    }
}