using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using CLROBS;

namespace CSharpSamplePlugin
{
    class SampleImageSource : ImageSource
    {

        private Texture texture = null;

        public SampleImageSource()
        {
            byte[] data = new byte[100 * 100 * 4];
            for (int i = 0; i < data.Length; i++)
            {
                data[i] = (byte)0xFF;
            }

            texture = GS.CreateTexture(100, 100, GSColorFormat.GS_BGRA, data, false, false);
        }


        public void UpdateSettings()
        {
            this.ToString();
        }

        public void Tick(float seconds)
        {
            this.ToString();
        }

        public void Render(float x, float y, float width, float height)
        {
            this.ToString();
        }

        public void Preprocess()
        {
            this.ToString();
        }

        public Vector2 GetSize()
        {
            return new Vector2(100f, 100f);
        }

        public void EndScene()
        {
            this.ToString();
        }

        public void BeginScene()
        {
            this.ToString();
        }

        public void Dispose()
        {
            if (texture != null)
            {
                texture.Dispose();
            }
        }

        private API Api
        {
            get { return SamplePlugin.Instance.Api; }
        }

        private GraphicsSystem GS
        {
            get { return GraphicsSystem.Instance; }
        }
    }
}
