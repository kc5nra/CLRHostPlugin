using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using OBS;
namespace CSharpSamplePlugin
{
    class SamplePlugin : AbstractPlugin
    {
        public SamplePlugin()
        {
            // Setup the default properties
            Name = "Sample Plugin Name";
            Description = "Sample Plugin Description";
        }
        public override bool LoadPlugin()
        {
            Api.AddImageSourceFactory(new SampleImageSourceFactory());
            Api.AddImageSourceFactory(new SampleImageSourceFactory());
            return true;
        }

        public override void UnloadPlugin()
        {
        }

        public override void OnStartStream()
        {
            String h = ""; h.ToString();
        }
        public override void OnStopStream()
        {
            String h = ""; h.ToString();
        }
    }
}
