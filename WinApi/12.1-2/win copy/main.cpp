#include <windows.h>
#include <windowsx.h>
#include <tchar.h>
#include <commctrl.h>
#include "resource.h"
#include "..\\DllC++\\stdafx.h"
#pragma comment(lib, "comctl32")
#pragma comment(lib, "..\\Debug\\DllC++.lib")

HANDLE hThread;

DWORD WINAPI ThreadFunc(LPVOID lpv);
HWND hStatPercent,hStat,hProgressBar;
HINSTANCE hInst;

LONG range;      // диапазон для индикатора процесса

BOOL bStop;

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

BOOL CALLBACK DialogProc(HWND , UINT , WPARAM , LPARAM );
BOOL OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
void OnCommand(HWND hwnd, int id,HWND hwndCtl, UINT codeNotify);
void OnClose(HWND hwnd);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int nCmdShow)
{
	MSG msg;
	INITCOMMONCONTROLSEX icc = {sizeof(INITCOMMONCONTROLSEX)};
	icc.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&icc);
	// создаём главное окно приложения на основе немодального диалога
	HWND hDialog = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
	// Отображаем окно	
	ShowWindow(hDialog, nCmdShow); 
	//Запускаем цикл обработки сообщений
	while(GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch(message)
	{
	case WM_INITDIALOG:
		hInst=GetModuleHandle(NULL);
		return TRUE;
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
			case IDC_BUTTON1:
			DialogBox(hInst,MAKEINTRESOURCE(IDD_DIALOG2),NULL,DialogProc);			
			break;
		}
		return TRUE;
	case WM_CLOSE:
		// закрываем немодальный диалог
		DestroyWindow(hWnd); // разрушаем окно
		PostQuitMessage(0); // останавливаем цикл обработки сообщений
		return TRUE;
		

	}
	return FALSE;
}

BOOL CALLBACK DialogProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		HANDLE_MSG(hWnd,WM_INITDIALOG,OnInitDialog);		
		HANDLE_MSG(hWnd,WM_COMMAND,OnCommand);
		HANDLE_MSG(hWnd,WM_CLOSE,OnClose);

	}
	return FALSE;

}

BOOL OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{

	hProgressBar=GetDlgItem(hwnd,IDC_PROGRESS1);	
	hStat=GetDlgItem(hwnd,IDC_STAT);
	hStatPercent=GetDlgItem(hwnd,IDC_PERCENT);
	EnableWindow(GetDlgItem(hwnd,IDC_STOP),bStop);
	return TRUE;
}

void OnCommand(HWND hwnd, int id,HWND hwndCtl, UINT codeNotify)
{
	switch(id)
	{
	case IDC_START:
		WinDll(hwnd, IDC_PROGRESS1, IDC_STAT, IDC_PERCENT, bStop);	
		EnableWindow(GetDlgItem(hwnd,IDC_STOP),TRUE);
		EnableWindow(GetDlgItem(hwnd,IDC_START),bStop);
		break;

	case IDC_STOP:
		bStop=TRUE;
		EnableWindow(GetDlgItem(hwnd,IDC_STOP),FALSE);
		EnableWindow(GetDlgItem(hwnd,IDC_START),bStop);
		if(hThread)
			CloseHandle(hThread);
		break;
	}

}
void OnClose(HWND hwnd)
{
	EndDialog(hwnd,0);
	if(hThread)
			CloseHandle(hThread);

}