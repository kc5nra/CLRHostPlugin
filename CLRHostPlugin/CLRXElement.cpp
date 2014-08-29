#include "stdafx.h"

#include "CLRXElement.h"

#include "mscorelib.h"

CLRXElement * CLRXElement::Create(
    mscorlib::_Type *type,
    void *elementPointer)
{
    type->AddRef();

    // Release
    SAFEARRAY *constructors = nullptr;
    mscorlib::_ConstructorInfo **constructorInfos = nullptr;
    mscorlib::_ConstructorInfo *constructorInfo = nullptr;
    SAFEARRAY *constructorParameters = nullptr;
    CLRXElement *element = nullptr;

    // Local
    HRESULT hr;
    LONG index = 0;

    variant_t elementRef((long long) elementPointer);
    variant_t instance;

    hr = type->GetConstructors_2(&constructors);
    if (FAILED(hr) ||
        !constructors || constructors->rgsabound->cElements != 2)
    {
        Log(L"CLRXElement::Create() failed to retrieve constructors from "
            L"managed XElement type: 0x%08lx", hr);
        goto errorCleanup;
    }

    constructorInfos = (mscorlib::_ConstructorInfo **) constructors->pvData;
    constructorInfo = constructorInfos[1];
    constructorInfo->AddRef();
    SafeArrayDestroy(constructors);

    constructorParameters = SafeArrayCreateVector(VT_VARIANT, 0, 1);
    hr = SafeArrayPutElement(constructorParameters, &index, &elementRef);

    if (FAILED(hr)) {
        Log(L"CLRXElement::Create() failed to set constructor argument: "
            L"0x%08lx", hr);
        goto errorCleanup;
    }
    hr = constructorInfo->Invoke_5(constructorParameters, &instance);
    if (FAILED(hr) || !instance.punkVal) {
        Log(L"CLRXElement::Create() failed invoke XElement constructor: "
            L"0x%08lx", hr);
        goto errorCleanup;
    }

    SafeArrayDestroy(constructorParameters);
    constructorParameters = nullptr;
    constructorInfos = nullptr;
    constructorInfo->Release();
    constructorInfo = nullptr;

    element = new CLRXElement();
    if (!element->Attach(CLRObjectRef(instance.punkVal, nullptr), type)) {
        Log(L"CLRXElement::Create() failed to attach to managed XElement "
            L"instance", hr);
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