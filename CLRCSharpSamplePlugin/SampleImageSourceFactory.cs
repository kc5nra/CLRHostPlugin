using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using CLROBS;

using System.Windows;

namespace CSharpSamplePlugin
{
    public class SampleImageSourceFactory : AbstractImageSourceFactory
    {
        public SampleImageSourceFactory()
        {
            this.ClassName = "SampleImageSourceClass";
            this.DisplayName = "Sample ImageSource Description";
        }

        public override ImageSource Create(XElement data)
        {
            return new SampleImageSource();
        }

        public override void ShowConfiguration(XElement data)
        {
            Window window = new Window();
            SampleConfigurationDialog configDialog = new SampleConfigurationDialog();
            window.Width = 400;
            window.Height = 400;
            window.WindowStartupLocation = WindowStartupLocation.CenterScreen;
            window.Content = configDialog;
            bool? returnVal = window.ShowDialog();
            if (returnVal.HasValue && returnVal.Value)
            {
            }
            else
            {

            }
        }
    }
}
