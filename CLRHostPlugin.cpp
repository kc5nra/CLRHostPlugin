/**
 * John Bradley (jrb@turrettech.com)
 */
#include "CLRHostPlugin.h"
#include "Localization.h"
#include "CLRHostApi.h"
#include "CLRHost.h"

HINSTANCE CLRHostPlugin::hinstDLL = NULL;
CLRHostPlugin *CLRHostPlugin::instance = NULL;

CLRHostPlugin::CLRHostPlugin() {
	isDynamicLocale = false;

	if (!locale->HasLookup(KEY("PluginName"))) {
		isDynamicLocale = true;
		int localizationStringCount = sizeof(localizationStrings) / sizeof(CTSTR);
		Log(TEXT("CLR host plugin strings not found, dynamically loading %d strings"), sizeof(localizationStrings) / sizeof(CTSTR));
		for(int i = 0; i < localizationStringCount; i += 2) {
			locale->AddLookupString(localizationStrings[i], localizationStrings[i+1]);
		}
		if (!locale->HasLookup(KEY("PluginName"))) {
			AppWarning(TEXT("Uh oh..., unable to dynamically add our localization keys"));
		}
	}
    clrApi = new CLRHostApi();
    clrHost = new CLRHost(nullptr, clrApi);
    if (clrHost->Initialize()) {
        clrHost->LoadInteropLibrary();
    }
     
}

CLRHostPlugin::~CLRHostPlugin() {
	
	if (isDynamicLocale) {
		int localizationStringCount = sizeof(localizationStrings) / sizeof(CTSTR);
		Log(TEXT("CLR host plugin instance deleted; removing dynamically loaded localization strings"));
		for(int i = 0; i < localizationStringCount; i += 2) {
			locale->RemoveLookupString(localizationStrings[i]);
		}
	}

	isDynamicLocale = false;

    if (clrHost) {
        delete clrHost;
        clrHost = nullptr;
    }

    if (clrApi) {
        delete clrApi;
        clrApi = nullptr;
    }

}

bool LoadPlugin()
{
    if(CLRHostPlugin::instance != NULL)
        return false;
    CLRHostPlugin::instance = new CLRHostPlugin();
    return true;
}

void UnloadPlugin()
{
    if(CLRHostPlugin::instance == NULL)
        return;
    delete CLRHostPlugin::instance;
    CLRHostPlugin::instance = NULL;
}

void OnStartStream()
{
}

void OnStopStream()
{
}

CTSTR GetPluginName()
{
    return STR("PluginName");
}

CTSTR GetPluginDescription()
{
    return STR("PluginDescription");
}

BOOL CALLBACK DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    if(fdwReason == DLL_PROCESS_ATTACH)
        CLRHostPlugin::hinstDLL = hinstDLL;
    return TRUE;
}
