#include "OBSApi.h"
#include "CLRImageSource.h"

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
};