#pragma once

#include "CLRObject.h"

namespace mscorlib {
    struct _MethodInfo;
}

class CLRSettingsPane : public CLRObject
{
protected:
    mscorlib::_MethodInfo *createPaneMethod;
    mscorlib::_MethodInfo *destroyPaneMethod;
    mscorlib::_MethodInfo *applySettingsMethod;
    mscorlib::_MethodInfo *cancelSettingsMethod;
    mscorlib::_MethodInfo *hasDefaultsMethod;
    mscorlib::_MethodInfo *setDefaultsMethod;
    // properties
    mscorlib::_MethodInfo *getCategoryMethod;
public:
    virtual bool Attach(CLRObjectRef &clrObjectRef, mscorlib::_Type *objectType);
    virtual void Detach();

private:
    std::wstring category;
public:
    long long CreatePane(long long parentHwnd);
    void DestroyPane();
    void ApplySettings();
    void CancelSettings();
    bool HasDefaults();
    void SetDefaults();
    std::wstring& GetCategory();
};