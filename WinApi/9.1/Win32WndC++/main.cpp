#include <Windows.h>
#include <tchar.h>
#include <WindowsX.h>
#include <TlHelp32.h>
#include "resource.h"

BOOL CALLBACK DlgProc(HWND hWnd, UINT nMes, WPARAM wParam, LPARAM lParam);

HWND hDlg;

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR szCmdLine, int nCmdShow){
	return DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
}

void OnClose(HWND hWnd);
BOOL OnInitDialog(HWND hWnd, HWND hWndFocus, LPARAM lParam);
void OnCommand(HWND hWnd, int id, HWND hWndCtrl, UINT CodeNotify);

bool Moving(bool bToRight, int nIndex = -1);
bool MoveAll(bool bToRight);
void Fill();

BOOL CALLBACK DlgProc(HWND hWnd, UINT nMes, WPARAM wParam, LPARAM lParam){
	switch (nMes){
		HANDLE_MSG(hWnd, WM_CLOSE, OnClose);
		HANDLE_MSG(hWnd, WM_INITDIALOG, OnInitDialog);
		HANDLE_MSG(hWnd, WM_COMMAND, OnCommand);
	}
	return false;
}

void OnClose(HWND hWnd){
	EndDialog(hWnd, 0);
}

BOOL OnInitDialog(HWND hWnd, HWND hWndFocus, LPARAM lParam){
	hDlg = hWnd;
	Fill();
	return true;
}

void OnCommand(HWND hWnd, int id, HWND hWndCtrl, UINT CodeNotify){
	switch (id){
	case IDC_ADDRIGHT:
		Moving(true);
		break;
	case IDC_ADDLEFT:
		Moving(false);
		break;
	case IDC_ADDALLRIGHT:
		MoveAll(true);
		break;
	case IDC_ADDALLLEFT:
		MoveAll(false);
		break;
	case IDC_CLOSE:
		int *nSize;
		int *nTemp;
		HANDLE *hTemp;
		nSize = new int;
		nTemp = new int;
		hTemp = new HANDLE;

		*nSize = SendDlgItemMessage(hWnd, IDC_LIST2, LB_GETCOUNT, 0, 0);
		for (int i = 0; i < *nSize;){
			*nTemp = SendDlgItemMessage(hWnd, IDC_LIST2, LB_GETITEMDATA, (WPARAM)i, 0);
			*hTemp = OpenProcess(PROCESS_TERMINATE, 0, *nTemp);
			TerminateProcess(*hTemp, 0);
			SendDlgItemMessage(hWnd, IDC_LIST2, LB_DELETESTRING, (WPARAM)i, 0);
			*nSize = SendDlgItemMessage(hWnd, IDC_LIST2, LB_GETCOUNT, 0, 0);
		}
		delete nSize;
		delete nTemp;
		delete hTemp;
		break;
	case IDC_RUN:
		TCHAR *szDir;
		STARTUPINFO sui;
		PROCESS_INFORMATION pi;
		BOOL bOk;
		memset(&sui, 0, sizeof(STARTUPINFO));
		nSize = new int;
		*nSize = SendDlgItemMessage(hWnd, IDC_EDIT1, EM_LINELENGTH, 1, 0) + 1;
		szDir = new TCHAR[*nSize];
		SendDlgItemMessage(hWnd, IDC_EDIT1, WM_GETTEXT, *nSize, (LPARAM)szDir);
		bOk = CreateProcess(szDir, NULL, NULL, NULL, FALSE, 0, NULL, NULL, &sui, &pi);
		if (!bOk)
		{
			MessageBox(hWnd, _T("Не удалось запустить процесс."), 0, 0);
			delete [] szDir;
			delete nSize;
			break;
		}
		WaitForSingleObject(pi.hProcess, INFINITE);
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
		delete [] szDir;
		delete nSize;
		break;
	case IDC_REFRESH:
		SendDlgItemMessage(hWnd, IDC_LIST1, LB_RESETCONTENT, 0, 0);
		SendDlgItemMessage(hWnd, IDC_LIST2, LB_RESETCONTENT, 0, 0);
		Fill();
		break;
	}
}

