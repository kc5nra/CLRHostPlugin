#pragma once

#include "CLRObject.h"
#include <string>

namespace mscorlib {
    struct _MethodInfo;
}

class CLRVector2 : public CLRObject
{
protected:
    mscorlib::_MethodInfo *getXMethod;
    mscorlib::_MethodInfo *setXMethod;
    mscorlib::_MethodInfo *getYMethod;
    mscorlib::_MethodInfo *setYMethod;

public:
    virtual bool Attach(CLRObjectRef &clrObjectRef, mscorlib::_Type *objectType);
    virtual void Detach();
    virtual CLRVector2 *NewInstance(mscorlib::_Type *objectType, float x, float y);

public:
    float getX();
    void setX(float x);
    float getY();
    void setY(float y);

};