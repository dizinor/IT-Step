#include <Windows.h>
#include <tchar.h>
#include <WindowsX.h>
#include "resource.h"
#pragma once

BOOL CALLBACK DlgProc(HWND hWnd, UINT nMes, WPARAM wParam, LPARAM lParam);

void OnClose(HWND hWnd);
BOOL OnInitDialog(HWND hWnd, HWND hWndFocus, LPARAM lParam);
void OnCommand(HWND hWnd, int id, HWND hWndCtrl, UINT CodeNotify);