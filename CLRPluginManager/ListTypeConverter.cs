using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CLRPluginManager
{
    public class ListTypeConverter : TypeConverter
    {
        public override bool GetStandardValuesSupported(
            ITypeDescriptorContext context)
        {
            return true;
        }

        public override bool GetStandardValuesExclusive(ITypeDescriptorContext
        context)
        {
            return true;
        }

        public override StandardValuesCollection GetStandardValues(
            ITypeDescriptorContext context)
        {
            PluginDefinition def = context.Instance as PluginDefinition;
            List<Plugin> values = new List<Plugin>();
            values.AddRange(def.AvailableVersions);
            return new StandardValuesCollection(values);
        }

        public override bool CanConvertFrom(ITypeDescriptorContext context, Type sourceType)
        {
            return true;
        }

        public override bool CanConvertTo(ITypeDescriptorContext context, Type destinationType)
        {
            return true;
        }

        public override object ConvertFrom(ITypeDescriptorContext context, System.Globalization.CultureInfo culture, object value)
        {
            PluginDefinition def = context.Instance as PluginDefinition;
            Plugin p = def.AvailableVersions.FirstOrDefault(
                obj => obj.Version == (string)value);
            return p;
        }

        public override object ConvertTo(ITypeDescriptorContext context, System.Globalization.CultureInfo culture, object value, Type destinationType)
        {
            if (value != null)
            {
                Plugin p = (value as Plugin);
                if (p != null)
                {
                    return p.Version;
                }
                else
                {
                    return value.ToString();
                }
            }
            else
            {
                return null;
            }
        }
    }
}
