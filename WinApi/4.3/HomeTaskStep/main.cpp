#include <Windows.h>
#include <tchar.h>
#include <ctime>
#include "resource.h"

BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wParam, LPARAM lParam);



INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdLine){
	return DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wParam, LPARAM lParam){
	static time_t currentTime;
	time_t dif;
	int nYear, nMonth, nDay;
	static tm* timeStruct;
	TCHAR temp[50];
	switch(mes){
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		return true;
	case WM_INITDIALOG:
		time(&currentTime);
		timeStruct = localtime(&currentTime);
		return true;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDC_CALC){
			SendMessage(GetDlgItem(hWnd, IDC_DAY), WM_GETTEXT, 20, (LPARAM)temp);
			nDay = _ttoi(temp);
			SendMessage(GetDlgItem(hWnd, IDC_MONTH), WM_GETTEXT, 20, (LPARAM)temp);
			nMonth = _ttoi(temp);
			SendMessage(GetDlgItem(hWnd, IDC_YEAR), WM_GETTEXT, 20, (LPARAM)temp);
			nYear = _ttoi(temp);
			if (nDay > 31){
				MessageBox(hWnd, _T("Дата не может быть больше 31"), 0, 0);
				return false;
			}
			else if (nDay > 29 && !(nYear % 4) && nMonth == 2){
				MessageBox(hWnd, _T("В феврале в высокосный год не может быть больше 29 дней"), 0, 0);
				return false;
			}
			else if (nDay > 28 && nYear % 4 && nMonth == 2){
				MessageBox(hWnd, _T("В феврале в не высокосный год не может быть больше 28 дней"), 0, 0);
				return false;
			}
			else if (nMonth > 12){
				MessageBox(hWnd, _T("Месяц не может быть больше 12"), 0, 0);
				return false;
			}
			else if (nYear <= 1900){
				MessageBox(hWnd, _T("Год не может быть меньше 1900"), 0, 0);
				return false;
			}
			if (!nDay || !nMonth || !nYear){
				MessageBox(hWnd, _T("Все поля должны быть заполнены"), 0, 0);
				return false;
			}
			timeStruct->tm_year = nYear - 1900;
			timeStruct->tm_mon = nMonth - 1;
			timeStruct->tm_mday = nDay;
			dif = mktime(timeStruct) - currentTime;
			wsprintf(temp, _T("%d"), dif / (3600 * 24 * 365));
			dif %= (3600 * 24 * 365);
			SendMessage(GetDlgItem(hWnd,IDC_YEAR2), WM_SETTEXT, 0, (LPARAM)temp);
			wsprintf(temp, _T("%d"), dif / (3600 * 24 * 30));
			dif %= 3600 * 24 * 12;
			SendMessage(GetDlgItem(hWnd,IDC_MONTH2), WM_SETTEXT, 0, (LPARAM)temp);
			wsprintf(temp, _T("%d"), dif / (3600 * 24));
			SendMessage(GetDlgItem(hWnd,IDC_DAY2), WM_SETTEXT, 0, (LPARAM)temp);
		}
		return true;
	}
	return false;
}