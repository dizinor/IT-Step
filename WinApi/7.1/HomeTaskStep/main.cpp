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

bool IsEnglish;
HMENU hMenu, hMenuPopUp, hMenuPopUpSaveAs;

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
	}
	return false;
}

VOID OnClose(HWND hWnd){
	EndDialog(hWnd, 0);
}

BOOL OnInitDlg(HWND hWnd, HWND hWndFocus, LPARAM lParam){
	IsEnglish = true;
	hMenu = CreateMenu();
	hMenuPopUp = CreatePopupMenu();
	hMenuPopUpSaveAs = CreatePopupMenu();

	AppendMenu(hMenu, MF_POPUP, (UINT_PTR) hMenuPopUp, _T(""));

	AppendMenu(hMenuPopUp, MF_STRING, WM_USER, _T(""));
	AppendMenu(hMenuPopUp, MF_STRING, WM_USER+1, _T(""));
	AppendMenu(hMenuPopUp, MF_STRING, WM_USER+2, _T(""));
	AppendMenu(hMenuPopUp, MF_POPUP, (UINT_PTR)hMenuPopUpSaveAs, _T(""));

	AppendMenu(hMenuPopUpSaveAs, MF_STRING, WM_USER+3, _T(""));
	AppendMenu(hMenuPopUpSaveAs, MF_STRING, WM_USER+4, _T(""));
	return true;
}

void OnCommand(HWND hWnd, int id, HWND hWndCtl, UINT codeNotify){
	if (id == IDC_STAT)
		SetMenu(hWnd, LoadMenu(GetModuleHandle(0), (IsEnglish)?MAKEINTRESOURCE(IDR_MENUR):MAKEINTRESOURCE(IDR_MENUE)));
	else if (id == IDC_DYNAMIC){
		ModifyMenu(hMenu, 0, MF_BYPOSITION|MF_POPUP, (UINT_PTR)hMenuPopUp, (IsEnglish)?_T("Файл"):_T("File"));

		ModifyMenu(hMenuPopUp, 0, MF_BYPOSITION|MF_STRING, WM_USER, (IsEnglish)?_T("Новый"):_T("New"));
		ModifyMenu(hMenuPopUp, 1, MF_BYPOSITION|MF_STRING, WM_USER+1, (IsEnglish)?_T("Открыть"):_T("Open"));
		ModifyMenu(hMenuPopUp, 2, MF_BYPOSITION|MF_STRING, WM_USER+2, (IsEnglish)?_T("Сохранить"):_T("Save"));
		ModifyMenu(hMenuPopUp, 3, MF_BYPOSITION|MF_POPUP, (UINT_PTR) hMenuPopUpSaveAs, (IsEnglish)?_T("Сохранить как..."):_T("Save as..."));

		ModifyMenu(hMenuPopUpSaveAs, 0, MF_BYPOSITION|MF_STRING, WM_USER+3, (IsEnglish)?_T("Текстовый файл"):_T("Text file"));
		ModifyMenu(hMenuPopUpSaveAs, 1, MF_BYPOSITION|MF_STRING, WM_USER+3, (IsEnglish)?_T("Бинарный файл"):_T("Binary file"));
		SetMenu(hWnd, hMenu);
	}
	SetWindowText(GetDlgItem(hWnd, IDC_STAT), (IsEnglish)?_T("To english"):_T("На русский"));
	SetWindowText(GetDlgItem(hWnd, IDC_DYNAMIC), (IsEnglish)?_T("To english"):_T("На русский"));
	IsEnglish = (IsEnglish)?false:true;
}