#pragma once
#include "OBSApi.h"
#include "CLRHost.h"
class CLRSettingsPane : public SettingsPane
{
public:
    CLRSettingsPane(CLRHost *clrHost);
};