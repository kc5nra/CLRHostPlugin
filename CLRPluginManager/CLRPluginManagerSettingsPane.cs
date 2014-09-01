using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using CLROBS;

namespace CLRPluginManager
{
    class CLRPluginManagerSettingsPane : AbstractWPFSettingsPane
    {
        private PluginManager pluginManager;

        public CLRPluginManagerSettingsPane(PluginManager pluginManager)
        {
            this.pluginManager = pluginManager;
            Category = "CLR Plugin Manager";
        }

        public override void ApplySettings()
        {
            pluginManager.SavePluginDefinitions();
        }

        public override void CancelSettings()
        {
            throw new NotImplementedException();
        }

        public override UIElement CreateUIElement()
        {
            return new PluginManagerControl(pluginManager);
        }

        public override bool HasDefaults()
        {
            return false;
        }

        public override void SetDefaults()
        {
            throw new NotImplementedException();
        }
    }
}
