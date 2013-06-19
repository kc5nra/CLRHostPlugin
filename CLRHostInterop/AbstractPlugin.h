#pragma once

#include "Plugin.h"
#include "API.h"

using namespace CLROBS;

namespace CLROBS 
{
    public ref class AbstractPlugin abstract : public Plugin
    {

    private:
        String^ pluginName;
        String^ pluginDescription;

    public:
        AbstractPlugin();
        ~AbstractPlugin();
    public:

        virtual bool LoadPlugin() abstract;
        virtual void UnloadPlugin() abstract;

        virtual void OnStartStream() abstract;
        virtual void OnStopStream() abstract;

        property String^ Name
        {
        public:
            virtual String^ get() sealed;
        protected:
            void set(String^ name);
        }    
        property String^ Description 
        {
        public:
            virtual String^ get() sealed;
        protected:
            void set(String^ description);
        }
    };
};