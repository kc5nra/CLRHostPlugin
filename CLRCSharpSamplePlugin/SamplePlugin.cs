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
            Name = "Sample Image Plugin";
            Description = "Sample Image Plugin lets you show a picture";
        }
        public override bool LoadPlugin()
        {
            API.Instance.AddImageSourceFactory(new SampleImageSourceFactory());
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
