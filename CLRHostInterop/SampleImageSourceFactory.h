#pragma once

#include "ImageSourceFactory.h"

public ref class SampleImageSourceFactory : public ImageSourceFactory
{
public:
    virtual ImageSource^ Create()
    {
        return nullptr;
    }
    virtual String^ GetDisplayName()
    {
        return "Sample ImageSourceFactory";
    }
    virtual String^ GetSourceClassName()
    {
        return "SampleImageSourceFactory";
    }

    virtual void ShowConfiguration()
    {
    }
};