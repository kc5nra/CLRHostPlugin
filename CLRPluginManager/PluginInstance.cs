using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Reflection;
using System.IO;

namespace CLRPluginManager
{
    public class PluginInstance
    {
        public PluginDefinition PluginDefinition { get; private set; }
        public Plugin SelectedPlugin { get; private set; }
        public CLROBS.Plugin Instance { get; private set; }

        public bool HasInstance { get { return Instance != null; } }

        public PluginInstance(PluginDefinition pluginDefinition, Plugin selectedPlugin)
        {
            PluginDefinition = pluginDefinition;
            SelectedPlugin = selectedPlugin;
        }

        public bool Create()
        {
            if (Instance != null)
            {
                return true;
            }

            AppDomain currentDomain = AppDomain.CurrentDomain;
            ResolveEventHandler assemblyDependencyResolver =
                new ResolveEventHandler(AssemblyDependencyResolver);

            currentDomain.AssemblyResolve += assemblyDependencyResolver;
            string assemblyPath = Path.Combine(SelectedPlugin.Path, PluginDefinition.AssemblyName + ".dll");
            try
            {
                if (File.Exists(assemblyPath))
                {
                    Assembly pluginAssembly = Assembly.LoadFrom(assemblyPath);
                    Instance = CreatePluginInstance(pluginAssembly);
                    return Instance != null;
                }
            }
            catch (Exception e)
            {
                CLROBS.API.Instance.Log("Unable to create any valid plugin instance from assembly {0}", assemblyPath);
                CLROBS.API.Instance.Log("Exception {0}", e);
            }

            return false;
        }

        private CLROBS.Plugin CreatePluginInstance(Assembly pluginAssembly)
        {
            foreach (Type type in pluginAssembly.ExportedTypes)
            {
                try
                {
                    if (typeof(CLROBS.Plugin).IsAssignableFrom(type) &&
                        !type.IsInterface && !type.IsAbstract && type.IsPublic)
                    {
                        try
                        {
                            // Plugins must have a no-arg constructor
                            ConstructorInfo pluginConstructor = type.GetConstructor(new Type[0]);
                            if (pluginConstructor != null)
                            {
                                return (CLROBS.Plugin)pluginConstructor.Invoke(new object[0]);
                            }
                        }
                        catch (Exception e)
                        {
                            CLROBS.API.Instance.Log("Failed to create instance of {0}", type);
                            CLROBS.API.Instance.Log("Exception: {0}", e);
                        }
                    }
                }
                catch (Exception)
                { }
            }

            return null;
        }



        private Assembly AssemblyDependencyResolver(object sender, ResolveEventArgs args)
        {
            Assembly loadingAssembly = Assembly.GetExecutingAssembly();
            AssemblyName[] referencedAssemblies = loadingAssembly.GetReferencedAssemblies();

            AssemblyName internalReference = Array.Find<AssemblyName>(
                referencedAssemblies, a => a.Name == args.Name);
            if (internalReference != null)
            {
                return Assembly.LoadFrom(internalReference.CodeBase);
            }
            else
            {
                string resolvedAssemblyPath =
                        Path.Combine(SelectedPlugin.Path, 
                        ExtractAssemblyName(args.Name)) + ".dll";
                if (File.Exists(resolvedAssemblyPath))
                {
                    return Assembly.LoadFrom(resolvedAssemblyPath);
                }
            }
            return null;
        }

        private string ExtractAssemblyName(string assemblyName)
        {
            return assemblyName.Substring(0, assemblyName.IndexOf(","));
        }

    }
}
