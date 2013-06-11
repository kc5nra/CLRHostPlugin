#pragma once

#include <windows.h>
#include <string>

#include <comutil.h>

#include "CLRHostApi.h"

struct ICLRMetaHost;
struct ICLRRuntimeInfo;
struct ICLRRuntimeHost;
struct ICorRuntimeHost;


namespace mscorlib {
    struct _Assembly;
    struct _Type;
}

#define INTEROP_PATH            TEXT("plugins\\CLRHostPlugin\\")
#define INTEROP_ASSEMBLY        TEXT("CLRHostInterop.dll")
#define INTEROP_ASSEMBLY_PATH   INTEROP_PATH INTEROP_ASSEMBLY
#define INTEROP_LOAD_CLASS      TEXT("CLRHost.Interop")

class CLRHost {

private:

    CLRHostApi *clrApi;

    ICLRMetaHost *clrMetaHost;
    ICLRRuntimeInfo *clrRuntimeInfo;
    ICorRuntimeHost* corRuntimeHost;

    mscorlib::_Assembly *libraryAssembly;
    mscorlib::_Type *libraryType;
    variant_t libraryInstance;

    TCHAR *clrRuntimeVersion;

    bool isInitialized;
    bool isLibraryLoaded;
    
public:
    CLRHost::CLRHost(TCHAR *clrRuntimeVersion, CLRHostApi *clrApi);
    ~CLRHost();

public:
    bool Initialize();
    bool LoadInteropLibrary();
};