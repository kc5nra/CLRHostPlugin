#pragma once

class XElement;

namespace CLROBS {
    public ref class XElement
    {
    private:
        ::XElement *element;
    
    public:
        XElement(long element) 
        {
            this->element = (::XElement *)System::IntPtr(element).ToPointer();
        }
    
    public: //XBaseItem
        
        property System::String^ Name 
        {
        public:
            System::String^ get();
            void set(System::String^ name);
        }

    public:
        void ReverseOrder();
    };   
};