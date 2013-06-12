#pragma once

#include "Vector2.h"

namespace OBSAPI {
    public interface class ImageSource
    {
        virtual void Preprocess() = 0;
        virtual void Tick(float fSeconds) = 0;
        virtual void Render(Vector2^ position, Vector2^ size) = 0;
        virtual Vector2^ GetSize() = 0;
        virtual void UpdateSettings();
        virtual void BeginScene();
        virtual void EndScene();
    };
};