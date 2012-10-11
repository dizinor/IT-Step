#include "main.h"

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR szCmdLine, int nCmdShow){
	INITCOMMONCONTROLSEX ic;
	ic.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&ic);
	return DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), 0, DlgProc);
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT nMessage, WPARAM wParam, LPARAM lParam){
	switch (nMessage){
	case WM_INITDIALOG:
		HWND hTemp;
		for (int i = IDC_PROGRESS1; i <= IDC_PROGRESS4; i++){
			hTemp = GetDlgItem(hWnd, i);
			SendMessage(hTemp, PBM_SETRANGE, 0, MAKELPARAM(0,1));
			SendMessage(hTemp, PBM_SETPOS, 1, 0);
			CreateThread(NULL, NULL, ThreadFunc, LPVOID(hTemp), NULL, NULL);
			
		}
		return true;
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		return true;
	}
	return false;
}

DWORD WINAPI ThreadFunc(LPVOID lpParam){
	srand(time(0) + GetCurrentThreadId());
	while(true){
		SendMessage((HWND)lpParam, PBM_SETBARCOLOR, 0, LPARAM(RGB(rand()%256,rand()%256,rand()%256)));
		Sleep(100);
	}
	return 0;
}