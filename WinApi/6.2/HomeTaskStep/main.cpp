#include <Windows.h>
#include <WindowsX.h>
#include <tchar.h>
#include <CommCtrl.h>
#include <ctime>
#include <vector>
#include <algorithm>
#include "resource.h"
using namespace std;

#pragma comment(lib, "comctl32")

#define AMMOUNT 16

BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wParam, LPARAM lParam);
VOID OnClose(HWND);
BOOL OnInitDlg(HWND, HWND, LPARAM);
VOID OnCommand(HWND, int, HWND, UINT);
VOID OnTimer(HWND, UINT);

vector<int> nNumbers;
int nTime;

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdLine){
	INITCOMMONCONTROLSEX icc = {sizeof(INITCOMMONCONTROLSEX)};
	icc.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&icc);
	return DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wParam, LPARAM lParam){
	srand(time(0));
	switch(mes){
		HANDLE_MSG(hWnd, WM_CLOSE, OnClose);
		HANDLE_MSG(hWnd, WM_INITDIALOG, OnInitDlg);
		HANDLE_MSG(hWnd, WM_COMMAND, OnCommand);
		HANDLE_MSG(hWnd, WM_TIMER, OnTimer);
	}
	return false;
}

VOID OnClose(HWND hWnd){
	EndDialog(hWnd, 0);
}

BOOL OnInitDlg(HWND hWnd, HWND hWndFocus, LPARAM lParam){
	for (int i = IDC_BUTTON1; i <= IDC_BUTTON16; i++){
		EnableWindow(GetDlgItem(hWnd, i), 0);
	}
	SendDlgItemMessage(hWnd, IDC_SPIN1, UDM_SETRANGE32, 1, 120);
	SendDlgItemMessage(hWnd, IDC_SPIN1, UDM_SETPOS32, 0, 30);
	return true;
}

VOID OnCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify){
	TCHAR lpTemp[5];
	int nTemp;
	if (id >= IDC_BUTTON1 && id <= IDC_BUTTON16){
		GetWindowText(GetDlgItem(hWnd, id), lpTemp, 5);
		nTemp = _ttoi(lpTemp);
		if (nTemp == nNumbers.front()){
			EnableWindow(GetDlgItem(hWnd, id), 0);
			nNumbers.erase(nNumbers.begin());
			SendDlgItemMessage(hWnd, IDC_LIST1, LB_ADDSTRING, 0, (LPARAM)lpTemp);
		}
		if (nNumbers.empty()){
			MessageBox(hWnd, _T("Поздравляем!"), _T("Вы выиграли!"), 0);
			KillTimer(hWnd, 1);
			KillTimer(hWnd, 2);
		}
	}
	if (id == IDC_START){
		TCHAR lpTemp[5];
		nNumbers.clear();
		for (int i = 0; i < AMMOUNT; i++){
			nNumbers.push_back(rand()%100+1);
		}
		for (int i = IDC_BUTTON1; i <= IDC_BUTTON16; i++){
			wsprintf(lpTemp, _T("%d"), nNumbers[i - IDC_BUTTON1]);
			SetWindowText(GetDlgItem(hWnd, i), lpTemp);
			EnableWindow(GetDlgItem(hWnd, i), 1);
		}
		sort(nNumbers.begin(), nNumbers.begin() + AMMOUNT);
		nTime = SendDlgItemMessage(hWnd, IDC_SPIN1, UDM_GETPOS32, 0, NULL);
		SendDlgItemMessage(hWnd, IDC_PROGRESS1, PBM_SETRANGE, 0, MAKELPARAM(0, nTime));
		SendDlgItemMessage(hWnd, IDC_PROGRESS1, PBM_SETSTEP, 1, 0);
		SetTimer(hWnd, 1, nTime * 1000, NULL);
		SetTimer(hWnd, 2, 1000, NULL);
	}
}

VOID OnTimer (HWND hWnd, UINT id){
	if (id == 1){
		MessageBox(hWnd, _T("Время вышло!"), _T("Вы проиграли!"), 0);
		KillTimer(hWnd, 1);
		KillTimer(hWnd, 2);
		for (int i = IDC_BUTTON1; i <= IDC_BUTTON16; i++){
			EnableWindow(GetDlgItem(hWnd, i), 1);
		}
	}
	if (id == 2){
		SendDlgItemMessage(hWnd, IDC_PROGRESS1, PBM_STEPIT, 0, 0);
	}
}