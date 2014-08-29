#pragma once

namespace CLROBS
{
    public ref class Vector2
    {
    private:
        float x;
        float y;

    public:
        Vector2(float x, float y)
        {
            this->x = x;
            this->y = y;
        }

        property float X
        {
            float get()
            {
                return this->x;
            }
            void set(float x)
            {
                this->x = x;
            }
        }

        property float Y
        {
            float get()
            {
                return this->y;
            }
            void set(float y)
            {
                this->y = y;
            }
        }
    };
}