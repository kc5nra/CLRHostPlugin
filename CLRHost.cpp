#include "CLRHost.h"

#include "CLRHostApi.h"

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

CLRHost::CLRHost(TCHAR *clrRuntimeVersion, CLRHostApi *clrApi) 
{
    clrMetaHost = nullptr;
    clrRuntimeInfo = nullptr;
    corRuntimeHost = nullptr;
    this->clrRuntimeVersion = clrRuntimeVersion;
    isInitialized = false;
    isLibraryLoaded = false;
    this->clrApi = clrApi;

}

CLRHost::~CLRHost()
{
    if (isInitialized) {
        
        corRuntimeHost->Stop();

        if (clrMetaHost) { 
            clrMetaHost->Release(); 
            clrMetaHost = nullptr; 
        } 
        if (clrRuntimeInfo) { 
            clrRuntimeInfo->Release(); 
            clrRuntimeInfo = nullptr; 
        } 
        if (corRuntimeHost) { 
            corRuntimeHost->Release(); 
            corRuntimeHost = nullptr; 
        }
    }
    if (isLibraryLoaded) {
        if (libraryAssembly) {
            libraryAssembly->Release();
            libraryAssembly = nullptr;
        }
        if (libraryType) {
            libraryType->Release();
            libraryType = nullptr;
        }
        if (imageSourceType) {
            imageSourceType->Release();
            imageSourceType = nullptr;
        }
        if (imageSourceFactoryType) {
            imageSourceFactoryType->Release();
            imageSourceFactoryType = nullptr;
        }
        if (settingsPaneType) {
            settingsPaneType->Release();
            settingsPaneType = nullptr;
        }
        if (libraryInstance.punkVal) {
            libraryInstance.punkVal->Release();
        }
    }
}

HRESULT GetInstalledClrRuntimes(ICLRMetaHost *clrMetaHost, std::vector<std::wstring>& clrRuntimeList)
{
    HRESULT hr = S_OK;		
    clrRuntimeList.clear();

    IEnumUnknown* runtimeEnumerator = nullptr;
    hr = clrMetaHost->EnumerateInstalledRuntimes(&runtimeEnumerator);
    if (SUCCEEDED(hr)) {
        WCHAR currentRuntime[50];
        DWORD bufferSize = ARRAYSIZE(currentRuntime);
        IUnknown* runtime = nullptr;
        while (runtimeEnumerator->Next(1, &runtime, NULL) == S_OK)
        {
            ICLRRuntimeInfo* runtimeInfo = nullptr;
            hr = runtime->QueryInterface(IID_PPV_ARGS(&runtimeInfo));
            if (SUCCEEDED(hr))
            {
                hr = runtimeInfo->GetVersionString(currentRuntime, &bufferSize);
                if (SUCCEEDED(hr))
                {
                    clrRuntimeList.push_back(std::wstring(currentRuntime));
                }
                runtimeInfo->Release();
            }
            runtime->Release();
        }
        runtimeEnumerator->Release();
        hr = S_OK;
    }

    return hr;
}

