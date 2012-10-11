#include <Windows.h>
#include <tchar.h>
#include <time.h>
#include "resource.h"

class GAME{
	HWND hWnd;
	int nFilled[9];
	HBITMAP hCross;
	HBITMAP hCircle;

public:
	GAME(HWND hWnd){
		this->hWnd = hWnd;
		hCross = LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(IDB_CROSS));
		hCircle = LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(IDB_CIRCLE));
		for (int i = 0; i < 9; i++)
			nFilled[i] = -1;
		for (int i = IDC_GRID00; i <= IDC_GRID22; i++){
			EnableWindow(GetDlgItem(hWnd, i), 0);
		}
	}

	void PlayerTurn(WPARAM wParam){
		if (nFilled[LOWORD(wParam) - IDC_GRID00] == -1){
			SendMessage(GetDlgItem(hWnd, LOWORD(wParam)), BM_SETIMAGE, WPARAM(IMAGE_BITMAP), LPARAM(hCross));
			nFilled[LOWORD(wParam) - IDC_GRID00]  = 1;
		}
		if (bWhoWin(1) == TRUE){
			MessageBox(hWnd, _T("Вы выиграли!"), _T("Поздравляем!"), 0);
			for (int i = IDC_GRID00; i <= IDC_GRID22; i++){
				EnableWindow(GetDlgItem(hWnd, i), 0);
			}
		}
		else
			CpuTurn();
	}

	void CpuTurn(){
		short* temp = new short;
		do{
			*temp = rand()%9;
		}while (nFilled[*temp] != -1);
		SendMessage(GetDlgItem(hWnd, LOWORD(IDC_GRID00 + *temp)), BM_SETIMAGE, WPARAM(IMAGE_BITMAP), LPARAM(hCircle));
		nFilled[*temp] = 0;
		delete temp;
		if (bWhoWin(0) == TRUE){
			MessageBox(hWnd, _T("Вы проиграли!"), _T("Беда-беда!"), 0);
			for (int i = IDC_GRID00; i <= IDC_GRID22; i++){
				EnableWindow(GetDlgItem(hWnd, i), 0);
			}
		}
	}

	BOOL bWhoWin(int i){
		if(nFilled[0] == i && nFilled[1] == i && nFilled[2] == i)
			return TRUE;
		if(nFilled[3] == i && nFilled[4] == i && nFilled[5] == i)
			return TRUE;
		if(nFilled[6] == i && nFilled[7] == i && nFilled[8] == i)
			return TRUE;
		if(nFilled[0] == i && nFilled[3] == i && nFilled[6] == i)
			return TRUE;
		if(nFilled[1] == i && nFilled[4] == i && nFilled[7] == i)
			return TRUE;
		if(nFilled[2] == i && nFilled[5] == i && nFilled[8] == i)
			return TRUE;
		if(nFilled[0] == i && nFilled[4] == i && nFilled[8] == i)
			return TRUE;
		if(nFilled[2] == i && nFilled[4] == i && nFilled[6] == i)
			return TRUE;
		return FALSE;
	}

	void NewGame(){
		for (int i = 0; i < 9; i++)
			nFilled[i] = -1;
		for (int i = IDC_GRID00; i <= IDC_GRID22; i++){
			EnableWindow(GetDlgItem(hWnd, i), 1);
			SendMessage(GetDlgItem(hWnd, LOWORD(i)), BM_SETIMAGE, WPARAM(IMAGE_BITMAP), 0);
		}
		if (IsDlgButtonChecked(hWnd, IDC_CHECK1) == BST_UNCHECKED)
			CpuTurn();
	}
};

BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdLine){
	return DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wParam, LPARAM lParam){
	static GAME game(hWnd);
	srand(time(0));
	switch(mes){
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		return true;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDC_NEWGAME)
			game.NewGame();
		else if (LOWORD(wParam) >= IDC_GRID00 && LOWORD(wParam) <= IDC_GRID22)
			game.PlayerTurn(wParam);
		return true;
	}
	return false;
}