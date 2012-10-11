#include "main.h"

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR szCmdLine, int nCmdShow){
	return DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT nMes, WPARAM wParam, LPARAM lParam){
	switch (nMes){
		HANDLE_MSG(hWnd, WM_CLOSE, OnClose);
		HANDLE_MSG(hWnd, WM_COMMAND, OnCommand);
	}
	return false;
}

void OnClose(HWND hWnd){
	EndDialog(hWnd, 0);
}

void OnCommand(HWND hWnd, int id, HWND hWndCtrl, UINT CodeNotify){
	switch (id){
	case IDC_RUN:
		TCHAR* szTemp;
		STARTUPINFO sui;
		memset(&sui, 0, sizeof(STARTUPINFO));
		PROCESS_INFORMATION pi;
		
		szTemp = new TCHAR[MAX_PATH];
		GetCurrentDirectory(MAX_PATH, szTemp);
		lstrcat(szTemp, _T("\\..\\Debug\\DiscoDancer.exe"));

		CreateProcess(szTemp, NULL, NULL, NULL, FALSE, NULL, NULL, NULL, &sui, &pi);
		WaitForSingleObject(pi.hProcess, INFINITE);
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
		delete [] szTemp;
		break;
	case IDC_STOP:

		break;
	}
}