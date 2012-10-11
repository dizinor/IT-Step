// DllC++.cpp : Defines the exported functions for the DLL application.
//
#define DllExport
#include "stdafx.h"

HWND hStatPercent,hStat,hProgressBar;

INT IDC_STOP, IDC_START;

BOOL bStop;

BOOL InitWnd(HWND hwnd, int IDC_PROGRESS1, int IDC_STAT, int IDC_PERCENT, bool bStop)
{
	hProgressBar = GetDlgItem(hwnd, IDC_PROGRESS1);	
	hStat=GetDlgItem(hwnd, IDC_STAT);
	hStatPercent = GetDlgItem(hwnd, IDC_PERCENT);
	EnableWindow(GetDlgItem(hwnd, IDC_STOP), bStop);
	return TRUE;
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
	LONG range;
	range = 64000;
	bStop = FALSE;
	if(!bStop)
	{
		SendMessage((HWND)lpData, PBM_SETRANGE32, 0, range);
		SendMessage((HWND)lpData,PBM_SETPOS , range * TotalBytesTransferred.QuadPart / TotalFileSize.QuadPart, 0);
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

DWORD WINAPI WinCopy(LPVOID lpv)
{
	HWND hParent;
	hParent = (HWND)lpv;
	const TCHAR *FileFrom = _T("pbs.cpp");
	const TCHAR *FileTo = _T("new.1");
	BOOL copied = CopyFileEx(FileFrom, FileTo, ProgressRoutine, hProgressBar, 0, COPY_FILE_RESTARTABLE);		
	if(copied)
	{
		MessageBox(0, _T("Копирование удалось."), 0, 0);
		EnableWindow(GetDlgItem(hParent, IDC_STOP),FALSE);
	}
	else 
	{
		MessageBox(0, _T("Копирование не удалось."), 0, 0);
	}
	EnableWindow(GetDlgItem(hParent, IDC_START),TRUE);	
	return 0;
}

DWORD WINAPI ConsoleCopy(LPVOID lpv)
{
	const TCHAR *FileFrom = _T("pbs.cpp");
	const TCHAR *FileTo = _T("new.1");
	BOOL copied = CopyFile(FileFrom, FileTo, TRUE);		
	if(copied)
		std::cout<<"Copy complete\n";
	else 
		std::cout<<"Copy failed\n";
	return 0;
}

BOOL WinDll(HWND hwnd, int IDC_PROGRESS1, int IDC_STAT, int IDC_PERCENT, bool bStop)
{
	HANDLE hThread;
	InitWnd(hwnd, IDC_PROGRESS1, IDC_STAT, IDC_PERCENT, bStop);
	hThread = CreateThread(NULL, 0, WinCopy, hwnd, CREATE_SUSPENDED, NULL);
	SetThreadPriority(hThread,THREAD_PRIORITY_BELOW_NORMAL);
	ResumeThread(hThread);
	bStop = FALSE;
	return TRUE;
}

BOOL ConsoleDll()
{
	HANDLE hThread;
	hThread = CreateThread(NULL, 0, ConsoleCopy, NULL, 0, NULL);
	SetThreadPriority(hThread,THREAD_PRIORITY_BELOW_NORMAL);
	ResumeThread(hThread);
	bStop = FALSE;
	WaitForSingleObject(hThread, INFINITE);
	CloseHandle(hThread);
	return TRUE;
}