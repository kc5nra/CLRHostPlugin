// CLRHostInterop.h
#pragma once

#include "CLRHostApi.h"

using namespace System;
using namespace System::Windows::Forms;

namespace CLRHost {

	public ref class Interop
	{
    public:
        CLRHostApi *clrApi;

    public:
        Interop(long clrApiPointer) {
            this->clrApi = reinterpret_cast<CLRHostApi *>(clrApiPointer);
        }
	};
}
