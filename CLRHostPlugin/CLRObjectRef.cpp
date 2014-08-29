#include "stdafx.h"

#include "CLRobjectRef.h"

CLRObjectRef::CLRObjectRef()
{
    this->objectRef = nullptr;
    this->typeRef = nullptr;
}

CLRObjectRef::CLRObjectRef(void *objectRef, void *typeRef)
{
    this->objectRef = objectRef;
    this->typeRef = typeRef;
}