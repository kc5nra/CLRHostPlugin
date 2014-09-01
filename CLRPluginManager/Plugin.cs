using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Runtime.Serialization;
using System.Text;
using System.Threading.Tasks;


namespace CLRPluginManager
{
    [DataContract]
    [TypeConverter(typeof(ExpandableObjectConverter))]
    public class Plugin
    {
        static readonly Random r = new Random();

        [DataMember]
        [Category("Information")]
        [Description("The path on the local machine where the plugin was loaded from.")]
        [Browsable(true)]
        [ReadOnly(true)]
        public String Path { get; set; }

        [DataMember]
        [Category("Information")]
        [Description("The version of this particular plugin")]
        [Browsable(true)]
        [ReadOnly(true)]
        public String Version { get; set; }

        public override string ToString()
        {
            return Version;
        }
    }
}
