#include "CLRXElement.h"

#include <metahost.h> 
#include <string>

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

CLRXElement * CLRXElement::Create(_Type *type, void *elementPointer)
{
    type->AddRef();

    // Release
    SAFEARRAY *constructors = nullptr;
    _ConstructorInfo **constructorInfos = nullptr;
    _ConstructorInfo *constructorInfo = nullptr;
    SAFEARRAY *constructorParameters = nullptr;
    CLRXElement *element = nullptr;
    
    // Local
    HRESULT hr;
    LONG index = 0;
    
    variant_t elementRef((long long) elementPointer);
    variant_t instance;
    
    hr = type->GetConstructors_2(&constructors);
    if (FAILED(hr) || !constructors || constructors->rgsabound->cElements != 2) {
        Log(TEXT("CLRXElement::Create() failed to retrieve constructors from managed XElement type: 0x%08lx"), hr); 
        goto errorCleanup;
    }
    
    constructorInfos = (_ConstructorInfo **)constructors->pvData;
    constructorInfo = constructorInfos[1];
    constructorInfo->AddRef();
    SafeArrayDestroy(constructors);
    
    constructorParameters = SafeArrayCreateVector(VT_VARIANT, 0, 1);
    hr = SafeArrayPutElement(constructorParameters, &index, &elementRef);
    
    if (FAILED(hr)) {
        Log(TEXT("CLRXElement::Create() failed to set constructor argument: 0x%08lx"), hr); 
        goto errorCleanup;
    }
    hr = constructorInfo->Invoke_5(constructorParameters, &instance);
    if (FAILED(hr) || !instance.punkVal) {
        Log(TEXT("CLRXElement::Create() failed invoke XElement constructor: 0x%08lx"), hr); 
        goto errorCleanup;
    }
    
    SafeArrayDestroy(constructorParameters);
    constructorParameters = nullptr;
    constructorInfos = nullptr;
    constructorInfo->Release();
    constructorInfo = nullptr;

    element = new CLRXElement();
    if (!element->Attach(CLRObjectRef(instance.punkVal, nullptr), type)) {
        Log(TEXT("CLRXElement::Create() failed to attach to managed XElement instance"), hr); 
        goto errorCleanup;
    }

    goto success;

errorCleanup:
    if (constructors) {
        SafeArrayDestroy(constructors);
        constructors = nullptr;
    }
    if (constructorInfo) {
        constructorInfo->Release();
        constructorInfo = nullptr;
    }
    if (constructorParameters) {
        SafeArrayDestroy(constructorParameters);
        constructorParameters = nullptr;
    }
    if (element) {
        delete element;
        element = nullptr;
    }
    return nullptr;

success:
    return element;
}