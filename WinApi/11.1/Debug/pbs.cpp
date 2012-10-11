#include <windows.h>
#include <windowsx.h>
#include <tchar.h>
#include <commctrl.h>
#include "resource.h"
#pragma comment(lib,"comctl32")

HANDLE hThread, hCopyStatus[2];
HWND hStatPercent,hStat,hProgressBar;
HINSTANCE hInst;

LONG range;     
BOOL bStop;

DWORD WINAPI ThreadFunc(LPVOID lpv);

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

	HWND hDialog;
	hDialog = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
	ShowWindow(hDialog, nCmdShow); 
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
		hInst = GetModuleHandle(NULL);
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
		DestroyWindow(hWnd); 
		PostQuitMessage(0);
		CloseHandle(hCopyStatus[0]);
		CloseHandle(hCopyStatus[1]);
		return TRUE;
	}
	return FALSE;
}

DWORD CALLBACK ProgressRoutine(
    LARGE_INTEGER TotalFileSize,
    LARGE_INTEGER TotalBytesTransferred,
    LARGE_INTEGER StreamSize,
    LARGE_INTEGER StreamBytesTransferred,
    DWORD dwStreamNumber,
    DWORD dwCallbackReason,
    HANDLE hSourceFile,
    HANDLE hDestinationFile,
    LPVOID lpData
)
{
	TCHAR pOutMessage[100],text[200];
	range=64000;
	if(!bStop)
	{
		SendMessage((HWND)lpData, PBM_SETRANGE32, 0, range);
		SendMessage((HWND)lpData,PBM_SETPOS , range*TotalBytesTransferred.QuadPart / TotalFileSize.QuadPart, 0);
		double percentage;
		percentage = 100.0 * (double)TotalBytesTransferred.QuadPart  / (double)TotalFileSize.QuadPart;
		_stprintf(text, _T(" %.0f %% - %d"), percentage,StreamBytesTransferred.QuadPart); 
		SetWindowText(hStatPercent,text);
		_stprintf(pOutMessage,_T(" %d bytes"), StreamSize.QuadPart);				
		SetWindowText(hStat,pOutMessage);
		return PROGRESS_CONTINUE;
	}
	else return PROGRESS_CANCEL;
}

DWORD WINAPI ThreadFunc(LPVOID lpv)
{
	HWND hParent;
	hParent = (HWND)lpv;
	SetWindowText(hParent, _T("Copy..."));
	const TCHAR *FileFrom = _T("pbs.cpp");
	const TCHAR *FileTo = _T("new.1");
	BOOL copied = CopyFileEx(FileFrom, FileTo, ProgressRoutine, hProgressBar, 0, COPY_FILE_RESTARTABLE);		
	if(copied)
	{
		SetWindowText(hParent,_T("Ready"));
		EnableWindow(GetDlgItem(hParent,IDC_STOP),FALSE);
		SetEvent(hCopyStatus[0]);
	}
	else 
	{
		SetWindowText(hParent, _T("Stopped"));
		SetEvent(hCopyStatus[1]);
	}
	EnableWindow(GetDlgItem(hParent,IDC_START),TRUE);	
	CloseHandle(hThread);
	return 0;
}

BOOL CALLBACK DialogProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		HANDLE_MSG(hWnd, WM_INITDIALOG, OnInitDialog);		
		HANDLE_MSG(hWnd, WM_COMMAND, OnCommand);
		HANDLE_MSG(hWnd, WM_CLOSE, OnClose);
	}
	return FALSE;
}

BOOL OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	hCopyStatus[0] = CreateEvent(NULL, FALSE, TRUE, NULL);
	hCopyStatus[1] = CreateEvent(NULL, FALSE, TRUE, NULL);
	hProgressBar = GetDlgItem(hwnd, IDC_PROGRESS1);	
	hStat=GetDlgItem(hwnd, IDC_STAT);
	hStatPercent = GetDlgItem(hwnd, IDC_PERCENT);
	EnableWindow(GetDlgItem(hwnd, IDC_STOP), bStop);
	return TRUE;
}

void OnCommand(HWND hwnd, int id,HWND hwndCtl, UINT codeNotify)
{
	switch(id)
	{
	case IDC_START:
		{
			hThread = CreateThread(NULL, 0, ThreadFunc, hwnd, CREATE_SUSPENDED, NULL);
			SetThreadPriority(hThread, THREAD_PRIORITY_BELOW_NORMAL);
			ResumeThread(hThread);
			DWORD dw;
			dw = WaitForMultipleObjects(2, hCopyStatus, FALSE, INFINITE);
			switch(dw)
			{
			case 0:
				MessageBox(hwnd, _T("Копирование удалось"), 0, 0);
				break;
			case 1:
				MessageBox(hwnd, _T("Копирование не удалось"), 0, 0);
				break;
			};
			bStop = FALSE;
			EnableWindow(GetDlgItem(hwnd, IDC_STOP), TRUE);
			EnableWindow(GetDlgItem(hwnd, IDC_START), bStop);
		}
		break;
	case IDC_STOP:
		bStop = TRUE;
		EnableWindow(GetDlgItem(hwnd, IDC_STOP), FALSE);
		EnableWindow(GetDlgItem(hwnd, IDC_START), bStop);
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