#include <Windows.h>
#include <WindowsX.h>
#include <tchar.h>
#include <ctime>
#include <vector>
#include "resource.h"
using namespace std;

BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdLine){
	return DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wParam, LPARAM lParam){
	int nTemp;
	TCHAR lpTemp[20];
	static vector<int> nDigits;
	static int nSum;
	static int nMulti;
	static float nAvrg;
	srand(time(0));
	switch(mes){
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		return true;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDC_BUTTON1){
			nSum = 0;
			nMulti = 1;
			nAvrg = 0;
			if (SendDlgItemMessage(hWnd, IDC_LIST1, LB_GETCOUNT, 0, 0) != 0)
				SendDlgItemMessage(hWnd, IDC_LIST1, LB_RESETCONTENT, 0, 0);
			for (int i = 0; i < 10; i++){
				do{
					nTemp = rand()%20-10;
				} while (nTemp == 0);
				nDigits.push_back(nTemp);
				wsprintf(lpTemp, _T("%d"), nTemp);
				SendDlgItemMessage(hWnd, IDC_LIST1, LB_ADDSTRING, 0, (LPARAM)lpTemp);
			}
			for (int i = 0; i < nDigits.size(); i++){
				nSum += nDigits[i];
				nMulti *= nDigits[i];
				nAvrg +=nDigits[i];
			}
			nAvrg /= nDigits.size();			
		}
		else if (LOWORD(wParam) == IDC_RADIO1){
			_stprintf(lpTemp, _T("%d"), nSum);
			SetWindowText(GetDlgItem(hWnd, IDC_STATIC1), lpTemp);
		}
		else if (LOWORD(wParam) == IDC_RADIO2){
			_stprintf(lpTemp, _T("%d"), nMulti);
			SetWindowText(GetDlgItem(hWnd, IDC_STATIC1), lpTemp);
		}
		else if (LOWORD(wParam) == IDC_RADIO3){
			_stprintf(lpTemp, _T("%4.2f"), nAvrg);
			SetWindowText(GetDlgItem(hWnd, IDC_STATIC1), lpTemp);
		}
		return true;
	}
	return false;
}