#include "OBSApi.h"

#include "CLRImageSource.h"
#include "CLRVector2.h"

class ImageSourceBridge : public ImageSource
{
private:
    CLRImageSource *clrImageSource;

public:
    ImageSourceBridge(CLRImageSource *clrImageSource)
    {
        this->clrImageSource = clrImageSource;
    }

    ~ImageSourceBridge()
    {
        delete clrImageSource;
    }

    virtual void Preprocess()
    {
        clrImageSource->Preprocess();
    }

    virtual void Tick(float fSeconds)
    {
        clrImageSource->Tick(fSeconds);
    }

    virtual void Render(const Vect2 &pos, const Vect2 &size)
    {
        clrImageSource->Render(pos.x, pos.y, size.x, size.y);
    }

    virtual Vect2 GetSize() const
    {
        CLRVector2 *size = clrImageSource->GetSize();
        Vect2 vectSize(size->getX(), size->getY());
        delete size;
        return vectSize;
    }

    virtual void UpdateSettings()
    {
        clrImageSource->UpdateSettings();
    }

    virtual void BeginScene()
    {
        clrImageSource->BeginScene();
    }

    virtual void EndScene()
    {
        clrImageSource->EndScene();
    }
};