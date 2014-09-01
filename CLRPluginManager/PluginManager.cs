using CLROBS;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.Serialization.Json;
using System.Text;
using System.Threading.Tasks;

namespace CLRPluginManager
{
    public class PluginManager
    {
        public List<PluginDefinition> PluginDefinitions { get; private set; }

        public List<PluginInstance> LoadedPlugins { get; private set; }

        public PluginManager()
        {
            PluginDefinitions = new List<PluginDefinition>();
            LoadedPlugins = new List<PluginInstance>();

            ReloadPluginDefinitions();
            LoadPlugins();
        }

        public void SavePluginDefinitions()
        {
            foreach (PluginDefinition pluginDefinition in PluginDefinitions)
            {
                try
                {
                    using (FileStream stream =
                        File.OpenWrite(pluginDefinition.Path))
                    {
                        DataContractJsonSerializer ser =
                            new DataContractJsonSerializer(
                                typeof(PluginDefinition));
                        ser.WriteObject(stream, pluginDefinition);
                    }
                }
                catch (Exception e)
                {
                    API.Instance.Log("Failed to serialize {0}",
                        pluginDefinition.Path);
                    API.Instance.Log("Exception: {0}", e);
                }
            }
        }

        public void LoadPlugins()
        {
            foreach (PluginDefinition pluginDefinition in PluginDefinitions)
            {
                LoadPlugin(pluginDefinition);
            }
        }

        private void LoadPlugin(PluginDefinition pluginDefinition)
        {
            if (pluginDefinition.Enabled &&
                pluginDefinition.SelectedVersion != null)
            {
                PluginInstance pluginInstance =
                    new PluginInstance(pluginDefinition,
                        pluginDefinition.SelectedVersion);
                if (pluginInstance.Create())
                {
                    LoadedPlugins.Add(pluginInstance);
                }
            }
        }

        private void ReloadPluginDefinitions()
        {
            PluginDefinitions.Clear();

            string pluginPath = API.Instance.GetPluginDataPath();

            var directories = Directory.EnumerateDirectories(
                pluginPath, "*.clrplugin");
            foreach (var pluginDirectory in directories)
            {
                PluginDefinition def = LoadPluginDefinition(pluginDirectory);
                if (def != null)
                {
                    PluginDefinitions.Add(def);
                }
            }
        }

        public static PluginDefinition LoadPluginDefinition(
            string pluginDirectory)
        {
            string pluginDefinition =
                Path.Combine(pluginDirectory, "pluginDefinition.json");
            if (File.Exists(pluginDefinition))
            {
                try
                {
                    using (FileStream stream = File.OpenRead(pluginDefinition))
                    {
                        DataContractJsonSerializer ser =
                            new DataContractJsonSerializer(
                                typeof(PluginDefinition));
                        PluginDefinition def = ser.ReadObject(stream)
                            as PluginDefinition;
                        def.Path = pluginDefinition;
                        def.AvailableVersions =
                            LoadAvailableVersions(pluginDirectory);
                        return def;
                    }
                }
                catch (Exception e)
                {
                    API.Instance.Log("Failed to deserialize {0}",
                        pluginDefinition);
                    API.Instance.Log("Exception: {0}", e);
                }
            }

            return null;
        }

        private static List<Plugin> LoadAvailableVersions(
            string pluginDirectory)
        {
            List<Plugin> availableVersions = new List<Plugin>();
            String versionsDirectory =
                Path.Combine(pluginDirectory, "Versions");
            if (Directory.Exists(versionsDirectory))
            {
                var versionDirectories =
                    Directory.EnumerateDirectories(versionsDirectory);
                foreach (String versionDirectory in versionDirectories)
                {
                    availableVersions.Add(LoadPluginVersion(versionDirectory));
                }
            }

            return availableVersions;
        }

        private static Plugin LoadPluginVersion(string versionDirectory)
        {
            Plugin p = new Plugin();
            p.Path = versionDirectory;
            p.Version = new DirectoryInfo(versionDirectory).Name;
            return p;
        }
    }
}