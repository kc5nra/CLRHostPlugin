#include "XElement.h"
#include "OBSApi.h"
#include "OBSUtils.h"

namespace CLROBS
{
    System::String^ XElement::Name::get()
    {
        return gcnew System::String(element->GetName());
    }

    void XElement::Name::set(System::String^ name)
    {
        element->SetName(ToWString(name).c_str());
    }

    bool XElement::Import(System::String^ name)
    {
        return element->Import(ToWString(name).c_str());
    }

    bool  XElement::Export(System::String^ name)
    {
        return element->Export(ToWString(name).c_str());
    }

    bool XElement::HasItem(System::String^ name)
    {
        return element->HasItem(ToWString(name).c_str());
    }

    void XElement::RemoveItem(System::String^ name)
    {
        return element->RemoveItem(ToWString(name).c_str());
    }

    void XElement::ReverseOrder()
    {
        element->ReverseOrder();
    }

    void XElement::MoveUp()
    {
        element->MoveUp();
    }

    void XElement::MoveDown()
    {
        element->MoveDown();
    }

    void XElement::MoveToTop()
    {
        element->MoveToTop();
    }

    void XElement::MoveToBottom()
    {
        element->MoveToBottom();
    }

    XElement^ XElement::Parent::get()
    {
        ::XElement *elementPtr = element->GetParent();
        return elementPtr ? gcnew XElement(elementPtr) : nullptr;
    }

    System::Int32 XElement::ElementCount()
    {
        return element->NumElements();
    }

    System::Int32 XElement::ElementCount(System::String^ name)
    {
        return element->NumElements(ToWString(name).c_str());
    }

    XElement^ XElement::GetElement(System::String^ name)
    {
        ::XElement *elementPtr = element->GetElement(ToWString(name).c_str());
        return elementPtr ? gcnew XElement(elementPtr) : nullptr;
    }

    XElement^ XElement::GetElementById(System::Int32 elementId)
    {
        ::XElement *elementPtr = element->GetElementByID(elementId);
        return elementPtr ? gcnew XElement(elementPtr) : nullptr;
    }

    XElement^ XElement::GetElementByItem(
        System::String^ name,
        System::String^ itemName,
        System::String^ itemValue)
    {
        ::XElement *elementPtr = element->GetElementByItem(
            ToWString(name).c_str(),
            ToWString(itemName).c_str(),
            ToWString(itemValue).c_str());

        return elementPtr ? gcnew XElement(elementPtr) : nullptr;
    }

    XElement^ XElement::CreateElement(System::String^ name)
    {
        ::XElement *elementPtr = element->CreateElement(
            ToWString(name).c_str());
        return elementPtr ? gcnew XElement(elementPtr) : nullptr;
    }

    XElement^ XElement::InsertElement(
        System::Int32 position,
        System::String^ name)
    {
        ::XElement *elementPtr = element->InsertElement(position,
            ToWString(name).c_str());
        return elementPtr ? gcnew XElement(elementPtr) : nullptr;
    }

    XElement^ XElement::CopyElement(
        XElement^ elementToCopy,
        System::String^ newName)
    {
        ::XElement *elementPtr = element->CopyElement(
            elementToCopy->element,
            ToWString(newName).c_str());
        return elementPtr ? gcnew XElement(elementPtr) : nullptr;
    }

    Generic::List<XElement^>^ XElement::GetElementList(System::String^ name)
    {
        List<::XElement *> list;
        element->GetElementList(ToWString(name).c_str(), list);
        auto returnList = gcnew Generic::List<XElement ^>();
        for (unsigned int i = 0; i < list.Num(); i++) {
            returnList->Add(gcnew XElement(list[i]));
        }
        return returnList;
    }

    void XElement::RemoveElement(XElement^ elementToRemove)
    {
        element->RemoveElement(elementToRemove->element);
    }

