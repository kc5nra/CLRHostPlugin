#include "ImageSource.h"

public ref class SampleImageSource : public ImageSource
{
public:
    virtual void Preprocess()
    {
    }
    virtual void Tick(float fSeconds)
    {
    }
    virtual void Render(Vector2^ position, Vector2^ size)
    {
    }
    virtual Vector2^ GetSize()
    {
        return gcnew Vector2(5.0f, 5.5f);
    }
    virtual void UpdateSettings()
    {
    }
    virtual void BeginScene()
    {
    }
    virtual void EndScene()
    {
    }
};