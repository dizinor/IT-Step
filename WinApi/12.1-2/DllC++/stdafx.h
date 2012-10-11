// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#ifdef DllExport
#define DllExport extern "C" _declspec(dllexport)
#else
#define DllExport extern "C" _declspec(dllimport)
#endif
#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>
#include <tchar.h>
#include <CommCtrl.h>
#include <iostream>
using namespace std;

// TODO: reference additional headers your program requires here

DllExport BOOL WinDll(HWND, int, int, int, bool);
DllExport BOOL ConsoleDll();