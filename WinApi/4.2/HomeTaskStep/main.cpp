#include <Windows.h>
#include <tchar.h>
#include <ctime>
#include "resource.h"

BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wParam, LPARAM lParam);



INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdLine){
	return DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wParam, LPARAM lParam){
	time_t currentTime;
	int nYear, nMonth, nDay;
	static tm* timeStruct;
	TCHAR temp[20];
	TCHAR* lpWeekDay[] = {_T("Воскресенье"), _T("Понедельник"), _T("Вторник"), _T("Среда"), _T("Четверг"), _T("Пятница"), _T("Суббота")};
	switch(mes){
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		return true;
	case WM_INITDIALOG:
		time(&currentTime);
		timeStruct = localtime (&currentTime);
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
			mktime(timeStruct);
			SendMessage(GetDlgItem(hWnd, IDC_WEEK), WM_SETTEXT, 0, (LPARAM)lpWeekDay[timeStruct->tm_wday]);
		}
		return true;
	}
	return false;
}