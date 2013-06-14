#include "AbstractPlugin.h"

AbstractPlugin::AbstractPlugin()
{
    Name = gcnew String("Default Plugin Name");
    Description = gcnew String("Default Plugin Description");
}

AbstractPlugin::~AbstractPlugin()
{
}

API^ AbstractPlugin::Api::get()
{
    return api;
}
void AbstractPlugin::Api::set(API^ api)
{
    this->api = api;
}

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