bool Moving(bool bToRight, int nIndex){
	TCHAR *szTemp = new TCHAR[255];
	int *nTemp = new int;
	nIndex = (nIndex == -1)?SendDlgItemMessage(hDlg, (bToRight)?IDC_LIST1:IDC_LIST2, LB_GETCURSEL, 0, 0):nIndex;
	*nTemp = SendDlgItemMessage(hDlg, (bToRight)?IDC_LIST1:IDC_LIST2, LB_GETITEMDATA, (WPARAM) nIndex, 0);
	if (bToRight == true && OpenProcess(PROCESS_TERMINATE, false, *nTemp) == NULL){
		delete [] szTemp;
		delete nTemp;
		return false;
	}
	SendDlgItemMessage(hDlg, (bToRight)?IDC_LIST1:IDC_LIST2, LB_GETTEXT,(WPARAM)nIndex, (LPARAM)szTemp);
	SendDlgItemMessage(hDlg, (bToRight)?IDC_LIST1:IDC_LIST2, LB_DELETESTRING,(WPARAM)nIndex, 0);
	SendDlgItemMessage(hDlg, (!bToRight)?IDC_LIST1:IDC_LIST2, LB_ADDSTRING, 0, (LPARAM)szTemp);
	nIndex =  SendDlgItemMessage(hDlg, (!bToRight)?IDC_LIST1:IDC_LIST2, LB_FINDSTRING, 0, (LPARAM)szTemp);
	SendDlgItemMessage(hDlg, (!bToRight)?IDC_LIST1:IDC_LIST2, LB_SETITEMDATA, (WPARAM)nIndex, (LPARAM)*nTemp);
	delete [] szTemp;
	delete nTemp;
	return true;
}

bool MoveAll(bool bToRight){
	int *nSize = new int;
	*nSize = SendDlgItemMessage(hDlg, (bToRight)?IDC_LIST1:IDC_LIST2, LB_GETCOUNT, 0, 0);
	for (int i = 0; i < *nSize;){
		if (Moving(bToRight, i) == true)
			*nSize = SendDlgItemMessage(hDlg, (bToRight)?IDC_LIST1:IDC_LIST2, LB_GETCOUNT, 0, 0);
		else
			i++;
	}
	delete nSize;
	return true;
}

void Fill(){
	HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	TCHAR *szTemp = new TCHAR[255];
	int *nIndex = new int;
	PROCESSENTRY32 pe32;
	memset(&pe32, 0, sizeof(PROCESSENTRY32));
	pe32.dwSize = sizeof(PROCESSENTRY32);

	if (Process32First(hSnapShot, &pe32)){
		_stprintf(szTemp, _T("%s"), pe32.szExeFile);
		SendDlgItemMessage(hDlg, IDC_LIST1, LB_ADDSTRING, 0, (LPARAM)szTemp);
		*nIndex = SendDlgItemMessage(hDlg, IDC_LIST1, LB_FINDSTRING, 0, (LPARAM)szTemp);
		SendDlgItemMessage(hDlg, IDC_LIST1, LB_SETITEMDATA, *nIndex, (LPARAM)pe32.th32ProcessID);
	}
	while(Process32Next(hSnapShot, &pe32)){
		_stprintf(szTemp, _T("%s"), pe32.szExeFile);
		SendDlgItemMessage(hDlg, IDC_LIST1, LB_ADDSTRING, 0, LPARAM(pe32.szExeFile));
		*nIndex = SendDlgItemMessage(hDlg, IDC_LIST1, LB_FINDSTRING, 0, (LPARAM)szTemp);
		SendDlgItemMessage(hDlg, IDC_LIST1, LB_SETITEMDATA, *nIndex, (LPARAM)pe32.th32ProcessID);
	}
	delete []szTemp;
	delete nIndex;
}