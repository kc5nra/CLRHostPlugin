using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using CLROBS;

using System.Windows;
using System.Windows.Media;

namespace CSharpSamplePlugin
{
    public class SampleImageSourceFactory : AbstractImageSourceFactory
    {
        public SampleImageSourceFactory()
        {
            this.ClassName = "SampleImageSourceClass";
            this.DisplayName = ".NET Image Source";
        }

        public override CLROBS.ImageSource Create(XElement data)
        {
            return new SampleImageSource(data);
        }

        public override bool ShowConfiguration(XElement data)
        {
            SampleConfigurationDialog dialog = new SampleConfigurationDialog(data);

            bool? returnVal = dialog.ShowDialog();
            return returnVal.GetValueOrDefault(false);
        }
    }
}
