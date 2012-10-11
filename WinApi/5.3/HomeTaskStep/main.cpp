#include <Windows.h>
#include <WindowsX.h>
#include <tchar.h>
#include "resource.h"

BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wParam, LPARAM lParam);
VOID OnClose(HWND);
BOOL OnInitDlg(HWND, HWND, LPARAM);
VOID OnCommand(HWND, int, HWND, UINT);

TCHAR lpDriveName[] = _T("n:\\");
DWORD dwDrives;

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdLine){
	return DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wParam, LPARAM lParam){
	switch(mes){
		HANDLE_MSG(hWnd, WM_CLOSE, OnClose);
		HANDLE_MSG(hWnd, WM_INITDIALOG, OnInitDlg);
		HANDLE_MSG(hWnd, WM_COMMAND, OnCommand);
	}
	return false;
}

VOID OnClose(HWND hWnd){
	EndDialog(hWnd, 0);
}

BOOL OnInitDlg(HWND hWnd, HWND hWndFocus, LPARAM lParam){
	dwDrives = GetLogicalDrives();
	int index;
	TCHAR lpTemp[100];
	for (int i = 0; i < 26; i++){
		if ((dwDrives>>i)&0x00000001 == 1){
			lpDriveName[0] = _T('A') + i;
			SendDlgItemMessage(hWnd, IDC_COMBO1, CB_ADDSTRING, 0, (LPARAM)lpDriveName);
		}
	}
	index = SendDlgItemMessage(hWnd, IDC_COMBO1, CB_GETCOUNT, 0, 0);
	for (int i = 0; i < index; i++){
		SendDlgItemMessage(hWnd, IDC_COMBO1, CB_GETLBTEXT, i, (LPARAM)lpTemp);
		switch(GetDriveType(lpTemp)){
		case DRIVE_UNKNOWN:
			lstrcat(lpTemp, _T(" (Неизвестный тип накопителя)"));
			break;
		case DRIVE_NO_ROOT_DIR:
			lstrcat(lpTemp, _T(" (Корневой каталог не существует)"));
			break;
		case DRIVE_REMOVABLE:
			lstrcat(lpTemp, _T(" (Съемный диск)"));
			break;
		case DRIVE_FIXED:
			lstrcat(lpTemp, _T(" (Жесткий диск)"));
			break;
		case DRIVE_REMOTE:
			lstrcat(lpTemp, _T(" (Сетевой диск)"));
			break;
		case DRIVE_CDROM:
			lstrcat(lpTemp, _T(" (Компакт-диск)"));
			break;
		case DRIVE_RAMDISK:
			lstrcat(lpTemp, _T(" (Виртуальный диск)"));
			break;
		}
		SendDlgItemMessage(hWnd, IDC_COMBO1, CB_DELETESTRING, i, 0);
		SendDlgItemMessage(hWnd, IDC_COMBO1, CB_INSERTSTRING, i, (LPARAM)lpTemp);
	}
	return true;
}

VOID OnCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify){
	
}