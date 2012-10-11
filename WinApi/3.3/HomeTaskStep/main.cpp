#include <Windows.h>
#include <tchar.h>
#include <time.h>
#include "resource.h"

BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdLine){
	return DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wParam, LPARAM lParam){
	srand(time(0));
	static RECT rect;
	static RECT rWindow;
	static RECT rWindowPos;
	static HWND hStatic;
	static POINT ptr;
	int nX;
	int nY;
	switch(mes){
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		return true;
	case WM_INITDIALOG:
		hStatic = GetDlgItem(hWnd, IDC_STATIC1);
		GetWindowRect(hStatic, &rect);
		GetWindowRect(hWnd, &rWindowPos);
		GetClientRect(hWnd, &rWindow);
		return true;
	case WM_MOUSEMOVE:
		GetCursorPos(&ptr);
		if (ptr.x > rect.left && ptr.x < rect.right && ptr.y > rect.top && ptr.y < rect.bottom){
			do{
				nX = rand()%rWindow.right;
			} while (ptr.x  > nX + rWindowPos.left && ptr.x < nX + rWindowPos.left + rect.right - rect.left);
			do{
				nY = rand()%rWindow.bottom;
			} while (ptr.y > nY + rWindowPos.top && ptr.y < nY + rWindowPos.top + rect.bottom - rect.top);
			SetWindowPos(hStatic, 0, nX, nY, 0, 0, SWP_NOSIZE);
			GetWindowRect(hStatic, &rect);
		}
		return true;
	}
	return false;
}