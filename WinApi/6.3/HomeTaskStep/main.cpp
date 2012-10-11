#include <Windows.h>
#include <WindowsX.h>
#include <tchar.h>
#include <CommCtrl.h>
#include "resource.h"

#pragma comment(lib, "comctl32")

BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wParam, LPARAM lParam);
VOID OnClose(HWND hWnd);
BOOL OnInitDlg(HWND hWnd, HWND hWndFocus, LPARAM lParam);
VOID OnCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify);
VOID OnHScroll(HWND hwnd, HWND hwndCtl, UINT code, int pos);

DWORD dwRed;
DWORD dwGreen;
DWORD dwBlue;
TCHAR lpName[100];

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdLine){
	INITCOMMONCONTROLSEX icc = {sizeof(INITCOMMONCONTROLSEX)};
	icc.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&icc);
	return DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wParam, LPARAM lParam){
	switch(mes){
		HANDLE_MSG(hWnd, WM_CLOSE, OnClose);
		HANDLE_MSG(hWnd, WM_INITDIALOG, OnInitDlg);
		HANDLE_MSG(hWnd, WM_HSCROLL, OnHScroll);
	}
	return false;
}

VOID OnClose(HWND hWnd){
	EndDialog(hWnd, 0);
}

BOOL OnInitDlg(HWND hWnd, HWND hWndFocus, LPARAM lParam){
	for (int i = IDC_SLIDER1; i <= IDC_SLIDER3; i++){
		SendDlgItemMessage(hWnd, i, TBM_SETRANGE, true, MAKELPARAM(0, 255));
	}
	SendDlgItemMessage(hWnd, IDC_PROGRESS1, PBM_SETBKCOLOR, 0, (LPARAM)RGB(dwRed,dwGreen,dwBlue));
	wsprintf(lpName, _T("Red: %d, Green: %d, Blue: %d"), dwRed, dwGreen, dwBlue);
	SetWindowText(hWnd, lpName);
	return true;
}

VOID OnHScroll(HWND hWnd, HWND hWndCtl, UINT code, int pos){
	dwRed = SendDlgItemMessage(hWnd, IDC_SLIDER1, TBM_GETPOS, 0, 0);
	dwGreen = SendDlgItemMessage(hWnd, IDC_SLIDER2, TBM_GETPOS, 0, 0);
	dwBlue = SendDlgItemMessage(hWnd, IDC_SLIDER3, TBM_GETPOS, 0, 0);
	SendDlgItemMessage(hWnd, IDC_PROGRESS1, PBM_SETBKCOLOR, 0, LPARAM(RGB(dwRed,dwGreen,dwBlue)));
	wsprintf(lpName, _T("Red: %d, Green: %d, Blue: %d"), dwRed, dwGreen, dwBlue);
	SetWindowText(hWnd, lpName);
}