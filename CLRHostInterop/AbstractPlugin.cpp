#include "AbstractPlugin.h"

namespace CLROBS
{
    AbstractPlugin::AbstractPlugin()
    {
        Name = gcnew String("Default Plugin Name");
        Description = gcnew String("Default Plugin Description");
    }

    AbstractPlugin::~AbstractPlugin()
    {}

    String^ AbstractPlugin::Name::get()
    {
        return pluginName;
    }

    void AbstractPlugin::Name::set(String^ pluginName)
    {
        this->pluginName = pluginName;
    }

    String^ AbstractPlugin::Description::get()
    {
        return pluginDescription;
    }

    void AbstractPlugin::Description::set(String^ pluginDescription)
    {
        this->pluginDescription = pluginDescription;
    }
}