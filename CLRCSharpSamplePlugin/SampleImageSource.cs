using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using CLROBS;
using System.Threading;
using System.IO;
using System.Windows.Media.Imaging;
using System.Windows.Media;

namespace CSharpSamplePlugin
{
    class SampleImageSource : AbstractImageSource//, IDisposable
    {
        private Object textureLock = new Object();
        private Texture texture = null;
        private XElement config;

        public SampleImageSource(XElement config)
        {
            this.config = config;
            UpdateSettings();
        }
        
        private void LoadTexture(String imageFile)
        {

            lock (textureLock)
            {
                if (texture != null)
                {
                    texture.Dispose();
                    texture = null;
                }

                if (File.Exists(imageFile))
                {
                    BitmapImage src = new BitmapImage();
                    
                    src.BeginInit();
                    src.UriSource = new Uri(imageFile);
                    src.EndInit();
                    
                    WriteableBitmap wb = new WriteableBitmap(src);
              
                    texture = GS.CreateTexture((UInt32)wb.PixelWidth, (UInt32)wb.PixelHeight, GSColorFormat.GS_BGRA, null, false, false);

                    texture.SetImage(wb.BackBuffer, GSImageFormat.GS_IMAGEFORMAT_BGRA, (UInt32)(wb.PixelWidth * 4));

                    config.Parent.SetInt("cx", wb.PixelWidth);
                    config.Parent.SetInt("cy", wb.PixelHeight);

                    Size.X = (float)wb.PixelWidth;
                    Size.Y = (float)wb.PixelHeight;

                }
                else
                {
                    texture = null;
                }
            }
        }

        override public void UpdateSettings()
        {
            XElement dataElement = config.GetElement("data");
            LoadTexture(config.GetString("file"));
        }

        override public void Render(float x, float y, float width, float height)
        {
            lock (textureLock)
            {
                if (texture != null)
                {
                    GS.DrawSprite(texture, 0xFFFFFFFF, x, y, x + width, y + height);
                }
            }
        }

        public void Dispose()
        {
            lock (textureLock)
            {
                if (texture != null)
                {
                    texture.Dispose();
                    texture = null;
                }
            }
        }
    }
}
