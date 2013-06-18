using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using CLROBS;
namespace CSharpSamplePlugin
{
    class SamplePlugin : AbstractPlugin
    {
        private static SamplePlugin instance;
        public static SamplePlugin Instance {
            get { return instance; }
        }

        public SamplePlugin()
        {
            instance = this;

            // Setup the default properties
            Name = "Sample Plugin Name";
            Description = "Sample Plugin Description";
        }
        public override bool LoadPlugin()
        {
            Api.AddImageSourceFactory(new SampleImageSourceFactory());
            return true;
        }

        public override void UnloadPlugin()
        {
        }

        public override void OnStartStream()
        {
        }
        public override void OnStopStream()
        {
        }
    }
}
