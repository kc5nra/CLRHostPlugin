// CLRHostInterop.h
#pragma once

#include "CLRHostApi.h"
#include "API.h"
#include "SampleImageSource.h"
#include "SampleImageSourceFactory.h"

using namespace System;

namespace CLRHost {

	public ref class Interop
	{
    public:
        API ^api;

    public:
        Interop(long clrApiPointer) {
            api = gcnew API(reinterpret_cast<CLRHostApi *>(clrApiPointer));
 
            api->AddImageSourceFactory(gcnew SampleImageSourceFactory());
        }
	};
}
