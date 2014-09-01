using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using CLROBS;

namespace CLRPluginManager
{
    class CLRPluginManagerPlugin : AbstractPlugin
    {
        private PluginManager pluginManager;

        public CLRPluginManagerPlugin()
        {
            Name = "CLR Plugin Manager";
            Description = "Plugin manager that handles loading and unloading of CLR plugins";

            pluginManager = new PluginManager();
        }



        public override bool LoadPlugin()
        {
            API.Instance.AddSettingsPane(new CLRPluginManagerSettingsPane(pluginManager));

            pluginManager.LoadedPlugins.ForEach(instance =>
            {
                if (instance.Instance.LoadPlugin())
                {
                    API.Instance.Log("Loaded plugin {0} ({1}) successfully",
                        instance.PluginDefinition.Name, instance.SelectedPlugin.Version);   
                }
                else
                {
                    API.Instance.Log("Failed to load {0} ({1})",
                        instance.PluginDefinition.Name, instance.SelectedPlugin.Version);
                }
            });

            return true;
        }

        public override void UnloadPlugin()
        {
            pluginManager.LoadedPlugins.ForEach(
                instance => instance.Instance.UnloadPlugin());
        }

        public override void OnStartStream()
        {
            pluginManager.LoadedPlugins.ForEach(
                instance => instance.Instance.OnStartStream());
        }

        public override void OnStopStream()
        {
            pluginManager.LoadedPlugins.ForEach(
                instance => instance.Instance.OnStopStream());
        }
    }
}
