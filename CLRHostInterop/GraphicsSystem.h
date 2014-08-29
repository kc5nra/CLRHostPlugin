#pragma once

class Texture;
class GraphicsSystem;

namespace CLROBS
{
    public enum class GSDrawMode
    {
        GS_POINTS,
        GS_LINES,
        GS_LINESTRIP,
        GS_TRIANGLES,
        GS_TRIANGLESTRIP
    };

    public enum class GSColorFormat
    {
        GS_UNKNOWNFORMAT,
        GS_ALPHA,
        GS_GRAYSCALE,
        GS_RGB,
        GS_RGBA,
        GS_BGR,
        GS_BGRA,
        GS_RGBA16F,
        GS_RGBA32F,
        GS_B5G5R5A1,
        GS_B5G6R5,
        GS_R10G10B10A2,
        GS_DXT1,
        GS_DXT3,
        GS_DXT5
    };

    public enum class GSIndexType
    {
        GS_UNSIGNED_SHORT,
        GS_UNSIGNED_LONG
    };

    public enum class GSBlendType
    {
        GS_BLEND_ZERO,
        GS_BLEND_ONE,
        GS_BLEND_SRCCOLOR,
        GS_BLEND_INVSRCCOLOR,
        GS_BLEND_SRCALPHA,
        GS_BLEND_INVSRCALPHA,
        GS_BLEND_DSTCOLOR,
        GS_BLEND_INVDSTCOLOR,
        GS_BLEND_DSTALPHA,
        GS_BLEND_INVDSTALPHA,
        GS_BLEND_FACTOR,
        GS_BLEND_INVFACTOR
    };

    public enum class GSSampleFilter
    {
        GS_FILTER_LINEAR,
        GS_FILTER_POINT,
        GS_FILTER_ANISOTROPIC,
        GS_FILTER_MIN_MAG_POINT_MIP_LINEAR,
        GS_FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT,
        GS_FILTER_MIN_POINT_MAG_MIP_LINEAR,
        GS_FILTER_MIN_LINEAR_MAG_MIP_POINT,
        GS_FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR,
        GS_FILTER_MIN_MAG_LINEAR_MIP_POINT,

        GS_FILTER_MIN_MAG_MIP_POINT = GS_FILTER_POINT,
        GS_FILTER_MIN_MAG_MIP_LINEAR = GS_FILTER_LINEAR
    };

    public enum class GSAddressMode
    {
        GS_ADDRESS_CLAMP,
        GS_ADDRESS_WRAP,
        GS_ADDRESS_MIRROR,
        GS_ADDRESS_BORDER,
        GS_ADDRESS_MIRRORONCE,

        GS_ADDRESS_NONE = GS_ADDRESS_CLAMP,
        GS_ADDRESS_REPEAT = GS_ADDRESS_WRAP
    };

    public enum class GSImageFormat
    {
        GS_IMAGEFORMAT_A8,
        GS_IMAGEFORMAT_L8,
        GS_IMAGEFORMAT_RGB,
        GS_IMAGEFORMAT_RGBX,
        GS_IMAGEFORMAT_RGBA,
        GS_IMAGEFORMAT_RGBA16F,
        GS_IMAGEFORMAT_RGBA32F,
        GS_IMAGEFORMAT_BGR,
        GS_IMAGEFORMAT_BGRX,
        GS_IMAGEFORMAT_BGRA,
    };

    public ref class Texture
    {
    private:
        ::Texture *texture;
    public:
        Texture(::Texture *texture);
        Texture(System::IntPtr texture);
        ~Texture();

    public:

        void SetImage(array<System::Byte>^ data, GSImageFormat imageFormat, unsigned int pitch);
        void SetImage(System::IntPtr data, GSImageFormat imageFormat, unsigned int pitch);

    public:
        property GSColorFormat Format
        {
        public:
            GSColorFormat get();
        }

        property unsigned int Width
        {
        public:
            unsigned int get();
        }

        property unsigned int Height
        {
        public:
            unsigned int get();
        }

        property System::IntPtr D3DTexture
        {
        public:
            System::IntPtr get();
        }

        property System::IntPtr OBSTexture
        {
        public:
            System::IntPtr get();
        }
    };

    public ref class GraphicsSystem
    {
    private:
        static GraphicsSystem^ instance = nullptr;
    public:
        static property GraphicsSystem^ Instance
        {
        public:
            GraphicsSystem^ get();
        }
    private:
        ::GraphicsSystem *graphicsSystem;

    private:
        GraphicsSystem(::GraphicsSystem *graphicsSystem);
        ~GraphicsSystem();

    public:

        System::IntPtr CreateSharedTexture(unsigned int width,
            unsigned int height, GSColorFormat colorFormat);
        Texture^ CreateTextureFromSharedHandle(unsigned int width,
            unsigned int height, System::IntPtr sharedHandle);
        Texture^ CreateTexture(unsigned int width, unsigned int height,
            GSColorFormat colorFormat, System::IntPtr data,
            bool isBuildingMipMaps, bool isStatic);
        Texture^ CreateTexture(unsigned int width, unsigned int height,
            GSColorFormat colorFormat, array<System::Byte>^ data,
            bool isBuildingMipMaps, bool isStatic);
        void DrawSprite(Texture^ texture, unsigned int color, float x, float y,
            float x2, float y2);
        void DrawSpriteEx(Texture^ texture, unsigned int color,
            float x, float y, float x2, float y2, float u, float v,
            float u2, float v2);
        void DrawSpriteExRotate(Texture^ texture, unsigned int color,
            float x, float y, float x2, float y2, float degrees,
            float u, float v, float u2, float v2, float texDegrees);
    };
};