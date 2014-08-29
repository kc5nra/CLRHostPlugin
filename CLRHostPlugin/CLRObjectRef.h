#pragma once

#include "CLRApiCommon.h"

#include <string>

class CLR_API CLRObjectRef
{
private:
    void *objectRef;
    void *typeRef;
public:
    CLRObjectRef();
    CLRObjectRef(void *objectRef, void *typeRef);

public:
    void *GetObjectRef()
    {
        return objectRef;
    }
    void *GetTypeRef()
    {
        return typeRef;
    }

    bool isObjectRefNull()
    {
        return objectRef == nullptr;
    }
    bool isTypeRefNull()
    {
        return typeRef == nullptr;
    }
};