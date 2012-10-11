#include <Windows.h>
#include <tchar.h>
#include <strsafe.h>
#include <fstream>
#include <cstringt.h>
#include "resource.h"
using namespace std;

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK WinProc(HWND, UINT, WPARAM, LPARAM);

TCHAR lpClassName[] = _T("Открытие файлов");
HWND hWnd;
HWND hEdit;

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow){ 
	WNDCLASS wcl;
	MSG msg;
	RECT rect;
	setlocale(LC_ALL, "");
	
	memset(&wcl, 0, sizeof(WNDCLASS));
	wcl.hInstance = hInst;
	wcl.lpfnWndProc = WinProc;
	wcl.lpszClassName = lpClassName;
	wcl.style = CS_HREDRAW|CS_VREDRAW;
	wcl.hCursor = LoadCursor(0, IDC_ARROW);
	wcl.hbrBackground = (HBRUSH)GetStockObject(DKGRAY_BRUSH);


	RegisterClass(&wcl);
	
	hWnd = CreateWindow(lpClassName, 0, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 0, LoadMenu(hInst, MAKEINTRESOURCE(IDR_MENU1)), hInst, 0);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	GetClientRect(hWnd, &rect);

	hEdit = CreateWindow(_T("EDIT"), 0, WS_CHILD|WS_VISIBLE|ES_MULTILINE|WS_VSCROLL|ES_NOHIDESEL, 0, 0, rect.right, rect.bottom, hWnd, (HMENU)ID_EDIT, GetModuleHandle(0), 0);

	while (GetMessage(&msg, 0, 0, 0)){
		DispatchMessage(&msg);
		TranslateMessage(&msg);
	}
	return msg.wParam;
}
	
LRESULT CALLBACK WinProc(HWND hWnd, UINT id, WPARAM wParam, LPARAM lParam){
	static TCHAR szFile[MAX_PATH];
	static OPENFILENAME ofn;
	int nSize;
	TCHAR * szBuffer;
	std::basic_fstream<TCHAR, char_traits<TCHAR>> fInput;
	switch (id){
	case WM_CREATE:
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.lpstrFile = szFile;
		ofn.hwndOwner = hWnd;
		ofn.nMaxFile = sizeof(szFile);
		ofn.lpstrFilter = _T("Текстовые документы\0*.txt\0\0");
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam)){
		case ID_OPEN:
			_tcscpy_s(szFile, _countof(szFile), _T(""));
			GetOpenFileName(&ofn);
			_tcscpy_s(szFile, _countof(szFile), ofn.lpstrFile);
			fInput.open(szFile, ios::in|ios::binary);
			fInput.seekg (0, ios::end);
			nSize = fInput.tellg();
			fInput.seekg (0, ios::beg);
			szBuffer = new TCHAR[nSize+1];
			fInput.read(szBuffer, nSize);
			szBuffer[nSize] = '\0';
			SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)szBuffer);
			delete[] szBuffer;
			fInput.close();
			break;
		case ID_FINDANDREPLACE:
			CreateDialog(GetModuleHandle(0), MAKEINTRESOURCE(IDD_DIALOG1), 0, DlgProc);
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, id, wParam, lParam);
}

BOOL CALLBACK DlgProc(HWND hDlg, UINT id, WPARAM wParam, LPARAM lParam){
	std::basic_string<TCHAR> szBuffer1;
	std::basic_string<TCHAR> szBuffer2;
	std::basic_string<TCHAR> szBuffer3;
	int nSize1, nSize2, nSize3;
	static size_t nFindS = 0;
	static size_t nFindR = 0;
	TCHAR * szTemp;
	switch (id){
	case WM_CLOSE:
		DestroyWindow(hDlg);
		return true;
	case WM_COMMAND:
		switch (LOWORD(wParam)){
		case ID_FIND:
			nSize1 = GetWindowTextLength(hEdit);
			nSize2 = GetWindowTextLength(GetDlgItem(hDlg, IDC_EDIT1)) + 1;
			szTemp = new TCHAR[nSize1+1];
			GetWindowText(hEdit, szTemp, nSize1);
			szBuffer1 = szTemp;
			delete [] szTemp;
			szTemp = new TCHAR[nSize2];
			GetWindowText(GetDlgItem(hDlg, IDC_EDIT1), szTemp, nSize2);
			szBuffer2 = szTemp;
			delete [] szTemp;
			if (szBuffer2.empty())
				break;
			if (nFindS == string::npos)
				nFindS = 0;
			nFindS = szBuffer1.find(szBuffer2.c_str(), nFindS + 1);
			if (nFindS != string::npos){
				SendMessage(hEdit, EM_SETSEL, nFindS, (nFindS + nSize2 - 1));
				SendMessage(hEdit, EM_SCROLLCARET, 0, 0);
			}
			break;
		case ID_REPLACE:
			nSize1 = GetWindowTextLength(hEdit);
			nSize2 = GetWindowTextLength(GetDlgItem(hDlg, IDC_EDIT1)) + 1;
			nSize3 = GetWindowTextLength(GetDlgItem(hDlg, IDC_EDIT2)) + 1;
			szTemp = new TCHAR[nSize1+1];
			GetWindowText(hEdit, szTemp, nSize1);
			szBuffer1 = szTemp;
			delete [] szTemp;
			szTemp = new TCHAR[nSize2+1];
			GetWindowText(GetDlgItem(hDlg, IDC_EDIT1), szTemp, nSize2);
			szBuffer2 = szTemp;
			if (szTemp != szBuffer2.c_str()){
				nFindR = 0;
				szBuffer2 = szTemp;
			}
			delete [] szTemp;
			if (szBuffer2.empty())
				break;
			szTemp = new TCHAR[nSize3];
			GetWindowText(GetDlgItem(hDlg, IDC_EDIT2), szTemp, nSize3);
			szBuffer3 = szTemp;
			if (szTemp != szBuffer3.c_str()){
				nFindR = 0;
				szBuffer3 = szTemp;
			}
			delete [] szTemp;
			if (nFindR == string::npos)
				nFindR = 0;
			nFindR = szBuffer1.find(szBuffer2.c_str(), nFindR + 1);
			if (nFindR != string::npos){
				SendMessage(hEdit, EM_SETSEL, nFindR, (nFindR + nSize2 - 1));
				SendMessage(hEdit, EM_SCROLLCARET, 0, 0);
				SendMessage(hEdit, EM_REPLACESEL, true, (LPARAM)szBuffer3.c_str());
			}
			break;
		case IDC_EDIT1:
			if (HIWORD(wParam) == EN_CHANGE){
				nFindS = 0;
			}
			break;
		case IDC_EDIT2:
			if (HIWORD(wParam) == EN_CHANGE){
				nFindR = 0;
			}
			break;
		}
		return true;
	}
	return false;
}