#include "XConfig.h"
#include "OBSApi.h"

#include <msclr\marshal_cppstd.h>

using namespace msclr::interop;
using namespace CLROBS;

System::String^ CLROBS::XElement::Name::get() 
{ 
    return gcnew System::String(element->GetName()); 
}
            
void CLROBS::XElement::Name::set(System::String^ name) 
{ 
    std::wstring wstrName = marshal_as<std::wstring, System::String^>(name);
    element->SetName(wstrName.c_str());
}


void CLROBS::XElement::ReverseOrder() { 
    element->ReverseOrder(); 
}
