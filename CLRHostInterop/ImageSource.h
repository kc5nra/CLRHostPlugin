#pragma once

#include "Vector2.h"
#include "XElement.h"

namespace CLROBS
{
    public interface class ImageSource
    {
        virtual void Preprocess();
        virtual void Tick(float seconds);
        virtual void Render(float x, float y, float width, float height);

        property Vector2^ Size
        {
            virtual Vector2^ get();
            virtual void set(Vector2^ size);
        }

        virtual void UpdateSettings();
        virtual void BeginScene();
        virtual void EndScene();
    };
};