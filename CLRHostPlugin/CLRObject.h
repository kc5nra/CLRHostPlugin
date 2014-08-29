#pragma once

#include "CLRObjectRef.h"

namespace mscorlib
{
    struct _Type;
}

struct IUnknown;

#define CLROBJECT_CHECK_VALID_VOID() \
if (!IsValid()) { \
    Log(L"%s no managed object attached", __FUNCSIG__); \
    return; \
}

#define CLROBJECT_CHECK_VALID_NONVOID(returnVal) \
if (!IsValid()) { \
    Log(L"%s no managed object attached", __FUNCSIG__); \
    return returnVal; \
}

class CLRObject
{
private:
    IUnknown *objectRef;
    mscorlib::_Type *objectType;

public:
    virtual ~CLRObject();

public:
    virtual bool Attach(CLRObjectRef &clrObjectRef, mscorlib::_Type *objectType);
    virtual void Detach();
    virtual bool IsValid()
    {
        return (objectRef != nullptr && objectType != nullptr);
    }

public:
    IUnknown *GetObjectRef()
    {
        return objectRef;
    }
    mscorlib::_Type *GetObjectType()
    {
        return objectType;
    }
};