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
        public SamplePlugin()
        {
            // Setup the default properties
            Name = "Sample Image Plugin";
            Description = "Sample Image Plugin lets you show a picture";
        }
        
        public override bool LoadPlugin()
        {
            API.Instance.AddImageSourceFactory(new SampleImageSourceFactory());
            return true;
        }
    }
}
