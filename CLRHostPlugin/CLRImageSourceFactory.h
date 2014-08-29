#pragma once

#include "CLRObject.h"
#include "CLRObjectRef.h"

class CLRXElement;
class CLRImageSource;

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
    bool ShowConfiguration(CLRXElement *data);
    std::wstring GetDisplayName();
    std::wstring GetSourceClassName();
    
};