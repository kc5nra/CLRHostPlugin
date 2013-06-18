#pragma once

#include "Vector2.h"
#include "XConfig.h"

namespace CLROBS {
    public interface class ImageSource
    {
        virtual void Preprocess();
        virtual void Tick(float fSeconds);
        virtual void Render(float x, float y, float width, float height);
        virtual Vector2^ GetSize();
        virtual void UpdateSettings();
        virtual void BeginScene() ;
        virtual void EndScene();
    };
};