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
        { }

        public void Tick(float seconds)
        { }

        public void Render(float x, float y, float width, float height)
        { }

        public void Preprocess()
        { }

        public Vector2 GetSize()
        {
            return new Vector2(.5f, .5f);
        }

        public void EndScene()
        { }

        public void BeginScene()
        { }
    }
}
