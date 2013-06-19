#pragma once

class XElement;

using namespace System::Collections;

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
        void MoveUp();
        void MoveDown();
        void MoveToTop();
        void MoveToBottom();
        
        bool HasItem(System::String^ name);

        System::String^ GetString(System::String^ name);
        System::String^ GetString(System::String^ name, System::String^ defaultValue);
        System::Int32 GetInt(System::String^ name);
        System::Int32 GetInt(System::String^ name, System::Int32 defaultValue);
        float GetFloat(System::String^ name);
        float GetFloat(System::String^ name, float defaultValue);
        System::Int32 GetColor(System::String^ name);
        System::Int32 GetColor(System::String^ name, System::Int32 defaultValue);
        System::Int32 GetHex(System::String^ name);
        System::Int32 GetHex(System::String^ name, System::Int32 defaultValue);
        
        Generic::List<System::String^>^ GetStringList(System::String^ name);
        Generic::List<System::Int32>^ GetIntList(System::String^ name);
        Generic::List<float>^ GetFloatList(System::String^ name);
        Generic::List<System::Int32>^ GetColorList(System::String^ name);
        Generic::List<System::Int32>^ GetHexList(System::String^ name);

        void SetString(System::String^ name, System::String^ string);
        void SetInt(System::String^ name, System::Int32 number);
        void SetFloat(System::String^ name, float number);
        void SetHex(System::String^ name, System::Int32 hex);
        void SetColor(System::String^ name, System::Int32 color);

        void SetStringList(System::String^ name, Generic::List<System::String^>^ list);
        void SetIntList(System::String^ name, Generic::List<System::Int32>^ list);
        void SetFloatList(System::String^ name, Generic::List<float>^ list);
        void SetHexList(System::String^ name, Generic::List<System::Int32>^ list);
        void SetColorList(System::String^ name, Generic::List<System::Int32>^ list);
        
        void AddString(System::String^ name, System::String^ string);
        void AddInt(System::String^ name, System::Int32 number);
        void AddFloat(System::String^ name, float number);
        void AddHex(System::String^ name, System::Int32 hex);
        void AddColor(System::String^ name, System::Int32 color);
    };   
};