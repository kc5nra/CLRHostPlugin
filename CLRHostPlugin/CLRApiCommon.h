#pragma once

#ifdef CLR_DLL
#define CLR_API __declspec(dllexport)
#else
#define CLR_API __declspec(dllimport)
#endif