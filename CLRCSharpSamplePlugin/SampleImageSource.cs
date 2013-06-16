using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using OBS;

namespace CSharpSamplePlugin
{
    class SampleImageSource : ImageSource
    {
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
            return new Vector2(.5f, .5f);
        }

        public void EndScene()
        {
            this.ToString();
        }

        public void BeginScene()
        {
            this.ToString();
        }

    }
}
