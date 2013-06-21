using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using CLROBS;

namespace CSharpSamplePlugin
{
    public class SampleImageSourceFactory : AbstractImageSourceFactory
    {
        public SampleImageSourceFactory()
        {
            ClassName = "SampleImageSourceClass";
            DisplayName = ".NET Image Source";
        }

        public override ImageSource Create(XElement data)
        {
            return new SampleImageSource(data);
        }

        public override bool ShowConfiguration(XElement data)
        {
            SampleConfigurationDialog dialog = new SampleConfigurationDialog(data);
            return dialog.ShowDialog().GetValueOrDefault(false);
        }
    }
}
