#pragma once

namespace OBSAPI {
    public interface class ImageSourceFactory
    {
        virtual ImageSource^ Create();
        virtual String^ GetDisplayName();
        virtual String^ GetSourceClassName();
        virtual void ShowConfiguration();
    };
};