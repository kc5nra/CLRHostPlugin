#pragma once

#include "Plugin.h"
#include "API.h"

using namespace CLROBS;

namespace CLROBS 
{
    public ref class AbstractPlugin abstract : public Plugin
    {

    private:
        API^ api;
        String^ pluginName;
        String^ pluginDescription;

    public:
        AbstractPlugin();
        ~AbstractPlugin();
    public:
        property API^ Api {
            virtual API^ get() sealed;
            virtual void set(API^ api) sealed;
        }

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