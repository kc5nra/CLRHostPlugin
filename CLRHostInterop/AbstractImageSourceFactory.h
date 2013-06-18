#pragma once

#include "ImageSourceFactory.h"
#include "ImageSource.h"

using namespace System;
using namespace CLROBS;

namespace CLROBS 
{
    public ref class AbstractImageSourceFactory abstract : public ImageSourceFactory
    {
    private:
        String^ className;
        String^ displayName;

    public:
        AbstractImageSourceFactory();

        virtual ImageSource^ Create(XElement^ data) abstract;
        virtual void ShowConfiguration(XElement^ data) abstract;

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