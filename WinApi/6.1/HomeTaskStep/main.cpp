#include <Windows.h>
#include <WindowsX.h>
#include <tchar.h>
#include <ctime>
#include <CommCtrl.h>
#include "resource.h"

#pragma comment(lib, "comctl32")

BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wParam, LPARAM lParam);
void Click(HWND hWnd, WPARAM wParam, int nCurPos[][4]);
void Switch(HWND hWnd, int nCurPos[][4], int i1, int j1, int i0, int j0);

TCHAR lpTime[100];
TCHAR lpComplete[100];
HWND hStatus;

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdLine){
	INITCOMMONCONTROLSEX icc = {sizeof(INITCOMMONCONTROLSEX)};
	icc.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&icc);
	return DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wParam, LPARAM lParam){
	srand(time(0));
	int parts[2] = {200, 350};
	int nP = 0;
	static time_t start,end;
	static int nPosToWin[4][4] = {
		{ 1,   2,  3,  4},
		{ 5,   6,  7,  8},
		{ 9,  10, 11, 12},
	    {13,  14, 15,  0}}; 
	static int nCurPos[4][4] = {0};
	TCHAR * lpTemp1;
	TCHAR * lpTemp2;
	switch(mes){
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		return true;
	case WM_INITDIALOG:
		lpTemp1 = new TCHAR[10];
		for (int i = 0, k = IDC_BUTTON1; i < 4; i++)
			for (int j = 0; j < 4; j++, k++){
				GetWindowText(GetDlgItem(hWnd, k), lpTemp1, 10);
				nCurPos[i][j] = _ttoi(lpTemp1);
				EnableWindow(GetDlgItem(hWnd, k), 0);
			}
		delete lpTemp1;
		hStatus = CreateStatusWindow(CCS_BOTTOM|WS_VISIBLE|WS_CHILD, lpTime, hWnd, WM_USER);
		SendMessage(hStatus, SB_SETPARTS, 2, LPARAM(parts));
		return true;
	case WM_TIMER:
		time(&end);
		_stprintf(lpTime, _T("С начала прошло %.f секунд"), difftime(end,start));
		SendMessage(hStatus, SB_SETTEXT, 0, (LPARAM)lpTime);
		return true;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDC_NEWGAME){
			lpTemp1 = new TCHAR[10];
			lpTemp2 = new TCHAR[10];
			for (int i = IDC_BUTTON1; i <= IDC_BUTTON16; i++){
				int k = rand() % (IDC_BUTTON16 - IDC_BUTTON1) + IDC_BUTTON1 + 1;
				GetWindowText(GetDlgItem(hWnd, k), lpTemp1, 10);
				GetWindowText(GetDlgItem(hWnd, i), lpTemp2, 10);
				SetWindowText(GetDlgItem(hWnd, k), lpTemp2);
				SetWindowText(GetDlgItem(hWnd, i), lpTemp1);
				EnableWindow(GetDlgItem(hWnd, i), 1);
			}
			for (int i = 0, k = IDC_BUTTON1; i < 4; i++)
				for (int j = 0; j < 4; j++, k++){
					GetWindowText(GetDlgItem(hWnd, k), lpTemp1, 10);
					nCurPos[i][j] = _ttoi(lpTemp1);
				}
			delete [] lpTemp1;
			delete [] lpTemp2;
			time(&start);
			SetTimer(hWnd, 1, 1000, NULL);
		}
		else if (LOWORD(wParam) >= IDC_BUTTON1 && LOWORD(wParam) <= IDC_BUTTON16)
			Click(hWnd, wParam, nCurPos);
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				if (nCurPos[i][j] != nPosToWin[i][j])
					nP++;
		nP = ((16 - nP) * 100) / 16;
		wsprintf(lpComplete, _T("Выполнено на %d%%"), nP);
		SendMessage(hStatus, SB_SETTEXT, 1, LPARAM(lpComplete));
		if (LOWORD(wParam) == IDC_BUTTON16){
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++)
					if (nCurPos[i][j] != nPosToWin[i][j])
						return true;
			MessageBox(hWnd, _T("Вы выиграли!"), _T("Поздравляем!"),0);
			KillTimer(hWnd, 1);
			for (int i = IDC_BUTTON1; i <= IDC_BUTTON16; i++)
				EnableWindow(GetDlgItem(hWnd, i), 0);
		}
		return true;
	}
	return false;
}

void Click(HWND hWnd, WPARAM wParam, int nCurPos[][4]){
	int * ni= new int;
	int * nj = new int;
	if (LOWORD(wParam) >= IDC_BUTTON1 && LOWORD(wParam) <= IDC_BUTTON16){
		*ni = (LOWORD(wParam) - IDC_BUTTON1) / 4;
		*nj = (LOWORD(wParam) - IDC_BUTTON1) % 4;
		if (*ni > 0 && nCurPos[*ni - 1][*nj] == 0){
			Switch(hWnd, nCurPos, *ni, *nj, (*ni -1), *nj);
		}
		else if (*ni < 3 && nCurPos[*ni + 1][*nj] == 0){
			Switch(hWnd, nCurPos, *ni, *nj, (*ni + 1), *nj);
		}
		else if (*nj > 0 && nCurPos[*ni][*nj - 1] == 0){
			Switch(hWnd, nCurPos, *ni, *nj, *ni, (*nj - 1));
		}
		else if (*nj < 3 && nCurPos[*ni][*nj + 1] == 0){
			Switch(hWnd, nCurPos, *ni, *nj, *ni, (*nj + 1));
		}
	}
	delete ni;
	delete nj;
}

void Switch(HWND hWnd, int nCurPos[][4], int i1, int j1, int i0, int j0){
	TCHAR * lpTemp = new TCHAR[10];
	GetWindowText(GetDlgItem(hWnd, IDC_BUTTON1 + j1 + (4 * i1)), lpTemp, 10);
	SetWindowText(GetDlgItem(hWnd, IDC_BUTTON1 + j1 + (4 * i1)), _T(""));
	SetWindowText(GetDlgItem(hWnd, IDC_BUTTON1 + j0 + (4 * i0)), lpTemp);
	nCurPos[i0][j0] = nCurPos[i1][j1];
	nCurPos[i1][j1] = 0;
	delete []lpTemp;
}