    void XElement::RemoveElement(System::String^ name)
    {
        element->RemoveElement(ToWString(name).c_str());
    }

    System::String^ XElement::GetString(System::String^ name)
    {
        return GetString(name, gcnew System::String(""));
    }

    System::String^ XElement::GetString(
        System::String^ name,
        System::String^ defaultValue)
    {
        return gcnew System::String(
            element->GetString(
            ToWString(name).c_str(),
            (TSTR) ToWString(defaultValue).c_str()
            )
            );
    }

    System::Int32 XElement::GetInt(
        System::String^ name)
    {
        return GetInt(name, 0);
    }

    System::Int32 XElement::GetInt(
        System::String^ name,
        System::Int32 defaultValue)
    {
        return element->GetInt(ToWString(name).c_str(), defaultValue);
    }

    float XElement::GetFloat(
        System::String^ name)
    {
        return GetFloat(name, 0.0f);
    }

    float XElement::GetFloat(
        System::String^ name,
        float defaultValue)
    {
        return element->GetFloat(ToWString(name).c_str(), defaultValue);
    }

    System::Int32 XElement::GetColor(
        System::String^ name)
    {
        return GetColor(name, 0);
    }

    System::Int32 XElement::GetColor(
        System::String^ name,
        System::Int32 defaultValue)
    {
        return element->GetColor(ToWString(name).c_str(), defaultValue);
    }

    System::Int32 XElement::GetHex(System::String^ name)
    {
        return GetHex(name, 0);
    }

    System::Int32 XElement::GetHex(
        System::String^ name,
        System::Int32 defaultValue)
    {
        return element->GetHex(ToWString(name).c_str(), defaultValue);
    }

    Generic::List<System::String^>^ XElement::GetStringList(
        System::String^ name)
    {
        StringList list;
        element->GetStringList(ToWString(name).c_str(), list);
        auto returnList = gcnew Generic::List<System::String^>();
        for (unsigned int i = 0; i < list.Num(); i++) {
            returnList->Add(gcnew System::String(list[i]));
        }
        return gcnew Generic::List<System::String^>();
    }

    Generic::List<System::Int32>^ XElement::GetIntList(System::String^ name)
    {
        List<int> list;
        element->GetIntList(ToWString(name).c_str(), list);
        auto returnList = gcnew Generic::List<System::Int32>();
        for (unsigned int i = 0; i < list.Num(); i++) {
            returnList->Add(list[i]);
        }
        return returnList;
    }

    Generic::List<float>^ XElement::GetFloatList(System::String^ name)
    {
        throw gcnew System::NotImplementedException();

        // this seems to not be implemented in OBS

        /*List<float> list;
        element->GetFloatList(ToWString(name).c_str(), list);
        auto returnList = gcnew Generic::List<float>();
        for(unsigned int i = 0; i < list.Num(); i++) {
        returnList->Add(list[i]);
        }
        return returnList;*/
    }

    Generic::List<System::Int32>^ XElement::GetColorList(System::String^ name)
    {
        List<int> list;
        element->GetIntList(ToWString(name).c_str(), list);
        auto returnList = gcnew Generic::List<System::Int32>();
        for (unsigned int i = 0; i < list.Num(); i++) {
            returnList->Add(list[i]);
        }
        return returnList;
    }

    Generic::List<System::Int32>^ XElement::GetHexList(System::String^ name)
    {
        List<int> list;
        element->GetIntList(ToWString(name).c_str(), list);
        auto returnList = gcnew Generic::List<System::Int32>();
        for (unsigned int i = 0; i < list.Num(); i++) {
            returnList->Add(list[i]);
        }
        return returnList;
    }

    void XElement::SetString(
        System::String^ name,
        System::String^ string)
    {
        element->SetString(ToWString(name).c_str(), ToWString(string).c_str());
    }

    void XElement::SetInt(
        System::String^ name,
        System::Int32 number)
    {
        element->SetInt(ToWString(name).c_str(), number);
    }

