/**
* John Bradley (jrb@turrettech.com)
*/
#pragma once

#define STR_PREFIX L"Plugins.CLRHost."
#define KEY(k) (STR_PREFIX L ## k)
#define STR(text) locale->LookupString(KEY(text))

#ifndef CHP_VERSION
#define CHP_VERSION L" !INTERNAL VERSION!"
#endif

static CTSTR localizationStrings [] = {
    KEY("PluginName"), L"CLR Host Plugin",
    KEY("PluginDescription"), L"Allows plugins to be written in any CLR language\n\n"
    L"Plugin Version: " CHP_VERSION,
};
