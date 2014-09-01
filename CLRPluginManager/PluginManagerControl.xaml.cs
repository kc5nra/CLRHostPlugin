using System;
using System.Collections.Generic;
using System.Collections.Specialized;
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
using System.Windows.Media.Animation;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace CLRPluginManager
{
    /// <summary>
    /// Interaction logic for PluginManagerControl.xaml
    /// </summary>
    public partial class PluginManagerControl : UserControl
    {
        private PluginManager pluginManager;

        public PluginManagerControl(PluginManager pluginManager)
        {
            InitializeComponent();
            this.pluginManager = pluginManager;
            PluginDefinition p = new PluginDefinition();
            PluginsListView.ItemsSource = pluginManager.PluginDefinitions;
            PluginsListView.SelectionChanged +=
                PluginsListView_SelectionChanged;

            if (PluginsListView.HasItems)
            {
                PluginsListView.SelectedIndex = 0;
            }

            PluginDefinitionPropertyGrid.PropertyValueChanged +=
                PluginDefinitionPropertyGrid_PropertyValueChanged;
        }

        private void PluginDefinitionPropertyGrid_PropertyValueChanged(object s,
            System.Windows.Forms.PropertyValueChangedEventArgs e)
        {
            CLROBS.API.Instance.SetChangedSettings(true);
        }

        private void PluginsListView_SelectionChanged(object sender,
            SelectionChangedEventArgs e)
        {
            if (PluginsListView.SelectedIndex != -1)
            {
                PluginDefinitionDetailsGrid.Visibility = Visibility.Visible;
                PluginDefinitionPropertyGrid.SelectedObject =
                    PluginsListView.SelectedItem;
            }
            else
            {
                PluginDefinitionDetailsGrid.Visibility = Visibility.Hidden;
            }
        }

        private void PluginEnabledCheckbox_Checked(object sender,
            RoutedEventArgs e)
        {
            PluginDefinitionPropertyGrid.Refresh();
            CLROBS.API.Instance.SetChangedSettings(true);
        }

        private void Grid_Drop(object sender, DragEventArgs e)
        {
            DoOpacityChange(DragDropInstallPanel, false);
            StringCollection potentialPlugins =
                ((DataObject)e.Data).GetFileDropList();
            foreach (string potentialPlugin in potentialPlugins)
            {
                InstallPluginControl installPluginControl =
                    new InstallPluginControl(pluginManager, potentialPlugin);
                installPluginControl.ShowDialog();
            }
        }

        private void Grid_Drag(object sender, DragEventArgs e)
        {
            e.Effects = DragDropEffects.None;

            if (sender != PluginsListView)
            {
                DoOpacityChange(DragDropInstallPanel, true);
                e.Handled = true;
                return;
            }

            StringCollection potentialPlugins =
                ((DataObject)e.Data).GetFileDropList();
            foreach (string potentialPlugin in potentialPlugins)
            {
                if ((Directory.Exists(potentialPlugin) ||
                    File.Exists(potentialPlugin)) &&
                    potentialPlugin.EndsWith(".clrplugin"))
                {
                    e.Effects = DragDropEffects.Copy;
                    e.Handled = true;
                }
                else
                {
                    DoOpacityChange(InvalidDropTextBlock, true);
                }
            }
        }

        private void Grid_DragLeave(object sender, DragEventArgs e)
        {
            if (sender != PluginsListView)
            {
                DoOpacityChange(InvalidDropTextBlock, false);
                DoOpacityChange(DragDropInstallPanel, false);
            }
        }

        private void DoOpacityChange(UIElement e, bool isVisible)
        {
            e.Opacity = (isVisible) ? 100 : 0;
        }
    }
}