#include <Windows.h>
#include <tchar.h>
#include <vector>
#include "resource.h"
using namespace std;

BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wParam, LPARAM lParam);

struct STATICS{
	int nPosX;
	int nPosY;
	int nWidth;
	int nHeight;
	int k;
	HWND hWnd;
};

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdLine){
	return DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wParam, LPARAM lParam){
	static int nX;
	static int nY;
	static int k = 0;
	static vector<STATICS> statics;
	STATICS temp;
	TCHAR str[100];
	switch(mes){
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		return true;
	case WM_LBUTTONDOWN:
		nX = LOWORD(lParam);
		nY = HIWORD(lParam);
		return true;
	case WM_LBUTTONUP:
		if ((LOWORD(lParam) == nX) && (HIWORD(lParam) == nY))
			return true;
		if (LOWORD(lParam) > nX)
			temp.nWidth = LOWORD(lParam) - nX;
		else if (LOWORD(lParam) < nX){
			temp.nWidth = nX - LOWORD(lParam);
			nX = LOWORD(lParam);
		}
		if (HIWORD(lParam) > nY)
			temp.nHeight = HIWORD(lParam) - nY;
		else if (HIWORD(lParam) < nY){
			temp.nHeight = nY - HIWORD(lParam);
			nY = HIWORD(lParam);
		}
		temp.nPosX = nX;
		temp.nPosY = nY;
		if ((temp.nWidth < 10) || (temp.nHeight < 10)){
			MessageBox(hWnd,_T("Сторона не может быть меньше 10."), NULL, NULL);
			temp.nWidth = (temp.nWidth < 10) ? 10 : temp.nWidth;
			temp.nHeight = (temp.nHeight < 10) ? 10 : temp.nHeight;
		}
		temp.hWnd = CreateWindowEx(0, _T("STATIC"),NULL, WS_BORDER|WS_VISIBLE|WS_CHILD, temp.nPosX, temp.nPosY, temp.nWidth, temp.nHeight, hWnd, NULL, 0, 0);
		temp.k = ++k;
		statics.push_back(temp);
		return true;
	case WM_RBUTTONDOWN:
		nX = LOWORD(lParam);
		nY = HIWORD(lParam);
		for (int i = statics.size() - 1; i >= 0; i--){
			if ((nX >= statics[i].nPosX)  && (nX <= statics[i].nWidth + statics[i].nPosX) && (nY >= statics[i].nPosY) && (nY <= statics[i].nHeight + statics[i].nPosY)){
				wsprintf(str, _T("Статик №%d, Ширина:%d, Высота:%d, Х:%d, Y:%d"), statics[i].k, statics[i].nWidth, statics[i].nHeight, statics[i].nPosX, statics[i].nPosY);
				SetWindowText(hWnd,str);
				return true;
			}
		}
		SetWindowText(hWnd,_T("Тут нету статика."));
		return true;
	case WM_LBUTTONDBLCLK:
		nX = LOWORD(lParam);
		nY = HIWORD(lParam);
		for (int i = statics.size() - 1; i >= 0; i--){
			if ((nX >= statics[i].nPosX)  && (nX <= statics[i].nWidth + statics[i].nPosX) && (nY >= statics[i].nPosY) && (nY <= statics[i].nHeight + statics[i].nPosY)){
				DestroyWindow(statics[i].hWnd);
				statics.erase(statics.begin() + i);
				return true;
			}
		}
		return true;
	}
	return false;
}