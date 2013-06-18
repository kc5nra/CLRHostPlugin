#pragma once

#include "CLRObject.h"
#include "CLRObjectRef.h"
#include "CLRImageSource.h"
#include "CLRXElement.h"
#include <string>

namespace mscorlib {
    struct _MethodInfo;
}

class CLRImageSourceFactory : public CLRObject
{
protected:
    mscorlib::_MethodInfo *createMethod;
    mscorlib::_MethodInfo *getDisplayNameMethod;
    mscorlib::_MethodInfo *getSourceClassNameMethod;
    mscorlib::_MethodInfo *showConfigurationMethod;

public:
    virtual bool Attach(CLRObjectRef &clrObjectRef, mscorlib::_Type *objectType);
    virtual void Detach();

public:
    CLRImageSource *Create(CLRXElement *data);
    void ShowConfiguration(CLRXElement *data);
    std::wstring GetDisplayName();
    std::wstring GetSourceClassName();
    
};