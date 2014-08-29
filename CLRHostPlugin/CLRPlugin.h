#pragma once

#include "CLRObject.h"
#include "CLRObjectRef.h"

#include <string>

namespace mscorlib {
    struct _EventInfo;
    struct _MethodInfo;
}

class CLRPlugin : public CLRObject
{
protected:
    mscorlib::_MethodInfo *loadPluginMethod;
    mscorlib::_MethodInfo *unloadPluginMethod;
    mscorlib::_MethodInfo *onStartStreamMethod;
    mscorlib::_MethodInfo *onStopStreamMethod;
    mscorlib::_MethodInfo *getPluginNameMethod;
    mscorlib::_MethodInfo *getPluginDescriptionMethod;

public:
    virtual bool Attach(CLRObjectRef &clrObjectRef, mscorlib::_Type *objectType);
    virtual void Detach();

public:
    bool LoadPlugin();
    void UnloadPlugin();
    void OnStartStream();
    void OnStopStream();
    std::wstring GetPluginName();
    std::wstring GetPluginDescription();
};