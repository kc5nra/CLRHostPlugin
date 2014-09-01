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

namespace CLRPluginManager
{
    /// <summary>
    /// Interaction logic for UserControl1.xaml
    /// </summary>
    public partial class InstallPluginControl : Window
    {
        private PluginManager pluginManager;
        private string pluginLocation;

        public InstallPluginControl(PluginManager pluginManager, string pluginLocation)
        {
            InitializeComponent();
            this.pluginManager = pluginManager;
            this.pluginLocation = pluginLocation;
        }

        private void InstallPlugin()
        {
            if (Directory.Exists(pluginLocation))
            {
                InstallPluginFromDirectory(pluginLocation);
            }
        }

        private void InstallPluginFromDirectory(string pluginDirectory)
        {
            PluginDefinition pluginDefinition = PluginManager.LoadPluginDefinition(pluginDirectory);

            if (pluginDefinition != null)
            {
                PluginDefinition matchingDefinition = pluginManager.PluginDefinitions.SingleOrDefault(
                    def => def.Name == pluginDefinition.Name);

                DirectoryInfo pluginDirectoryInfo = new DirectoryInfo(pluginDirectory);

                string pluginDestination = Path.Combine(CLROBS.API.Instance.GetPluginDataPath(), pluginDirectoryInfo.Name);
                CopyTo(pluginDirectory, pluginDestination, true);
                if (matchingDefinition == null)
                {
                    pluginManager.PluginDefinitions.Add(pluginDefinition);
                }
                else
                {
                }
            }
        }

        private void CopyPluginFromDirectory(string pluginDirectory)
        {
            CopyTo(pluginDirectory, CLROBS.API.Instance.GetPluginDataPath());
        }

        private void CopyTo(string sourcePath, string destinationPath, bool overwrite = false)
        {
            var source = new DirectoryInfo(sourcePath);
            var target = new DirectoryInfo(destinationPath);

            CopyToRecursive(source, target, overwrite);
        }

        private void CopyToRecursive(DirectoryInfo source, DirectoryInfo target, bool overwrite = false)
        {
            foreach (DirectoryInfo dir in source.GetDirectories())
            {
                DirectoryInfo sub = new DirectoryInfo(Path.Combine(target.FullName, dir.Name));
                if (!sub.Exists)
                {
                    sub.Create();
                }
                CopyToRecursive(dir, sub, overwrite);
            }
            foreach (FileInfo file in source.GetFiles())
            {
                file.CopyTo(Path.Combine(target.FullName, file.Name), overwrite);
                File.SetAttributes(file.FullName, FileAttributes.Normal);
            }
        }

        private void Install_Click(object sender, RoutedEventArgs e)
        {
            InstallPlugin();
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            LayoutGrid.ClearValue(WidthProperty);
            LayoutGrid.ClearValue(HeightProperty);
        }
    }
}