bool CLRHost::Initialize() 
{
    assert(!isInitialized);

    HRESULT hr; 
    std::vector<std::wstring> clrRuntimeList;

    Log(TEXT("CLRHost::Initialize() Load and start the .NET runtime %s"), clrRuntimeVersion);

    hr = CLRCreateInstance(CLSID_CLRMetaHost, IID_PPV_ARGS(&clrMetaHost)); 
    if (FAILED(hr)) { 
        Log(TEXT("CLRCreateInstance failed: 0x%08lx"), hr); 
        goto errorCleanup; 
    } 

    if (clrRuntimeVersion) {
        hr = clrMetaHost->GetRuntime(clrRuntimeVersion, IID_PPV_ARGS(&clrRuntimeInfo)); 
        if (FAILED(hr)) { 
            Log(TEXT("ICLRMetaHost::GetRuntime(%s) failed: 0x%08lx"), clrRuntimeVersion, hr); 
        }
    }
    
    if (!clrRuntimeInfo) {
        hr = GetInstalledClrRuntimes(clrMetaHost, clrRuntimeList);
        if (SUCCEEDED(hr)) {
            if (clrRuntimeList.size()) {
                std::wstring version = *(clrRuntimeList.end() - 1);
                Log(TEXT("Attempting to use %s .NET runtime"), version.c_str());

                hr = clrMetaHost->GetRuntime(version.c_str(), IID_PPV_ARGS(&clrRuntimeInfo)); 
                if (FAILED(hr)) { 
                    Log(TEXT("ICLRMetaHost::GetRuntime(%s) failed: 0x%08lx"), version.c_str(), hr); 
                    goto errorCleanup; 
                }
            } else {
                Log(TEXT("No .NET Runtimes found!"));
                goto errorCleanup;
            }
        } else {
            Log(TEXT("CLRHost::GetInstalledClrRuntimes) failed: 0x%08lx"), hr); 
            goto errorCleanup;
        }
    }

    BOOL isLoadable; 
    hr = clrRuntimeInfo->IsLoadable(&isLoadable); 
    if (FAILED(hr)) { 
        Log(TEXT("ICLRRuntimeInfo::IsLoadable() failed: 0x%08lx"), hr); 
        goto errorCleanup; 
    } 

    if (!isLoadable) { 
        Log(TEXT(".NET runtime %s cannot be loaded"), clrRuntimeVersion); 
        goto errorCleanup; 
    } 
    
    hr = clrRuntimeInfo->GetInterface(CLSID_CorRuntimeHost, IID_ICorRuntimeHost, (LPVOID *)&corRuntimeHost);
    if (FAILED(hr)) { 
         Log(TEXT("ICLRRuntimeInfo::GetInterface() failed when retrieving ICorRuntimeHost instance: 0x%08lx"), hr); 
        goto errorCleanup; 
    }

    // Start the CLR. 
    hr = corRuntimeHost->Start(); 
    if (FAILED(hr)) { 
        Log(TEXT("ICorRuntimeHost::Start() failed: 0x%08lx"), hr); 
        goto errorCleanup; 
    }

    isInitialized = true;
    goto success;

errorCleanup: 

    if (clrMetaHost) { 
        clrMetaHost->Release(); 
        clrMetaHost = nullptr; 
    } 
    if (clrRuntimeInfo) { 
        clrRuntimeInfo->Release(); 
        clrRuntimeInfo = nullptr; 
    } 
    if (corRuntimeHost) {
        corRuntimeHost->Release();
        corRuntimeHost = nullptr;
    }

success:
    return isInitialized; 
}

