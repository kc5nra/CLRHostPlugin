#pragma once

#include <string>
#include <map>

#include "CLRApiCommon.h"
#include "CLRObjectRef.h"
#include "CLRImageSourceFactory.h"

class CLR_API GSTexture
{
private:
    void *gsTexture;
    void *d3dTexture;
public:
    GSTexture(void *gsTexture, void *d3dTexture)
    {
        this->gsTexture = gsTexture;
        this->d3dTexture = d3dTexture;
    }

public:
    void FreeTexture() { delete gsTexture; }

public:
    void *GetGSTexture() { return gsTexture; }
    void *GetD3DTexture() { return d3dTexture; }


};

class CLRHostApi 
{
private:
    std::map<std::wstring, CLRImageSourceFactory *> imageSourceFactories;
public:
    ~CLRHostApi();
public:
    CLR_API void CLRLog(std::wstring &logMessage);
    CLR_API void AddSettingsPane(CLRObjectRef &clrObjectReference);
    CLR_API void AddImageSourceFactory(CLRObjectRef &clrObjectReference);
	CLR_API GSTexture SimpleCreateDynamicTexture(int width, int height, int colorFormat, bool isBuildingMipMaps);

public:
    std::map<std::wstring, CLRImageSourceFactory *> &GetImageSourceFactories() { return imageSourceFactories; }
};