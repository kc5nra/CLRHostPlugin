using namespace OBS;
using namespace System;

public ref class MyPlugin : public Plugin {
private:
    API^ api;

public:
    MyPlugin(API^ api)
    {
        this->api = api;
    }

    virtual bool LoadPlugin()
    {
		api->AddImageSourceFactory(
        return true;
    }

    virtual void UnloadPlugin()
    {

    }

    virtual void OnStartStream()
    {

    }

    virtual void OnStopStream()
    {
    }

    virtual String^ GetPluginName()
    {
        return gcnew String("Sample Plugin Name");
    }

    virtual String ^GetPluginDescription()
    {
        return gcnew String("Sample Plugin Description");
    }

};

