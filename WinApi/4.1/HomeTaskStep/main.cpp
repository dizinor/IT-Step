#include <Windows.h>
#include <tchar.h>
#include "resource.h"
#define PLUS 1
#define MINUS 2
#define MULTIPLY 3
#define DIVIDE 4

BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wParam, LPARAM lParam);
int nWhatOperator(TCHAR*);

HWND hOperand1;
HWND hOperand2;
HWND hOperator;
HWND hResult;

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdLine){
	return DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wParam, LPARAM lParam){
	TCHAR buffer[100];
	int nX;
	int nY;
	int nResult;
	switch(mes){
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		return true;
	case WM_INITDIALOG:
		hOperand1 = GetDlgItem(hWnd, IDC_OPERAND1);
		hOperand2 = GetDlgItem(hWnd, IDC_OPERAND2);
		hOperator = GetDlgItem(hWnd, IDC_OPERATOR);
		hResult = GetDlgItem(hWnd, IDC_RESULT);
		return true;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDC_CALC){
			SendMessage(hOperand1, WM_GETTEXT, 100, (LPARAM)buffer);
			nX = _ttoi(buffer);
			if (nX == 0 &&  buffer[0] != '0'){
				MessageBox(hWnd, _T("Введите в качестве первого операнда верное число"), 0, 0);
				return false;
			}
			SendMessage(hOperand2, WM_GETTEXT, 100, (LPARAM)buffer);
			nY = _ttoi(buffer);
			if (nY == 0 && buffer[0] != '0'){
				MessageBox(hWnd, _T("Введите в качестве второго операнда верное число"), 0, 0);
				return false;
			}
			SetWindowText(hOperand2, buffer);
			SendMessage(hOperator, WM_GETTEXT, 100, (LPARAM)buffer);
			switch (nWhatOperator(buffer)){
			case 0:
				MessageBox(hWnd, _T("Введите в качестве оператора '+', '-', '*' или '/'"), 0, 0);
				return false;
			case PLUS:
				nResult = nX + nY;
				break;
			case MINUS:
				nResult = nX - nY;
				break;
			case MULTIPLY:
				nResult = nX * nY;
				break;
			case DIVIDE:
				nResult = nX / nY;
				break;
			}
			wsprintf(buffer, _T("= %d"), nResult);
			SetWindowText(hResult, buffer);
		}
		return true;
	}
	return false;
}

int nWhatOperator(TCHAR *temp){
	if (temp[1] != '\0')
		return 0;
	else if (temp[0] == '+')
		return PLUS;
	else if (temp[0] == '-')
		return MINUS;
	else if (temp[0] == '*')
		return MULTIPLY;
	else if (temp[0] == '/')
		return DIVIDE;
	return 0;
}