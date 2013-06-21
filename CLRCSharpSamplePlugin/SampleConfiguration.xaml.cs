using CLROBS;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace CSharpSamplePlugin
{
    /// <summary>
    /// Interaction logic for SampleConfiguration.xaml
    /// </summary>
    public partial class SampleConfigurationDialog : Window
    {
        private XElement config;

        public SampleConfigurationDialog(XElement config)
        {
            InitializeComponent();
            this.config = config;

            String file = config.GetString("file");
            if (File.Exists(file))
            {
                LoadImage(new Uri(config.GetString("file")));
            }
        }

        private void okButton_Click(object sender, RoutedEventArgs e)
        {
            config.SetString("file", filenameText.Text);
            DialogResult = true;
            Close();
        }

        private void cancelButton_Click(object sender, RoutedEventArgs e)
        {
            DialogResult = false;
            Close();
        }

        private void browseButton_Click(object sender, RoutedEventArgs e)
        {
            Microsoft.Win32.OpenFileDialog dlg = new Microsoft.Win32.OpenFileDialog();
            dlg.Filter = "PNG Image (.png)|*.png|JPEG Image (.jpg)|*.jpg";
            dlg.Multiselect = false;
            if (dlg.ShowDialog().GetValueOrDefault()) {
                LoadImage(new Uri(dlg.FileName));
            }
        }

        private void LoadImage(Uri imageUri)
        {
            filenameText.Text = imageUri.LocalPath;
            BitmapImage src = new BitmapImage();
            src.BeginInit();
            src.UriSource = imageUri;
            src.EndInit();
            previewImage.Source = src;
            previewImage.Stretch = Stretch.Uniform;
        }


    }
}
