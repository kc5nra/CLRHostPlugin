#include "OBSApi.h"
#include "CLRSettingsPane.h"

class SettingsPaneBridge : public SettingsPane
{
private:
    CLRSettingsPane *clrSettingsPane;

public:
    SettingsPaneBridge(CLRSettingsPane *clrSettingsPane)
    {
        this->clrSettingsPane = clrSettingsPane;
    }

    ~SettingsPaneBridge()
    {
        delete clrSettingsPane;
    }

    virtual CTSTR GetCategory() const
    {
        return clrSettingsPane->GetCategory().c_str();
    }

    virtual HWND CreatePane(HWND parentHwnd)
    {
        return reinterpret_cast<HWND>(clrSettingsPane->CreatePane((long long) parentHwnd));
    }

    virtual void DestroyPane()
    {
        clrSettingsPane->DestroyPane();
    }

    virtual INT_PTR ProcMessage(UINT message, WPARAM wParam, LPARAM lParam)
    {
        return 0;
    }

    virtual void ApplySettings()
    {
        clrSettingsPane->ApplySettings();
    }

    virtual void CancelSettings()
    {
        clrSettingsPane->CancelSettings();
    }

    virtual bool HasDefaults() const
    {
        return clrSettingsPane->HasDefaults();
    }

    virtual void SetDefaults()
    {
        clrSettingsPane->SetDefaults();
    }
};