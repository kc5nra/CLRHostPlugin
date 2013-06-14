using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using OBS;

namespace CSharpSamplePlugin
{
    public class SampleImageSourceFactory : AbstractImageSourceFactory
    {
        public SampleImageSourceFactory()
        {
            this.ClassName = "SampleImageSourceClass";
            this.DisplayName = "Sample ImageSource Description";
        }

        public override ImageSource Create()
        {
            return new SampleImageSource();
        }

        public override void ShowConfiguration()
        {
            throw new NotImplementedException();
        }
    }
}
