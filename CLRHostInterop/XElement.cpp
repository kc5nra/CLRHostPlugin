#include "XElement.h"
#include "OBSApi.h"

#include <msclr\marshal_cppstd.h>

using namespace msclr::interop;
using namespace CLROBS;

std::wstring ToWString(System::String^ string)
{
    return marshal_as<std::wstring, System::String^>(string);
}

System::String^ CLROBS::XElement::Name::get() 
{ 
    return gcnew System::String(element->GetName()); 
}
            
void CLROBS::XElement::Name::set(System::String^ name) 
{ 
    element->SetName(ToWString(name).c_str());
}


void CLROBS::XElement::ReverseOrder() { 
    element->ReverseOrder(); 
}

void CLROBS::XElement::MoveUp()
{
    element->MoveUp();
}

void CLROBS::XElement::MoveDown()
{
    element->MoveDown();
}
void CLROBS::XElement::MoveToTop()
{
    element->MoveToTop();
}
void CLROBS::XElement::MoveToBottom()
{
    element->MoveToBottom();
}

bool CLROBS::XElement::HasItem(System::String^ name)
{
    return element->HasItem(ToWString(name).c_str());
}

System::String^ CLROBS::XElement::GetString(System::String^ name) { 
    return GetString(name, gcnew System::String("")); 
}

System::String^ CLROBS::XElement::GetString(
    System::String^ name, 
    System::String^ defaultValue)
{
    return gcnew System::String(
        element->GetString(
            ToWString(name).c_str(), 
            (TSTR)ToWString(defaultValue).c_str()
        )
    );
}

System::Int32 CLROBS::XElement::GetInt(
    System::String^ name)
{
    return GetInt(name, 0);
}

System::Int32 CLROBS::XElement::GetInt(
    System::String^ name, 
    System::Int32 defaultValue)
{
    return element->GetInt(ToWString(name).c_str(), defaultValue);
}

float CLROBS::XElement::GetFloat(
    System::String^ name)
{
    return GetFloat(name, 0.0f);
}

float CLROBS::XElement::GetFloat(
    System::String^ name, 
    float defaultValue)
{
    return element->GetFloat(ToWString(name).c_str(), defaultValue);
}
System::Int32 CLROBS::XElement::GetColor(
    System::String^ name)
{
    return GetColor(name, 0);
}

System::Int32 CLROBS::XElement::GetColor(
    System::String^ name, 
    System::Int32 defaultValue)
{
    return element->GetColor(ToWString(name).c_str(), defaultValue);    
}

System::Int32 CLROBS::XElement::GetHex(
    System::String^ name)
{
    return GetHex(name, 0);
}

System::Int32 CLROBS::XElement::GetHex(
    System::String^ name, 
    System::Int32 defaultValue)
{
    return element->GetHex(ToWString(name).c_str(), defaultValue);
}
        
Generic::List<System::String^>^ CLROBS::XElement::GetStringList(System::String^ name)
{
    StringList list;
    element->GetStringList(ToWString(name).c_str(), list);
    auto returnList = gcnew Generic::List<System::String^>();
    for(unsigned int i = 0; i < list.Num(); i++) {
        returnList->Add(gcnew System::String(list[i]));
    }
    return gcnew Generic::List<System::String^>();
}

Generic::List<System::Int32>^ CLROBS::XElement::GetIntList(System::String^ name)
{
    List<int> list;
    element->GetIntList(ToWString(name).c_str(), list);
    auto returnList = gcnew Generic::List<System::Int32>();
    for(unsigned int i = 0; i < list.Num(); i++) {
        returnList->Add(list[i]);
    }
    return returnList;
}

Generic::List<float>^ CLROBS::XElement::GetFloatList(System::String^ name)
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

Generic::List<System::Int32>^ CLROBS::XElement::GetColorList(System::String^ name)
{
    List<int> list;
    element->GetIntList(ToWString(name).c_str(), list);
    auto returnList = gcnew Generic::List<System::Int32>();
    for(unsigned int i = 0; i < list.Num(); i++) {
        returnList->Add(list[i]);
    }
    return returnList;
}

Generic::List<System::Int32>^ CLROBS::XElement::GetHexList(System::String^ name)
{
    List<int> list;
    element->GetIntList(ToWString(name).c_str(), list);
    auto returnList = gcnew Generic::List<System::Int32>();
    for(unsigned int i = 0; i < list.Num(); i++) {
        returnList->Add(list[i]);
    }
    return returnList;
}

void CLROBS::XElement::SetString(System::String^ name, System::String^ string)
{
    element->SetString(ToWString(name).c_str(), ToWString(string).c_str());
}

void CLROBS::XElement::SetInt(System::String^ name, System::Int32 number)
{
    element->SetInt(ToWString(name).c_str(), number);
}

void CLROBS::XElement::SetFloat(System::String^ name, float number)
{
    element->SetFloat(ToWString(name).c_str(), number);
}

void CLROBS::XElement::SetHex(System::String^ name, System::Int32 hex)
{
    element->SetHex(ToWString(name).c_str(), hex);
}

void CLROBS::XElement::SetColor(System::String^ name, System::Int32 color)
{
    SetHex(name, color);
}

void CLROBS::XElement::SetStringList(System::String^ name, Generic::List<System::String^>^ list)
{
    StringList _list;
    for(int i = 0; i < list->Count; i++) {
        _list.Add(ToWString(list[i]).c_str());
    }
    element->SetStringList(ToWString(name).c_str(), _list);
}

void CLROBS::XElement::SetIntList(System::String^ name, Generic::List<System::Int32>^ list)
{
    List<int> _list;
    for(int i = 0; i < list->Count; i++) {
        _list.Add(list[i]);
    }
    element->SetIntList(ToWString(name).c_str(), _list);
}

void CLROBS::XElement::SetFloatList(System::String^ name, Generic::List<float>^ list)
{
    List<float> _list;
    for(int i = 0; i < list->Count; i++) {
        _list.Add(list[i]);
    }
    element->SetFloatList(ToWString(name).c_str(), _list);
}

void CLROBS::XElement::SetHexList(System::String^ name, Generic::List<System::Int32>^ list)
{
    List<DWORD> _list;
    for(int i = 0; i < list->Count; i++) {
        _list.Add(list[i]);
    }
    element->SetHexList(ToWString(name).c_str(), _list);
}

void CLROBS::XElement::SetColorList(System::String^ name, Generic::List<System::Int32>^ list)
{
    SetHexList(name, list);
}

void CLROBS::XElement::AddString(System::String^ name, System::String^ string)
{
    element->AddString(ToWString(name).c_str(), (TSTR)ToWString(string).c_str());
}

void CLROBS::XElement::AddInt(System::String^ name, System::Int32 number)
{
    element->AddInt(ToWString(name).c_str(), number);
}

void CLROBS::XElement::AddFloat(System::String^ name, float number)
{
    element->AddFloat(ToWString(name).c_str(), number);
}

void CLROBS::XElement::AddHex(System::String^ name, System::Int32 hex)
{
    element->AddHex(ToWString(name).c_str(), hex);
}

void CLROBS::XElement::AddColor(System::String^ name, System::Int32 color)
{
    AddHex(name, color);
}
