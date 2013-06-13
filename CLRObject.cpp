#include "CLRObject.h"

#include <metahost.h> 
#include <string>
#include <vector>

#pragma comment(lib, "mscoree.lib") 
#import "mscorlib.tlb" raw_interfaces_only high_property_prefixes("_get","_put","_putref") rename("ReportEvent", "InteropServices_ReportEvent") 
using namespace mscorlib; 

void __cdecl Log(const TCHAR *format, ...);
void __cdecl CrashError(const TCHAR *format, ...);

#ifndef assert
#ifdef _DEBUG
#define assert(check) if(!(check)) CrashError(TEXT("Assertion Failiure: (") TEXT(#check) TEXT(") failed\r\nFile: %s, line %d"), TEXT(__FILE__), __LINE__);
#else
#define assert(check)
#endif
#endif

CLRObject::~CLRObject() {
    Detach();
}

bool CLRObject::Attach(CLRObjectRef &clrObjectRef, mscorlib::_Type *objectType)
{
    this->objectRef = (IUnknown *)clrObjectRef.GetObjectRef();
    this->objectType = objectType;

    objectRef->AddRef();
    objectType->AddRef();
    return true;
}

void CLRObject::Detach()
{
    if (objectRef) {
        objectRef->Release();
        objectRef = nullptr;
    }
    if (objectType) {
        objectType->Release();
        objectType = nullptr;
    }
}
