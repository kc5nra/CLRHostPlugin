#pragma once

#include "ImageSourceFactory.h"
#include "ImageSource.h"
#include "API.h"

using namespace System;
using namespace System::Windows;
using namespace System::Windows::Interop;

namespace CLROBS
{
    public ref class AbstractImageSourceFactory abstract : public ImageSourceFactory
    {
    private:
        String^ className;
        String^ displayName;

    public:
        AbstractImageSourceFactory();

    public: // ImageSourceFactory

        virtual ImageSource^ Create(XElement^ data) abstract;
        virtual bool ShowConfiguration(XElement^ data) abstract;

        property String^ DisplayName
        {
        public:
            virtual String^ get() sealed;
        protected:
            void set(String^ displayName);
        }

        property String^ ClassName
        {
        public:
            virtual String^ get() sealed;
        protected:
            void set(String^ className);
        }
    };
};