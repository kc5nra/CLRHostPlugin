#pragma once

#include "CLRObject.h"
#include "CLRVector2.h"
#include <string>

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
    mscorlib::_MethodInfo *updateSettings;
    mscorlib::_MethodInfo *beginSceneMethod;
    mscorlib::_MethodInfo *endSceneMethod;

public:
    virtual bool Attach(CLRObjectRef &clrObjectRef, mscorlib::_Type *objectType);
    virtual void Detach();

public:
    void Preprocess();
    void Tick(float fSeconds);
    void Render(float x, float y, float width, float height);
    CLRVector2& GetSize();
    void UpdateSettings();
    void BeginScene();
    void EndScene();
};