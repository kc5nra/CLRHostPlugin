#include "OBSApi.h"
#include "CLRHostApi.h"

void CLRHostApi::OBSLog(std::wstring &logMessage)
{
    Log(TEXT("CLRApi>> %s"), logMessage.c_str());
}

void CLRHostApi::Hello()
{

}
