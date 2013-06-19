#include "AbstractImageSourceFactory.h"

#define WS_CHILD    0x40000000L
#define WS_VISIBLE  0x10000000L

AbstractImageSourceFactory::AbstractImageSourceFactory()
{
    this->ClassName = gcnew String("DefaultImageSourceClassName");
    this->DisplayName = gcnew String("DefaultImageSourceDisplayName");
}

String^ AbstractImageSourceFactory::ClassName::get()
{
    return className;
}

void AbstractImageSourceFactory::ClassName::set(String^ className)
{
    this->className = className;
}

String^ AbstractImageSourceFactory::DisplayName::get()
{
    return displayName;
}

void AbstractImageSourceFactory::DisplayName::set(String^ displayName)
{
    this->displayName = displayName;
}