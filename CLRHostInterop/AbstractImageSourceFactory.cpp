#include "AbstractImageSourceFactory.h"

namespace CLROBS
{
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
}