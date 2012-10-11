#include <Windows.h>
#include <WindowsX.h>
#include <tchar.h>
#include <ctime>
#include <vector>
#include "resource.h"
using namespace std;

BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wParam, LPARAM lParam);
VOID OnClose(HWND);
BOOL OnInitDlg(HWND, HWND, LPARAM);
VOID OnCommand(HWND, int, HWND, UINT);

int rnd;
TCHAR * classes[] = {_T("BUTTON"), _T("EDIT"), _T("LISTBOX"), _T("COMBOBOX"), _T("STATIC")};
vector<HWND>buttons;
vector<HWND>edits;
vector<HWND>lists;
vector<HWND>combos;
vector<HWND>statics;
RECT rect;

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdLine){
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
	for (int i = 0; i < 5; i++)
		SendDlgItemMessage(hWnd, IDC_COMBO1, CB_ADDSTRING, 0, (LPARAM)classes[i]);
	GetClientRect(hWnd, &rect);
	return true;
}

VOID OnCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify){
	int index;
	if (id == IDC_CREATE){
		index = SendDlgItemMessage(hWnd, IDC_COMBO1, CB_GETCURSEL, 0, 0);
		if (index == 0){
			buttons.push_back(CreateWindowEx(0, classes[0], classes[0], WS_CHILD|WS_VISIBLE, rand()%rect.right, rand()%rect.bottom, 50, 15, hWnd, NULL, NULL, NULL));
		}
		else if (index == 1){
			edits.push_back(CreateWindowEx(0, classes[1], classes[1], WS_CHILD|WS_VISIBLE, rand()%rect.right, rand()%rect.bottom, 50, 15, hWnd, NULL, NULL, NULL));
		}
		else if (index == 2){
			lists.push_back(CreateWindowEx(0, classes[2], NULL, WS_CHILD|WS_VISIBLE|LBS_STANDARD, rand()%rect.right, rand()%rect.bottom, 150, 50, hWnd, (HMENU)1100, NULL, NULL));
		}
		else if (index == 3){
			combos.push_back(CreateWindowEx(0, classes[3], classes[3], WS_CHILD|WS_VISIBLE|CBS_DROPDOWN, rand()%rect.right, rand()%rect.bottom, 50, 15, hWnd, NULL, NULL, NULL));
		}
		else if (index == 4){
			statics.push_back(CreateWindowEx(0, classes[4], classes[4], WS_CHILD|WS_VISIBLE, rand()%rect.right, rand()%rect.bottom, 50, 15, hWnd, NULL, NULL, NULL));
		}
	}
	if (id == IDC_DELETE){
		index = SendDlgItemMessage(hWnd, IDC_COMBO1, CB_GETCURSEL, 0, 0);
		if (index == 0){
			if (buttons.size() > 0){
				DestroyWindow(buttons.back());
				buttons.pop_back();
			}
		}
		else if (index == 1){
			if (edits.size() > 0){
				DestroyWindow(edits.back());
				edits.pop_back();
			}
		}
		else if (index == 2){
			if (lists.size() > 0){
				DestroyWindow(lists.back());
				lists.pop_back();
			}
		}
		else if (index == 3){
			if (combos.size() > 0){
				DestroyWindow(combos.back());
				combos.pop_back();
			}
		}
		else if (index == 4){
			if (statics.size() > 0){
				DestroyWindow(statics.back());
				statics.pop_back();
			}
		}
	}
}