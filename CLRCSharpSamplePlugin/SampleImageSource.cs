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
    class SampleImageSource : CLROBS.ImageSource, IDisposable
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
                texture.Dispose();
                texture = null;

                if (File.Exists(imageFile))
                {
                    BitmapImage src = new BitmapImage();
                    
                    src.BeginInit();
                    src.UriSource = new Uri(imageFile);
                    src.EndInit();

                    
                    WriteableBitmap wb = new WriteableBitmap(src);
              
                    texture = GS.CreateTexture((UInt32)wb.PixelWidth, (UInt32)wb.PixelHeight, GSColorFormat.GS_BGRA, wb.BackBuffer, false, true);
                }
                else
                {
                    texture = null;
                }
            }
        }

        public void UpdateSettings()
        {
            XElement dataElement = config.GetElement("data");
            LoadTexture(config.GetString("file"));
        }

        public void Tick(float seconds)
        {
        }

        public void Render(float x, float y, float width, float height)
        {
            lock (textureLock)
            {
                if (texture != null)
                {
                    GS.DrawSprite(texture, 0xFFFFFFFF, x, y, x + width, y + height);
                }
            }
        }

        public void Preprocess()
        {
        }

        public Vector2 GetSize()
        {
            return new Vector2(100f, 100f);
        }

        public void EndScene()
        {
        }

        public void BeginScene()
        {
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

        private API Api
        {
            get { return API.Instance; }
        }

        private GraphicsSystem GS
        {
            get { return GraphicsSystem.Instance; }
        }
    }
}
