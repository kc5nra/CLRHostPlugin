#pragma once

#include "CLRObject.h"
#include <string>

namespace mscorlib {
    struct _Type;
    struct _MethodInfo;
}

class CLRXElement : public CLRObject
{
public:
    static CLRXElement *Create(mscorlib::_Type *type, void *element);

};