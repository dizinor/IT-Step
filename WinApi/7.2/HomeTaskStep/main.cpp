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
VOID OnContextMenu(HWND hwnd, HWND hwndContext, UINT xPos, UINT yPos);

HMENU hContext;
POINT lpPoint;
int nK[] = {3, 3, 3};

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
		HANDLE_MSG(hWnd, WM_COMMAND, OnCommand);
		HANDLE_MSG(hWnd, WM_CONTEXTMENU, OnContextMenu);
	}
	return false;
}

VOID OnClose(HWND hWnd){
	EndDialog(hWnd, 0);
}

BOOL OnInitDlg(HWND hWnd, HWND hWndFocus, LPARAM lParam){
	hContext = GetSubMenu(LoadMenu(GetModuleHandle(0), MAKEINTRESOURCE(IDR_MENU1)), 0);
	return true;
}

void OnCommand(HWND hWnd, int id, HWND hWndCtl, UINT codeNotify){
	if (id >= ID_MENU_EDIT && id <= ID_MENU_STATIC){
		TCHAR lpTemp[30];
		nK[id - ID_MENU_EDIT]--;
		if (id == ID_MENU_EDIT){
			wsprintf(lpTemp, _T("EDIT %d"), nK[id - ID_MENU_EDIT]);
			CreateWindowEx(0, _T("EDIT"), _T("EDIT"), WS_CHILD|WS_VISIBLE, lpPoint.x, lpPoint.y, 70, 20, hWnd, NULL, NULL, NULL);
			ModifyMenu(hContext, ID_MENU_EDIT, MF_BYCOMMAND|MF_STRING, ID_MENU_EDIT, lpTemp);
		}
		else if (id == ID_MENU_BUTTON){
			wsprintf(lpTemp, _T("BUTTON %d"), nK[id - ID_MENU_EDIT]);
			CreateWindowEx(0, _T("BUTTON"), _T("BUTTON"), WS_CHILD|WS_VISIBLE, lpPoint.x, lpPoint.y, 70, 20, hWnd, NULL, NULL, NULL);
			ModifyMenu(hContext, ID_MENU_BUTTON, MF_BYCOMMAND|MF_STRING, ID_MENU_BUTTON, lpTemp);
		}
		else if (id == ID_MENU_STATIC){
			wsprintf(lpTemp, _T("STATIC %d"), nK[id - ID_MENU_EDIT]);
			CreateWindowEx(0, _T("STATIC"), _T("STATIC"), WS_CHILD|WS_VISIBLE, lpPoint.x, lpPoint.y, 70, 20, hWnd, NULL, NULL, NULL);
			ModifyMenu(hContext, ID_MENU_STATIC, MF_BYCOMMAND|MF_STRING, ID_MENU_STATIC, lpTemp);
		}
		if (nK[id - ID_MENU_EDIT] == 0)
			DeleteMenu(hContext,id, MF_BYCOMMAND);
	}
}

VOID OnContextMenu(HWND hWnd, HWND hWndContext, UINT xPos, UINT yPos){
	GetCursorPos(&lpPoint);
	ScreenToClient(hWnd, &lpPoint);
	TrackPopupMenu(hContext, TPM_LEFTALIGN, xPos, yPos, 0, hWnd, 0);
}