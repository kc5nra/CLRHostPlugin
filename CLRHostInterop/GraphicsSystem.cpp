#include "OBSApi.h"
#include "GraphicsSystem.h"
#include <d3d10.h>

namespace CLROBS
{
    Texture::Texture(::Texture *texture)
    {
        this->texture = texture;
    }

    Texture::Texture(System::IntPtr texture)
    {
        this->texture = (::Texture *)(texture.ToPointer());
    }

    Texture::~Texture()
    {
        delete texture;
    }

    void Texture::SetImage(
        System::IntPtr data,
        GSImageFormat imageFormat,
        unsigned int pitch)
    {
        texture->SetImage(data.ToPointer(),
            static_cast<::GSImageFormat>(imageFormat), pitch);
    }

    void Texture::SetImage(
        array<System::Byte>^ data,
        GSImageFormat imageFormat,
        unsigned int pitch)
    {
        pin_ptr<unsigned char> dataPtr = &data[0];
        texture->SetImage(dataPtr,
            static_cast<::GSImageFormat>(imageFormat), pitch);
    }

    GSColorFormat Texture::Format::get()
    {
        return static_cast<GSColorFormat>(texture->GetFormat());
    }

    unsigned int Texture::Width::get()
    {
        return texture->Width();
    }

    unsigned int Texture::Height::get()
    {
        return texture->Height();
    }

    System::IntPtr Texture::D3DTexture::get()
    {
        return System::IntPtr(texture->GetD3DTexture());
    }

    System::IntPtr Texture::OBSTexture::get()
    {
        return System::IntPtr(texture);
    }

    GraphicsSystem^ GraphicsSystem::Instance::get()
    {
        if (!instance) {
            instance = gcnew GraphicsSystem(GS);
        }
        return instance;
    }

    GraphicsSystem::GraphicsSystem(::GraphicsSystem *graphicsSystem)
    {
        this->graphicsSystem = graphicsSystem;
    }

    GraphicsSystem::~GraphicsSystem()
    {}

    System::IntPtr GraphicsSystem::CreateSharedTexture(
        unsigned int width,
        unsigned int height,
        GSColorFormat colorFormat)
    {
        D3D10_TEXTURE2D_DESC desc = { 0 };
        desc.Width = width;
        desc.Height = height;
        desc.MipLevels = 1;
        desc.ArraySize = 1;
        desc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
        desc.SampleDesc.Count = 1;
        desc.Usage = D3D10_USAGE_DEFAULT;
        desc.MiscFlags = D3D10_RESOURCE_MISC_SHARED;
        desc.BindFlags = D3D10_BIND_RENDER_TARGET | D3D10_BIND_SHADER_RESOURCE;

        ID3D10Texture2D* sharedTexture = NULL;
        ID3D10Device *d3d10device = static_cast<ID3D10Device *>(GS->GetDevice());

        d3d10device->CreateTexture2D(&desc, NULL, &sharedTexture);

        IDXGIResource* pDXGIResource = NULL;
        sharedTexture->QueryInterface(__uuidof(IDXGIResource), (LPVOID*) &pDXGIResource);

        HANDLE sharedHandle;

        pDXGIResource->GetSharedHandle(&sharedHandle);
        pDXGIResource->Release();

        return System::IntPtr(sharedHandle);
    }

    Texture^ GraphicsSystem::CreateTextureFromSharedHandle(
        unsigned int width,
        unsigned int height,
        System::IntPtr sharedHandle)
    {
        ::Texture *texture =
            GS->CreateTextureFromSharedHandle
            (width, height, (HANDLE) sharedHandle.ToInt64());
        return gcnew Texture(texture);
    }

    Texture^ GraphicsSystem::CreateTexture(
        unsigned int width,
        unsigned int height,
        GSColorFormat colorFormat,
        System::IntPtr data,
        bool isBuildingMipMaps,
        bool isStatic)
    {
        ::Texture *texture =
            GS->CreateTexture(width, height,
            static_cast<::GSColorFormat>(colorFormat), data.ToPointer(),
            isBuildingMipMaps, isStatic);
        return gcnew Texture(texture);
    }

    Texture^ GraphicsSystem::CreateTexture(
        unsigned int width,
        unsigned int height,
        GSColorFormat colorFormat,
        array<System::Byte>^ data,
        bool isBuildingMipMaps,
        bool isStatic)
    {
        if (data != nullptr) {
            pin_ptr<unsigned char> dataPtr = &data[0];
            return gcnew Texture(GS->CreateTexture(width, height,
                static_cast<::GSColorFormat>(colorFormat), dataPtr,
                isBuildingMipMaps, isStatic));
        }
        else {
            return gcnew Texture(GS->CreateTexture(width, height,
                static_cast<::GSColorFormat>(colorFormat), nullptr,
                isBuildingMipMaps, isStatic));
        }
    }

    void GraphicsSystem::DrawSprite(
        Texture^ texture,
        unsigned int color,
        float x, float y,
        float x2, float y2)
    {
        ::Texture *nativeTexture = static_cast<::Texture *>(
            texture->OBSTexture.ToPointer());
        GS->DrawSprite(nativeTexture, color, x, y, x2, y2);
    }

    void GraphicsSystem::DrawSpriteEx(
        Texture^ texture,
        unsigned int color,
        float x, float y,
        float x2, float y2,
        float u, float v,
        float u2, float v2)
    {
        ::Texture *nativeTexture = static_cast<::Texture *>(
            texture->OBSTexture.ToPointer());
        GS->DrawSpriteEx(nativeTexture, color, x, y, x2, y2, u, v, u2, v2);
    }

    void GraphicsSystem::DrawSpriteExRotate(
        Texture^ texture,
        unsigned int color,
        float x, float y,
        float x2, float y2,
        float degrees,
        float u, float v,
        float u2, float v2,
        float texDegrees)
    {
        ::Texture *nativeTexture = static_cast<::Texture *>(
            texture->OBSTexture.ToPointer());
        GS->DrawSpriteExRotate(nativeTexture, color, x, y, x2, y2, degrees,
            u, v, u2, v2, texDegrees);
    }
}