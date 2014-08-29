#pragma once

#include "Plugin.h"
#include "API.h"

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

        virtual bool LoadPlugin()
        {
            return true;
        };

        virtual void UnloadPlugin()
        {};
        virtual void OnStartStream()
        {};
        virtual void OnStopStream()
        {};

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