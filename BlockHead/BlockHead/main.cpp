#include "main.h"
#include "game.h"

HWND hWnd;
HWND hP1Words;
HWND hP2Words;
HWND hField[5][5];
HWND hLetters[32];
HWND hClear;
HWND hPass;
HWND hSend;
HWND hP1Info;
HWND hP2Info;
HWND hTimerInfo;
DIC dic;
DIC usedWords;
WCHAR field[5][5];
std::wstring lpLetter;
bool flag[5][5];
bool bIsEnglish;
BESTWORD word;
std::wstring lpP1Name = L"Игрок 1\nСчет:";
std::wstring lpP2Name = L"Игрок 2\nСчет:";
std::wstring lpTimerInfo = L"До конца хода осталось ";
TURN turn;
int lastI = -1;
int lastJ = -1;
int nP1Score;
int nP2Score;
bool isCPU;
int nSec;
int nCount;
int nP1PassCount;
int nP2PassCount;

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASS wcl;
	MSG msg;

	INITCOMMONCONTROLSEX icc ={sizeof(INITCOMMONCONTROLSEX)};
	icc.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&icc);

	memset(&wcl, 0, sizeof(WNDCLASS));
	wcl.lpfnWndProc = WndProc;
	wcl.hInstance = hInst;
	wcl.lpszClassName = _T("Основное окно");
	wcl.hCursor = LoadCursor(0, IDC_ARROW);
	wcl.hbrBackground = (HBRUSH)GetStockObject(DKGRAY_BRUSH);
	wcl.style = 0;

	RegisterClass(&wcl);

	hWnd = CreateWindow(wcl.lpszClassName, _T("Балда"), WS_OVERLAPPED|WS_CAPTION|WS_SYSMENU|WS_THICKFRAME, CW_USEDEFAULT, CW_USEDEFAULT, 700, 510, 0, LoadMenu(hInst, MAKEINTRESOURCE(IDR_MENU1)), hInst, 0);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	
	while(GetMessage(&msg, NULL, 0, 0))
	{
		DispatchMessage(&msg);
		TranslateMessage(&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	srand((unsigned int)time(0));
	switch (uMessage)
	{
		HANDLE_MSG(hWnd, WM_DESTROY, OnDestroy);
		HANDLE_MSG(hWnd, WM_CREATE, OnCreate);
		HANDLE_MSG(hWnd, WM_COMMAND, OnCommand);
		HANDLE_MSG(hWnd, WM_TIMER, OnTimer);
	default:
		return DefWindowProc(hWnd, uMessage, wParam, lParam);
	}
	return 0;
}

BOOL CALLBACK DlgProc(HWND hDlg, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	switch(uMessage)
	{
		HANDLE_MSG(hDlg, WM_INITDIALOG, OnInit);
		HANDLE_MSG(hDlg, WM_COMMAND, OnCommandDlg);
	}
	return FALSE;
}

void OnDestroy(HWND hWnd)
{
	PostQuitMessage(0);
}
BOOL OnCreate(HWND hWnd, LPCREATESTRUCT lpCreateStruct)
{
	hP1Words = CreateWindow(_T("LISTBOX"), 0, WS_CHILD, 10, 10, 150, 255, hWnd, 0, GetModuleHandle(0), 0);
	hP2Words = CreateWindow(_T("LISTBOX"), 0, WS_CHILD, 525, 10, 150, 255, hWnd, 0, GetModuleHandle(0), 0);
	int *y = new int;
	int *x = new int;
	*y = 10;
	for (int i = 0; i < 5; i++)
	{
		*x = 220;
		for (int j = 0; j < 5; j++)
		{
			hField[i][j] = CreateWindow(_T("BUTTON"), 0, WS_CHILD|BS_BITMAP, *x, *y, 40, 40, hWnd, HMENU(i * 5 + j + FieldButton), GetModuleHandle(0), 0);
			*x += 50;	
		}
		*y += 50;
	}
	*y = 320;
	*x = 20;
	for (int i = 0, j = IDB_BITMAP1; i < 32; i++, j++)
	{
		if (i == 16)
		{
			*x = 20;
			*y += 40;
		}
		hLetters[i] = CreateWindow(_T("BUTTON"), 0, WS_CHILD|BS_BITMAP, *x, *y, 40, 40, hWnd, HMENU(LetterButton + i), GetModuleHandle(0), 0);
		SendMessage(hLetters[i], BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(j)));
		*x += 40;
	}
	hSend = CreateWindow(_T("BUTTON"), 0, WS_CHILD, 245, 265, 200, 40, hWnd, HMENU(ID_SEND), GetModuleHandle(0), 0);
	hClear = CreateWindow(_T("BUTTON"), _T("Очистить"), WS_CHILD, 10, 420, 80, 20, hWnd, HMENU(ID_CLEAR), GetModuleHandle(0), 0);
	hPass = CreateWindow(_T("BUTTON"), _T("Пасс"), WS_CHILD, 100, 420, 80, 20, hWnd, HMENU(ID_PASS), GetModuleHandle(0), 0);
	hP1Info = CreateWindow(_T("STATIC"), lpP1Name.c_str(), WS_CHILD, 35, 265, 100, 35, hWnd, 0, GetModuleHandle(0), 0);
	hP2Info = CreateWindow(_T("STATIC"), lpP2Name.c_str(), WS_CHILD, 550, 265, 100, 35, hWnd, 0, GetModuleHandle(0), 0);
	hTimerInfo = CreateWindow(_T("STATIC"), 0, WS_CHILD, 450, 420, 190, 20, hWnd, 0, GetModuleHandle(0), 0);
	if (!bFillingDic(dic))
		MessageBox(hWnd,_T("Не найден словарь"), 0, 0);
	bIsEnglish = false;
	delete x,y;
	return true;
}
void OnCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify)
{
	static bool isAddedUsed = false;
	static bool isAdded = false;
	static int curI = -1;
	static int curJ = -1;
	switch (id)
	{
	case ID_NewGame:
	case ID_GAME_NEWGAME:
		DialogBox(GetModuleHandle(0), MAKEINTRESOURCE(IDD_DIALOG1), hWnd, DlgProc);
		break;
	case ID_SaveGame:
	case ID_GAME_SAVEGAME:
		SaveGame();
		break;
	case ID_LoadGame:
	case ID_GAME_LOADGAME:
		LoadGame();
		break;
	case ID_40009:
		SetMenu(hWnd, LoadMenu(GetModuleHandle(0), MAKEINTRESOURCE(IDR_MENU2)));
		break;
	case ID_SETTINGS_TORUSSIAN:
		SetMenu(hWnd, LoadMenu(GetModuleHandle(0), MAKEINTRESOURCE(IDR_MENU1)));
		break;
	case ID_SEND:
		if (!isCPU)
		{
			if (bSendWord(dic, usedWords, word, field, (turn == 0)?nP1Score:nP2Score, (turn == 0)?hP1Words:hP2Words, (turn == 0)?hP1Info:hP2Info, (turn == 0)?lpP1Name:lpP2Name, hWnd, turn, lastI, lastJ))
			{
				ResetTimer();
			}
			bResetTurn(isAdded, isAddedUsed, curI, curJ, lastI, lastJ, lpLetter, hSend, hField);
		}
		else
		{
			if (bSendWord(dic, usedWords, word, field, nP1Score, hP1Words, hP1Info, lpP1Name, hWnd, turn, lastI, lastJ))
			{
				bCPUTurn(field, word, dic, usedWords, nP2Score, hP2Words, hP2Info, hField, lpP2Name, hWnd);
				ResetTimer();
				bResetTurn(isAdded, isAddedUsed, curI, curJ, lastI, lastJ, lpLetter, hSend, hField, isCPU);
			}
			else
				bResetTurn(isAdded, isAddedUsed, curI, curJ, lastI, lastJ, lpLetter, hSend, hField);
		}
		if (bIsEnd(field, nP1Score, nP2Score, hWnd))
			StopGame();
		break;
	case ID_CLEAR:
		bResetTurn(isAdded, isAddedUsed, curI, curJ, lastI, lastJ, lpLetter, hSend, hField);
		break;
	case ID_PASS:
		if (!isCPU)
			bResetTurn(isAdded, isAddedUsed, curI, curJ, lastI, lastJ, lpLetter, hSend, hField);
		else
		{
			bResetTurn(isAdded, isAddedUsed, curI, curJ, lastI, lastJ, lpLetter, hSend, hField, isCPU);
			bCPUTurn(field, word, dic, usedWords, nP2Score, hP2Words, hP2Info, hField, lpP2Name, hWnd);
		}
		if (!bPassCount((turn == Player1)?nP1PassCount:nP2PassCount))
			turn = (turn == Player1)?Player2:Player1;
		else
		{
			if (bIsEnd(field, (turn == Player1)?1:0, (turn == Player1)?0:1, hWnd, false))
				StopGame();
		}
		break;
	}
	if (id >= LetterButton && id <= LetterButton + 31)
	{
		bLetterChoose(lpLetter, id, isAdded);
	}
	if (id >= FieldButton && id <= FieldButton + 25)
	{
		if (field[(id - FieldButton) / 5][(id - FieldButton) % 5] == 0)
		{
			lastI = (id - FieldButton) / 5;
			lastJ = (id - FieldButton) % 5;
		}
		bEnterWord(id, curI, curJ, hSend, word, field, isAdded, isAddedUsed, lpLetter, flag, hField);
	}
}
void OnTimer(HWND hWnd, UINT id)
{
	WCHAR *buffer;
	std::wstring *temp;
	switch (id)
	{
	case 1:
		buffer = new WCHAR[20];
		_itow(nSec - nCount++, buffer, 10);
		temp = new std::wstring;
		*temp = lpTimerInfo + buffer;
		SetWindowText(hTimerInfo, temp->c_str());
		delete [] buffer;
		delete temp;
		break;
	case 2:
		nCount = 1;
		SetWindowText(hTimerInfo, _T("Время вышло!"));
		SendMessage(hWnd, WM_COMMAND, MAKEWPARAM(ID_PASS, BN_CLICKED), (LPARAM)hPass); 
		//bResetTurn(isAdded, isAddedUsed, curI, curJ, lastI, lastJ, lpLetter, hSend, hField, isCPU);
		break;
	}
}
BOOL OnInit(HWND hDlg, HWND hwndFocus, LPARAM lParam)
{
	SendDlgItemMessage(hDlg, IDC_SPIN1, UDM_SETRANGE32, 1, 120);
	SendDlgItemMessage(hDlg, IDC_SPIN1, UDM_SETPOS32, 0, 30);
	SendDlgItemMessage(hDlg, IDC_RADIO1, BM_SETCHECK, BST_CHECKED, 0);
	return true;
}
void OnCommandDlg(HWND hDlg, int id, HWND hwndCtl, UINT codeNotify)
{
	switch (id)
	{
	case IDC_OK:
		WCHAR *buffer = new WCHAR[20];
		SendDlgItemMessage(hDlg, IDC_EDIT1, WM_GETTEXT, 20, (LPARAM)buffer);
		nSec = _wtoi(buffer);
		delete[] buffer;
		if (SendDlgItemMessage(hDlg, IDC_RADIO2, BM_GETCHECK, 0, 0) == BST_CHECKED)
		{
			isCPU = true;
		}
		else
		{
			isCPU = false;
		}
		StartGame();
		nCount = 1;
		KillTimer(hWnd, 1);
		KillTimer(hWnd, 2);
		SetTimer(hWnd, 1, 1000, NULL);
		SetTimer(hWnd, 2, nSec * 1000, NULL);
		EndDialog(hDlg, 0);
		break;
	}
}
bool StartGame()
{
	ShowWindow(hP1Words, SW_SHOWNORMAL);
	ShowWindow(hP2Words, SW_SHOWNORMAL);
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			ShowWindow(hField[i][j], SW_SHOWNORMAL);
	for (int i = 0; i < 32; i++)
		ShowWindow(hLetters[i], SW_SHOWNORMAL);
	ShowWindow(hSend, SW_SHOWNORMAL);
	ShowWindow(hClear, SW_SHOWNORMAL);
	ShowWindow(hPass, SW_SHOWNORMAL);
	ShowWindow(hP1Info, SW_SHOWNORMAL);
	ShowWindow(hP2Info, SW_SHOWNORMAL);
	ShowWindow(hTimerInfo, SW_SHOWNORMAL);
	bInitField(field, dic, usedWords);
	bShowField(field, hField);
	turn = Player1;
	nP1Score = 0;
	nP2Score = 0;
	nP1PassCount = 0;
	nP2PassCount = 0;
	SetWindowText(hP1Info, lpP1Name.c_str());
	SetWindowText(hP2Info, lpP2Name.c_str());
	SendMessage(hP1Words, LB_RESETCONTENT, 0, 0);
	SendMessage(hP2Words, LB_RESETCONTENT, 0, 0);
	SetWindowText(hSend, L"");
	return true;
}
bool StopGame()
{
	ShowWindow(hP1Words, SW_HIDE);
	ShowWindow(hP2Words, SW_HIDE);
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			ShowWindow(hField[i][j], SW_HIDE);
	for (int i = 0; i < 32; i++)
		ShowWindow(hLetters[i], SW_HIDE);
	ShowWindow(hSend, SW_HIDE);
	ShowWindow(hClear, SW_HIDE);
	ShowWindow(hPass, SW_HIDE);
	ShowWindow(hP1Info, SW_HIDE);
	ShowWindow(hP2Info, SW_HIDE);
	ShowWindow(hTimerInfo, SW_HIDE);
	KillTimer(hWnd, 1);
	KillTimer(hWnd, 2);
	return true;
}
bool ResetTimer()
{
	nCount = 1;
	KillTimer(hWnd, 2);
	SetTimer(hWnd, 2, nSec * 1000, NULL);
	return true;
}
bool SaveGame()
{
	std::basic_fstream<wchar_t> fOut; 
	fOut.imbue(std::locale("rus_rus.866"));
	WCHAR szFileName[MAX_PATH];
	std::wstring szField;
	OPENFILENAME ofn;
	memset(&ofn, 0, sizeof(OPENFILENAME));
	ofn.hInstance = GetModuleHandle(0);
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hWnd;
	ofn.lpstrFile = szFileName;
	ofn.nMaxFile = sizeof(szFileName);
	ofn.lpstrFilter = L"Файлы сохранений\0*.sav\0\0";
	wcscpy_s(szFileName, _countof(szFileName), L"");
	GetSaveFileName(&ofn);
	wcscpy_s(szFileName, _countof(szFileName), ofn.lpstrFile);
	if (wcsstr(szFileName, L".sav") == NULL && wcsstr(szFileName, L".SAV") == NULL)
		wcscat_s(szFileName, _countof(szFileName), L".sav");
	fOut.open(szFileName, std::ofstream::binary|std::ofstream::out);
	for(int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			szField += field[i][j];
		}
	}
	fOut<<szField<<L'\n';
	fOut<<turn<<L'\n';
	bWritePlayerInfo(fOut, hP1Words, nP1Score, nP1PassCount);
	fOut<<L'\n';
	bWritePlayerInfo(fOut, hP2Words, nP2Score, nP2PassCount);
	fOut.close();
	return true;
}
bool bWritePlayerInfo(std::basic_fstream<WCHAR> &fOut, HWND hWords, int nScore, int nPassCount)
{
	std::vector <std::wstring> words;
	for (int i = 0; i < SendMessage(hWords, LB_GETCOUNT, 0, 0); i++)
	{
		int n = SendMessage(hWords, LB_GETTEXTLEN, i, 0);
		WCHAR *temp = new WCHAR[n + 1];
		SendMessage(hWords, LB_GETTEXT, i, (LPARAM)temp);
		words.push_back(temp);
		delete [] temp;
	}
	for (int i = 0; i < words.size(); i++)
	{
		fOut<<words[i]<<L' ';
	}
	fOut<<L'\n';
	fOut<<nScore<<L'\n';
	fOut<<nPassCount<<L'\n';
	return true;
}
bool LoadGame()
{
	std::basic_fstream<wchar_t> fIn; 
	fIn.imbue(std::locale("rus_rus.866"));
	WCHAR szFileName[MAX_PATH];
	OPENFILENAME ofn;
	memset(&ofn, 0, sizeof(OPENFILENAME));
	ofn.hInstance = GetModuleHandle(0);
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hWnd;
	ofn.lpstrFile = szFileName;
	ofn.nMaxFile = sizeof(szFileName);
	ofn.lpstrFilter = L"Файлы сохранений\0*.sav\0\0";
	wcscpy_s(szFileName, _countof(szFileName), L"");
	GetOpenFileName(&ofn);
	wcscpy_s(szFileName, _countof(szFileName), ofn.lpstrFile);
	fIn.open(szFileName, std::ofstream::binary|std::ofstream::in);
	for(int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			field[i][j] = fIn.get();
		}
	}
	fIn.get();
	fIn.get()>>turn;
	fIn.get();
	bReadPlayerData(fIn, hP1Words, nP1Score, nP2PassCount);
	fIn.get();
	bReadPlayerData(fIn, hP2Words, nP1Score, nP2PassCount);
	fIn.close();
	bShowField(field, hField);
	return true;
}
bool bReadPlayerData(std::basic_fstream<WCHAR> &fIn, HWND hWords, int &nScore, int &nPassCount)
{
	std::wstring temp;
	WCHAR c = 0;
	while (c != L'\n')
	{
		c = fIn.get();
		if (c == L' ')
		{
			SendMessage(hWords, LB_ADDSTRING, 0, (LPARAM)temp.c_str());
			temp.clear();
		}
		else 
			temp += c;
	}
	fIn>>nScore;
	fIn.get();
	fIn>>nPassCount;
	return true;
}