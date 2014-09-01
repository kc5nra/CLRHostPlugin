using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Runtime.Serialization;
using System.Text;
using System.Threading.Tasks;

namespace CLRPluginManager
{
    [DataContract]
    [TypeConverter(typeof(ExpandableObjectConverter))]
    public class PluginDefinition
    {
        [DataMember]
        [Category("Information")]
        [Description("The name of the plugin.")]
        [Browsable(true)]
        [ReadOnly(true)]
        public string Name { get; set; }

        [DataMember]
        [Category("Information")]
        [Description("General description of the plugin")]
        [Browsable(true)]
        [ReadOnly(true)]
        public string Description { get; set; }

        [IgnoreDataMember]
        [Category("Information")]
        [Description("The path on the local machine where the plugin description exists")]
        [Browsable(true)]
        [ReadOnly(true)]
        public string Path { get; set; }

        [DataMember]
        [Category("Information")]
        [DisplayName("Assembly Name")]
        [Description("Assembly name of Plugin")]
        [Browsable(true)]
        [ReadOnly(true)]
        public string AssemblyName { get; set; }

        [IgnoreDataMember]
        [Browsable(false)]
        public List<Plugin> AvailableVersions { get; set; }

        [IgnoreDataMember]
        [Category("Information")]
        [DisplayName("Available Versions")]
        [Description("Available versions of this plugin")]
        [Browsable(true)]
        [ReadOnly(true)]
        public ReadOnlyCollection<Plugin> ReadOnlyAvailableVersions {
            get { return AvailableVersions.AsReadOnly(); }
        }

        [DataMember]
        [Category("Runtime")]
        [DisplayName("Selected Version")]
        [Description("Currently selected version of the plugin to use in OBS")]
        [Browsable(true)]
        [TypeConverter(typeof(ListTypeConverter))]
        public Plugin SelectedVersion { get; set; }

        [DataMember]
        [Category("Runtime")]
        [Description("Enable this plugin for use in OBS")]
        [Browsable(true)]
        public bool Enabled { get; set; }

        [OnDeserialized]
        void OnDeserialized(StreamingContext c)
        {
            AvailableVersions = new List<Plugin>();
        }
    }
}
