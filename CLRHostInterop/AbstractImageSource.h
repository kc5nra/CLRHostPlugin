#pragma once

#include "ImageSource.h"
#include "API.h"
#include "GraphicsSystem.h"

namespace CLROBS
{
    public ref class AbstractImageSource abstract : public ImageSource
    {
    private:
        Vector2^ size;
    public:

        AbstractImageSource();

        virtual void Render(float x, float y, float width, float height)
            abstract;

        virtual void UpdateSettings() = 0;

        property Vector2^ Size
        {
            virtual Vector2^ get() sealed;
            virtual void set(Vector2^ size) sealed;
        }

        virtual void Preprocess();
        virtual void Tick(float fSeconds);
        virtual void BeginScene();
        virtual void EndScene();

    protected:

        /// Convenience API property
        property API^ Api
        {
            API^ get()
            {
                return API::Instance;
            }
        }

        /// Convenience GraphicsSystem property
        property GraphicsSystem^ GS
        {
            GraphicsSystem^ get()
            {
                return GraphicsSystem::Instance;
            }
        }
    };
};