    void XElement::SetFloat(
        System::String^ name,
        float number)
    {
        element->SetFloat(ToWString(name).c_str(), number);
    }

    void XElement::SetHex(
        System::String^ name,
        System::Int32 hex)
    {
        element->SetHex(ToWString(name).c_str(), hex);
    }

    void XElement::SetColor(
        System::String^ name,
        System::Int32 color)
    {
        SetHex(name, color);
    }

    void XElement::SetStringList(
        System::String^ name,
        Generic::List<System::String^>^ list)
    {
        StringList _list;
        for (int i = 0; i < list->Count; i++) {
            _list.Add(ToWString(list[i]).c_str());
        }
        element->SetStringList(ToWString(name).c_str(), _list);
    }

    void XElement::SetIntList(
        System::String^ name,
        Generic::List<System::Int32>^ list)
    {
        List<int> _list;
        for (int i = 0; i < list->Count; i++) {
            _list.Add(list[i]);
        }
        element->SetIntList(ToWString(name).c_str(), _list);
    }

    void XElement::SetFloatList(
        System::String^ name,
        Generic::List<float>^ list)
    {
        List<float> _list;
        for (int i = 0; i < list->Count; i++) {
            _list.Add(list[i]);
        }
        element->SetFloatList(ToWString(name).c_str(), _list);
    }

    void XElement::SetHexList(
        System::String^ name,
        Generic::List<System::Int32>^ list)
    {
        List<DWORD> _list;
        for (int i = 0; i < list->Count; i++) {
            _list.Add(list[i]);
        }
        element->SetHexList(ToWString(name).c_str(), _list);
    }

    void XElement::SetColorList(
        System::String^ name,
        Generic::List<System::Int32>^ list)
    {
        SetHexList(name, list);
    }

    void XElement::AddString(
        System::String^ name,
        System::String^ string)
    {
        element->AddString(ToWString(name).c_str(),
            (TSTR) ToWString(string).c_str());
    }

    void XElement::AddInt(
        System::String^ name,
        System::Int32 number)
    {
        element->AddInt(ToWString(name).c_str(), number);
    }

    void XElement::AddFloat(
        System::String^ name,
        float number)
    {
        element->AddFloat(ToWString(name).c_str(), number);
    }

    void XElement::AddHex(
        System::String^ name,
        System::Int32 hex)
    {
        element->AddHex(ToWString(name).c_str(), hex);
    }

    void XElement::AddColor(
        System::String^ name,
        System::Int32 color)
    {
        AddHex(name, color);
    }

    void XElement::AddStringList(
        System::String^ name,
        Generic::List<System::String^>^ list)
    {
        StringList _list;
        for (int i = 0; i < list->Count; i++) {
            _list.Add(ToWString(list[i]).c_str());
        }
        element->AddStringList(ToWString(name).c_str(), _list);
    }

    void XElement::AddIntList(
        System::String^ name,
        Generic::List<System::Int32>^ list)
    {
        List<int> _list;
        for (int i = 0; i < list->Count; i++) {
            _list.Add(list[i]);
        }
        element->AddIntList(ToWString(name).c_str(), _list);
    }

    void XElement::AddFloatList(
        System::String^ name,
        Generic::List<float>^ list)
    {
        List<float> _list;
        for (int i = 0; i < list->Count; i++) {
            _list.Add(list[i]);
        }
        element->AddFloatList(ToWString(name).c_str(), _list);
    }

    void XElement::AddHexList(
        System::String^ name,
        Generic::List<System::Int32>^ list)
    {
        List<DWORD> _list;
        for (int i = 0; i < list->Count; i++) {
            _list.Add(list[i]);
        }
        element->AddHexList(ToWString(name).c_str(), _list);
    }

    void XElement::AddColorList(
        System::String^ name,
        Generic::List<System::Int32>^ list)
    {
        AddHexList(name, list);
    }
}