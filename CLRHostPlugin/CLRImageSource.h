#pragma once

#include "CLRObject.h"

class CLRVector2;

namespace mscorlib {
    struct _MethodInfo;
}

class CLRImageSource : public CLRObject
{
protected:
    mscorlib::_MethodInfo *preprocessMethod;
    mscorlib::_MethodInfo *tickMethod;
    mscorlib::_MethodInfo *renderMethod;
    mscorlib::_MethodInfo *getSizeMethod;
    mscorlib::_MethodInfo *updateSettingsMethod;
    mscorlib::_MethodInfo *beginSceneMethod;
    mscorlib::_MethodInfo *endSceneMethod;

public:
    virtual bool Attach(CLRObjectRef &clrObjectRef, mscorlib::_Type *objectType);
    virtual void Detach();

public:
    void Preprocess();
    void Tick(float fSeconds);
    void Render(float x, float y, float width, float height);
    CLRVector2 *GetSize();
    void UpdateSettings();
    void BeginScene();
    void EndScene();
};