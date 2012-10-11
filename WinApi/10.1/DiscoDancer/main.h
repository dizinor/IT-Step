#include <Windows.h>
#include <WindowsX.h>
#include <CommCtrl.h>
#include <time.h>
#include "resource.h"

#pragma comment(lib, "comctl32")

BOOL CALLBACK DlgProc(HWND hWnd, UINT nMessage, WPARAM wParam, LPARAM lParam);
DWORD WINAPI ThreadFunc(LPVOID lpParam);