bool CLRHost::LoadInteropLibrary() 
{
    assert(isInitialized);

    HRESULT hr;
    
    IUnknown *appDomainSetupUnknown;
    IAppDomainSetup *appDomainSetup;
    IUnknown *appDomainUnknown;
    _AppDomain *appDomain;

    bstr_t bstrPluginPath(INTEROP_PATH);
    bstr_t isShadowCopyFiles("true");
    bstr_t interopAssemblyName(INTEROP_ASSEMBLY);

    bstr_t assemblyClassName("CLRHost.Interop");
    bstr_t imageSourceTypeName("OBSAPI.ImageSource");
    bstr_t imageSourceFactoryTypeName("OBSAPI.ImageSourceFactory");
    bstr_t settingsPaneTypeName("OBSAPI.SettingsPane");

    
    // The static method in the .NET class to invoke. 
    SAFEARRAY *apiArgs = NULL; 
    LONG argIndex;
    variant_t clrApiPtr((long)clrApi);

    hr = corRuntimeHost->CreateDomainSetup(&appDomainSetupUnknown);
    if (FAILED(hr)) {
        Log(TEXT("ICorRuntimeHost::CreateDomainSetup() failed: 0x%08lx"), hr);
        goto errorCleanup;
    }

    hr = appDomainSetupUnknown->QueryInterface( __uuidof( mscorlib::IAppDomainSetup), (void**)&appDomainSetup);
    if (FAILED(hr)) {
        Log(TEXT("IAppDomainSetup::QueryInterface() failed: 0x%08lx"), hr);
        goto errorCleanup;
    }
    
    hr = appDomainSetup->put_ApplicationBase(bstrPluginPath);
    if (FAILED(hr)) {
        Log(TEXT("IAppDomainSetup::put_ApplicationBase(%s) failed: 0x%08lx"), INTEROP_PATH, hr);
        goto errorCleanup;
    }
    hr = appDomainSetup->put_ShadowCopyFiles(isShadowCopyFiles);
    if (FAILED(hr)) {
        Log(TEXT("IAppDomainSetup::put_ShadowCopyFiles(%s) failed: 0x%08lx"), TEXT("TRUE"), hr);
        goto errorCleanup;
    }
    hr = appDomainSetup->put_ApplicationName(interopAssemblyName);
    if (FAILED(hr)) {
        Log(TEXT("IAppDomainSetup::put_ApplicationName(%s) failed: 0x%08lx"), INTEROP_ASSEMBLY, hr);
        goto errorCleanup;
    }
 
    
    hr = corRuntimeHost->CreateDomainEx(interopAssemblyName, appDomainSetup, nullptr, &appDomainUnknown);
    if (FAILED(hr)) {
        Log(TEXT("ICorRuntimeHost::CreateDomainEx(%s, ...) failed: 0x%08lx"), INTEROP_ASSEMBLY, hr);
        goto errorCleanup;
    }
    
    appDomainSetup->Release();
    appDomainSetup = nullptr;
    
    // Obtain the actual AppDomain object..
    hr = appDomainUnknown->QueryInterface(__uuidof( mscorlib::_AppDomain ), (void**)&appDomain);
    if (FAILED(hr)) {
        Log(TEXT("IAppDomain::QueryInterface(%s, ...) failed: 0x%08lx"), hr);
        goto errorCleanup;
    }
    appDomainUnknown->Release();
    appDomainUnknown = nullptr;

    // Load the .NET assembly. 
    Log(TEXT("Load the assembly %s"), INTEROP_ASSEMBLY_PATH); 
    hr = appDomain->Load_2(assemblyClassName, &libraryAssembly);
    if (FAILED(hr)) { 
        Log(TEXT("Failed to load the assembly: 0x%08lx"), hr); 
        goto errorCleanup;
    }

    hr = libraryAssembly->GetType_2(assemblyClassName, &libraryType);
    if (FAILED(hr)) {
        Log(TEXT("Failed to get type definition of interop library class: 0x%08lx"), hr); 
        goto errorCleanup;
    }
    
    hr = libraryAssembly->GetType_2(imageSourceTypeName, &imageSourceType);
    if (FAILED(hr)) {
        Log(TEXT("Failed to get type definition of %s class: 0x%08lx"), imageSourceTypeName.GetAddress(), hr); 
        goto errorCleanup;
    }

    hr = libraryAssembly->GetType_2(imageSourceFactoryTypeName, &imageSourceFactoryType);
    if (FAILED(hr)) {
        Log(TEXT("Failed to get type definition of interop library class: 0x%08lx"), hr); 
        goto errorCleanup;
    }

    hr = libraryAssembly->GetType_2(settingsPaneTypeName, &settingsPaneType);
    if (FAILED(hr)) {
        Log(TEXT("Failed to get type definition of interop library class: 0x%08lx"), hr); 
        goto errorCleanup;
    }

    apiArgs = SafeArrayCreateVector(VT_VARIANT, 0, 1);
    argIndex = 0;

    hr = SafeArrayPutElement(apiArgs, &argIndex, &clrApiPtr); 
    if (FAILED(hr)) 
    { 
        wprintf(L"SafeArrayPutElement failed w/hr 0x%08lx\n", hr); 
        goto errorCleanup; 
    }

    // Create instaoce of the 'Main' class object..
    hr = libraryAssembly->CreateInstance_3(assemblyClassName, false, BindingFlags_Default, nullptr, apiArgs, nullptr, nullptr, &libraryInstance);
    if (FAILED(hr)) {
        Log(TEXT("Failed to instantiate our interop library class: 0x%08lx"), hr); 
        goto errorCleanup;
    }

    SafeArrayDestroy(apiArgs);
    apiArgs = nullptr;

    isLibraryLoaded = true;
    goto success;

errorCleanup:
    if (appDomainSetup) {
        appDomainSetup->Release();
        appDomainSetup = nullptr;
    }
    if (appDomainUnknown) {
        appDomainUnknown->Release();
        appDomainUnknown = nullptr;
    }
    if (appDomain) {
        appDomain->Release();
        appDomain = nullptr;
    }
    if (libraryAssembly) {
        libraryAssembly->Release();
        libraryAssembly = nullptr;
    }
    if (libraryType) {
        libraryType->Release();
        libraryType = nullptr;
    }
    if (imageSourceType) {
        imageSourceType->Release();
        imageSourceType = nullptr;
    }
    if (imageSourceFactoryType) {
        imageSourceFactoryType->Release();
        imageSourceFactoryType = nullptr;
    }
    if (settingsPaneType) {
        settingsPaneType->Release();
        settingsPaneType = nullptr;
    }
    if (apiArgs) {
        SafeArrayDestroy(apiArgs);
    }
success:
    return true;
}