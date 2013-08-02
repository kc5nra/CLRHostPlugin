#include "OBSApi.h"
#include "GraphicsSystem.h"

CLROBS::Texture::Texture(::Texture *texture)
{
    this->texture = texture;
}

CLROBS::Texture::~Texture()
{
    delete texture;
}

void CLROBS::Texture::SetImage(System::IntPtr data, GSImageFormat imageFormat, unsigned int pitch)
{
    texture->SetImage(data.ToPointer(), static_cast<::GSImageFormat>(imageFormat), pitch);
}

void CLROBS::Texture::SetImage(array<System::Byte>^ data, GSImageFormat imageFormat, unsigned int pitch)
{
    pin_ptr<unsigned char> dataPtr = &data[0];
    texture->SetImage(dataPtr, static_cast<::GSImageFormat>(imageFormat), pitch);
}

CLROBS::GSColorFormat CLROBS::Texture::Format::get() 
{ 
    return static_cast<GSColorFormat>(texture->GetFormat()); 
}

unsigned int CLROBS::Texture::Width::get() 
{ 
    return texture->Width(); 
}
  
unsigned int CLROBS::Texture::Height::get() 
{ 
    return texture->Height(); 
}

System::IntPtr CLROBS::Texture::D3DTexture::get() 
{ 
    return System::IntPtr(texture->GetD3DTexture()); 
}

System::IntPtr CLROBS::Texture::OBSTexture::get() 
{ 
    return System::IntPtr(texture); 
}

CLROBS::GraphicsSystem^ CLROBS::GraphicsSystem::Instance::get()
{
    if (!instance) {
        instance = gcnew CLROBS::GraphicsSystem(GS);
    }
    return instance;
}

CLROBS::GraphicsSystem::GraphicsSystem(::GraphicsSystem *graphicsSystem)
{
    this->graphicsSystem = graphicsSystem;
}

CLROBS::GraphicsSystem::~GraphicsSystem()
{
}

CLROBS::Texture^ CLROBS::GraphicsSystem::CreateTexture(unsigned int width, unsigned int height, CLROBS::GSColorFormat colorFormat, System::IntPtr data, bool isBuildingMipMaps, bool isStatic)
{
    ::Texture *texture = GS->CreateTexture(width, height, static_cast<::GSColorFormat>(colorFormat), data.ToPointer(), isBuildingMipMaps, isStatic);
    return gcnew Texture(texture);
}

CLROBS::Texture^ CLROBS::GraphicsSystem::CreateTexture(unsigned int width, unsigned int height, CLROBS::GSColorFormat colorFormat, array<System::Byte>^ data, bool isBuildingMipMaps, bool isStatic)
{
    if (data != nullptr) {
        pin_ptr<unsigned char> dataPtr = &data[0];
        return gcnew Texture(GS->CreateTexture(width, height, static_cast<::GSColorFormat>(colorFormat), dataPtr, isBuildingMipMaps, isStatic));
    } else {
        return gcnew Texture(GS->CreateTexture(width, height, static_cast<::GSColorFormat>(colorFormat), nullptr, isBuildingMipMaps, isStatic));
    }
}

void CLROBS::GraphicsSystem::DrawSprite(CLROBS::Texture^ texture, unsigned int color, float x, float y, float x2, float y2)
{
    ::Texture *nativeTexture = static_cast<::Texture *>(texture->OBSTexture.ToPointer());
    GS->DrawSprite(nativeTexture, color, x, y, x2, y2);
}
