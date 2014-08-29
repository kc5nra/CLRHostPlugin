#pragma once

class XElement;

using namespace System::Collections;

namespace CLROBS
{
    /// <summary>
    /// XElement allows you to marshal and unmarshal config
    /// information from a file in a JSON-like format</summary>
    public ref class XElement
    {
    private:
        ::XElement *element;

    public:
        XElement(long long elementPtr)
        {
            this->element = reinterpret_cast<::XElement *>(elementPtr);
        }

        XElement(void *elementPtr)
        {
            this->element = static_cast<::XElement *>(elementPtr);
        }

    public:
        static bool operator == (XElement^ a, XElement^ b)
        {
            if (System::Object::ReferenceEquals(a, b)) {
                return true;
            }

            return a->element == b->element;
        }

        static bool operator != (XElement^ a, XElement^ b)
        {
            return a->element != b->element;
        }

        virtual bool Equals(System::Object^ object) override
        {
            XElement^ comparedToElement = static_cast<XElement ^>(object);
            if (object == nullptr) {
                return false;
            }
            return element == comparedToElement->element;
        }

        virtual int GetHashCode() override
        {
            return (int) element;
        }

    public: //XBaseItem

        property System::String^ Name
        {
        public:
            System::String^ get();
            void set(System::String^ name);
        }

    public:

        bool Import(System::String^ name);
        bool Export(System::String^ name);

        bool HasItem(System::String^ name);
        void RemoveItem(System::String^ name);

        void ReverseOrder();
        void MoveUp();
        void MoveDown();
        void MoveToTop();
        void MoveToBottom();

        property XElement^ Parent
        {
        public:
            CLROBS::XElement^ get();
        }

        System::Int32 ElementCount();
        System::Int32 ElementCount(System::String^ name);

        XElement^ GetElement(System::String^ name);
        XElement^ GetElementById(System::Int32 elementId);
        XElement^ GetElementByItem(System::String^ name, System::String^ itemName, System::String^ itemValue);
        XElement^ CreateElement(System::String^ name);
        XElement^ InsertElement(System::Int32 position, System::String^ name);
        XElement^ CopyElement(XElement^ name, System::String^ newName);
        Generic::List<XElement^>^ GetElementList(System::String^ name);
        void  RemoveElement(XElement^ element);
        void  RemoveElement(System::String^ name);

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

        void AddStringList(System::String^ name, Generic::List<System::String^>^ list);
        void AddIntList(System::String^ name, Generic::List<System::Int32>^ list);
        void AddFloatList(System::String^ name, Generic::List<float>^ list);
        void AddHexList(System::String^ name, Generic::List<System::Int32>^ list);
        void AddColorList(System::String^ name, Generic::List<System::Int32>^ list);
    };
};